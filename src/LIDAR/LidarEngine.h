#ifndef LIDAR_ENGINE_H
#define LIDAR_ENGINE_H

#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class WorldObject {
public:
    glm::vec3 position;
    glm::vec3 size;
    bool isEnemy;
    
    WorldObject(const glm::vec3& pos, const glm::vec3& sz, bool enemy);
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
                             const glm::vec3& boxMin, const glm::vec3& boxMax, float& t);
public:
    LidarEngine(int numRays = 10000);
    ~LidarEngine();
    
    void initializeGL();
    void addObject(const WorldObject& obj);
    void setCameraPosition(const glm::vec3& position);
    void fireRays(bool burstMode);
    void renderMarkers();
};

#endif
