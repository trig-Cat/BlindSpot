#include <glad/glad.h>
#include "LidarEngine.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_query.hpp>
#include <algorithm>
#include <ctime>
#include <cstdlib>

LidarEngine::LidarEngine(int numRays) : numRays(numRays), 
                                        coneHeight(10.0f),
                                        burstRadius(20.0f) {
    initializeGL();
    srand(time(nullptr));

}

LidarEngine::~LidarEngine() {

    glDeleteVertexArrays(1, &vertex_arr_obj);
    glDeleteBuffers(1, &vbo);
}

void LidarEngine::initializeGL() {
    glGenVertexArrays(1, &vertex_arr_obj);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vertex_arr_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2 * numRays, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LidarEngine::addObject(engines::WorldObject obj) {
    objects.push_back(obj);
}

void LidarEngine::setCameraPosition(glm::vec3 position) {
    cameraPosition = position;
}
bool rayAABBIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection,
                          glm::vec3 boxMin, glm::vec3 boxMax,
                          float& t) {
    glm::vec3 invRay = glm::vec3(1.0f) / rayDirection;
    glm::vec3 tMin = (boxMin - rayOrigin) * invRay;
    glm::vec3 tMax = (boxMax - rayOrigin) * invRay;

    glm::vec3 t0 = max(tMin, tMax);
    glm::vec3 t1 = min(tMin, tMax);

    float tClosest = glm::max(glm::max(t0.x, t0.y), t0.z);
    float tFarthest = glm::min(glm::min(t1.x, t1.y), t1.z);

    if (tClosest < tFarthest) {
        t = tClosest;
        return true;
    }
    return false;
}


void LidarEngine::fireRays(bool burstMode) {
    hitPoints.clear();
    isEnemyHits.clear();

    std::vector<glm::vec3> rays;
    
    if (burstMode) {
        for (int i = 0; i < numRays; ++i) {
            float theta = (rand() / (float)RAND_MAX) * 2.0f * glm::pi<float>();
            float phi = (rand() / (float)RAND_MAX) * glm::pi<float>() * 2.0f;
            
            float x = burstRadius * sin(phi) * cos(theta);
            float y = burstRadius * sin(phi) * sin(theta);
            float z = burstRadius * cos(phi);

            rays.push_back(glm::vec3(x, y, z));
        }
    } else {
        for (int i = 0; i < numRays; ++i) {
            float theta = (rand() / (float)RAND_MAX) * 2.0f * glm::pi<float>();
            float phi = (rand() / (float)RAND_MAX) * (glm::pi<float>() / 2.0f) * (coneHeight / burstRadius);

            float x = coneHeight * sin(phi) * cos(theta);
            float y = coneHeight * sin(phi) * sin(theta);
            float z = coneHeight * cos(phi);

            rays.push_back(glm::vec3(x, y, z));
        }
    }

    for (const auto& ray : rays) {
        glm::vec3 rayEnd = cameraPosition + ray;
        glm::vec3 direction = glm::normalize(ray);

        for (const auto& obj : objects) {
            glm::vec3 objMin = obj.position - obj.size * 0.5f;
            glm::vec3 objMax = obj.position + obj.size * 0.5f;

            float t = -1.0f;
            if (rayAABBIntersection(cameraPosition, direction, objMin, objMax, t)) {
                if (t > 0.0f && t < 1.0f) {
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


void LidarEngine::renderMarkers() {
    if (hitPoints.empty()) return;

    std::vector<glm::vec3> markerVertices;
    float markerSize = 0.2f;

    for (size_t i = 0; i < hitPoints.size(); ++i) {
        glm::vec3 hitPoint = hitPoints[i];
        glm::vec3 color = isEnemyHits[i] ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f);

        glm::vec3 corners[4] = {
            glm::vec3(hitPoint.x - markerSize, hitPoint.y - markerSize, hitPoint.z),
            glm::vec3(hitPoint.x + markerSize, hitPoint.y - markerSize, hitPoint.z),
            glm::vec3(hitPoint.x + markerSize, hitPoint.y + markerSize, hitPoint.z),
            glm::vec3(hitPoint.x - markerSize, hitPoint.y + markerSize, hitPoint.z)
        };

        for (const auto& corner : corners) {
            markerVertices.push_back(corner);
            markerVertices.push_back(color);
        }
    }

    if (!markerVertices.empty()) {
        glBindVertexArray(vertex_arr_obj);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, markerVertices.size() * sizeof(glm::vec3), markerVertices.data());
        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, markerVertices.size() / 2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
