#ifndef LIDAR_ENGINE_H
#define LIDAR_ENGINE_H


#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class WorldObject {
public:
    glm::vec3 position;
    glm::vec3 size;
    bool isEnemy;
    
    WorldObject(glm::vec3 pos, glm::vec3 sz, bool enemy = false) 
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
    
public:
    LidarEngine(int numRays = 10000);
    ~LidarEngine();
    
    void initializeGL();
    void addObject(WorldObject obj);
    void fireRays(bool burstMode = false);
    void setCameraPosition(glm::vec3 position);
    void renderMarkers();
};

#endif
