#ifndef LIDAR_ENGINE_H
#define LIDAR_ENGINE_H

#include "SDL3/SDL_rect.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<cstdlib>
#include<iostream>
#include <random>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  
  // TEMP: TILL A BETTER THING HAS BEEN FIGURED OUT
  // SDL_FPoint*convert_to_FPoint();
};

class WorldObject {
public:
  glm::vec3 position;
  glm::vec3 size;
  bool isEnemy;

  WorldObject(const glm::vec3 &pos, const glm::vec3 &sz, bool enemy);
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
  unsigned int vertex_arr_obj;
  unsigned int vbo;
  std::mt19937 rng;

  bool rayAABBIntersection(const glm::vec3 &rayOrigin,
                           const glm::vec3 &rayDirection,
                           const glm::vec3 &boxMin, const glm::vec3 &boxMax,
                           float &t);

public:
  LidarEngine(int numRays = 10000);
  ~LidarEngine();

  void addObject(const WorldObject &obj);
  void setCameraPosition(const glm::vec3 &position);
  void fireRays(bool burstMode);
  void renderMarkers(SDL_Renderer *renderer);
};

#endif
