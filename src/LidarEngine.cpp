#include <OpenGL/gl3.h>
#include <glad/glad.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class WorldObject {
public:
    glm::vec3 position;
    glm::vec3 size;
    bool isEnemy;
    
    WorldObject(const glm::vec3& pos, const glm::vec3& sz, bool enemy = false)
        : position(pos), size(sz), isEnemy(enemy) {}
};

class LidarEngine {
private:
    int numRays;
    float coneHeight;
    float burstRadius;
    glm::vec3 cameraPosition;
    std::vector<WorldObject> objects;
    std::vector<glm::vec3> hitPoints;
    std::vector<bool> isEnemyHits;
    GLuint vertex_arr_obj;
    GLuint vbo;
    std::mt19937 rng;
    
    bool rayAABBIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                               const glm::vec3& boxMin, const glm::vec3& boxMax, float& t) {
        float tmin = (boxMin.x - rayOrigin.x) / rayDirection.x;
        float tmax = (boxMax.x - rayOrigin.x) / rayDirection.x;
        if(tmin > tmax) std::swap(tmin, tmax);
        float tymin = (boxMin.y - rayOrigin.y) / rayDirection.y;
        float tymax = (boxMax.y - rayOrigin.y) / rayDirection.y;
        if(tymin > tymax) std::swap(tymin, tymax);
        if((tmin > tymax) || (tymin > tmax))
            return false;
        if(tymin > tmin)
            tmin = tymin;
        if(tymax < tmax)
            tmax = tymax;
        float tzmin = (boxMin.z - rayOrigin.z) / rayDirection.z;
        float tzmax = (boxMax.z - rayOrigin.z) / rayDirection.z;
        if(tzmin > tzmax) std::swap(tzmin, tzmax);
        if((tmin > tzmax) || (tzmin > tmax))
            return false;
        if(tzmin > tmin)
            tmin = tzmin;
        if(tzmax < tmax)
            tmax = tzmax;
        t = tmin < 0.0f ? tmax : tmin;
        return t >= 0.0f;
    }
    
public:
    LidarEngine(int numRays = 10000)
        : numRays(numRays), coneHeight(10.0f), burstRadius(20.0f), cameraPosition(0.0f, 0.0f, 0.0f) {
        std::random_device rd;
        rng = std::mt19937(rd());
        initializeGL();
    }
    
    ~LidarEngine() {
        glDeleteVertexArrays(1, &vertex_arr_obj);
        glDeleteBuffers(1, &vbo);
    }
    
    void initializeGL() {
        glGenVertexArrays(1, &vertex_arr_obj);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vertex_arr_obj);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * numRays, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void addObject(const WorldObject& obj) {
        objects.push_back(obj);
    }
    
    void setCameraPosition(const glm::vec3& position) {
        cameraPosition = position;
    }
    
    void fireRays(bool burstMode = false) {
        hitPoints.clear();
        isEnemyHits.clear();
        hitPoints.reserve(numRays);
        isEnemyHits.reserve(numRays);
        
        std::uniform_real_distribution<float> uniformDist(0.0f, 1.0f);
        std::uniform_real_distribution<float> thetaDist(0.0f, 2.0f * glm::pi<float>());
        
        for(int i = 0; i < numRays; ++i) {
            float theta = thetaDist(rng);
            glm::vec3 ray;
            if(burstMode) {
                std::uniform_real_distribution<float> phiDist(0.0f, glm::pi<float>());
                float phi = phiDist(rng);
                ray.x = burstRadius * sin(phi) * cos(theta);
                ray.y = burstRadius * sin(phi) * sin(theta);
                ray.z = burstRadius * cos(phi);
            } else {
                std::uniform_real_distribution<float> phiDist(0.0f, (glm::pi<float>() / 2.0f) * (coneHeight / burstRadius));
                float phi = phiDist(rng);
                ray.x = coneHeight * sin(phi) * cos(theta);
                ray.y = coneHeight * sin(phi) * sin(theta);
                ray.z = coneHeight * cos(phi);
            }
            glm::vec3 direction = glm::normalize(ray);
            for(const auto& obj : objects) {
                glm::vec3 objMin = obj.position - obj.size * 0.5f;
                glm::vec3 objMax = obj.position + obj.size * 0.5f;
                float t = 0.0f;
                if(rayAABBIntersection(cameraPosition, direction, objMin, objMax, t)) {
                    if(t > 0.0f && t < 1.0f) {
                        glm::vec3 hitPoint = cameraPosition + direction * t;
                        hitPoints.push_back(hitPoint);
                        isEnemyHits.push_back(obj.isEnemy);
                        break;
                    }
                }
            }
        }
        renderMarkers();
    }
    
    void renderMarkers() {
        if(hitPoints.empty())
            return;
        
        std::vector<Vertex> markerVertices;
        markerVertices.reserve(hitPoints.size() * 4);
        float markerSize = 0.2f;
        
        for(size_t i = 0; i < hitPoints.size(); ++i) {
            glm::vec3 hp = hitPoints[i];
            glm::vec3 col = isEnemyHits[i] ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(1.0f);
            Vertex verts[4] = {
                { glm::vec3(hp.x - markerSize, hp.y - markerSize, hp.z), col },
                { glm::vec3(hp.x + markerSize, hp.y - markerSize, hp.z), col },
                { glm::vec3(hp.x + markerSize, hp.y + markerSize, hp.z), col },
                { glm::vec3(hp.x - markerSize, hp.y + markerSize, hp.z), col }
            };
            markerVertices.insert(markerVertices.end(), std::begin(verts), std::end(verts));
        }
        
        glBindVertexArray(vertex_arr_obj);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, markerVertices.size() * sizeof(Vertex), markerVertices.data());
        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, markerVertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};

LidarEngine* enginePtr = nullptr;
bool useBurstMode = false;

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    enginePtr->fireRays(useBurstMode);
    glutSwapBuffers();
}

void reshapeCallback(int w, int h) {
    glViewport(0, 0, w, h);
}

void keyboardCallback(unsigned char key, int x, int y) {
    if(key == 'b' || key == 'B') {
        useBurstMode = !useBurstMode;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lidar Engine");
    
    if (!gladLoadGL()) {
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    enginePtr = new LidarEngine(5000);
    enginePtr->setCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    enginePtr->addObject(WorldObject(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), false));
    enginePtr->addObject(WorldObject(glm::vec3(2.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), true));
    
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();
    
    delete enginePtr;
    return 0;
}
