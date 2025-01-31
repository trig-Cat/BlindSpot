//
// Created by Abhistrator on 31/01/25.
//

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include "constants.h"
#include <glm/glm.hpp>

#include "LidarEngine/LidarEngine.h"
#include "LidarEngine/LidarEngine.h"
#include "LidarEngine/LidarEngine.h"
#include "LidarEngine/LidarEngine.h"


namespace engines {
    class WorldObject {
    public:
        glm::vec3 position;
        glm::vec3 size;
        bool isEnemy;
        bool isPlayer;

        glm::vec3 velocity;
        float velocity_mag;
        glm::vec3 vel_dir;



        // TODO: add draw function
        void setAsEnemy();
        void setAsPlayer();
        void setVelMagnitude(const float magnitude);
        void update(const float dt);
        void move(const float dt);

        WorldObject(glm::vec3 pos, glm::vec3 sz, bool enemy = false)
            : position(pos), size(sz), isEnemy(enemy) {}
    private:
        void updateVelocityAttr();
    };

    class MovementEngine {
        // Has a list of objects, if enemy then call enemy movement logic to it
        // If player, then call player movement logic to it.
    public:
        std::vector<WorldObject> objects;

        // to add new objects
        void addObject(const WorldObject &obj);
        void moveAllObjects();

    private:
        void playerMovementLogic(WorldObject &player);
        void enemyMovementLogic(WorldObject &enemy);
    };

    glm::vec<3, float> normalizeVector(const glm::vec3 vec);
    float getMagnitude(const glm::vec3 vec);

} // engines

#endif //MOVEMENT_H
