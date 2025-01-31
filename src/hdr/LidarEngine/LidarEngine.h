#ifndef LIDAR_ENGINE_H
#define LIDAR_ENGINE_H


#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>
#include "../engine.h"
#include <glm/gtc/matrix_transform.hpp>



class LidarEngine {
private:
    int numRays;
    float coneHeight;
    float burstRadius;
    glm::vec3 cameraPosition;
    std::vector<engines::WorldObject> objects;
    std::vector<glm::vec3> hitPoints;
    std::vector<bool> isEnemyHits;
    GLuint vertex_arr_obj;
    GLuint vbo;

    
public:
    LidarEngine(int numRays = 10000);
    ~LidarEngine();
    
    void initializeGL();
    void addObject(engines::WorldObject obj);
    void fireRays(bool burstMode = false);
    void setCameraPosition(glm::vec3 position);
    void renderMarkers();
};

#endif
