//
// Created by Abhistrator on 31/01/25.
//


#include "engine.h"

namespace engines {
    // WorldObject Definitions
    void WorldObject::setAsEnemy() {
        // sets other isplayer to false, as an object cannot be enemy and player at the same time
        isEnemy = true;
        isPlayer = false;
    }
    void WorldObject::setAsPlayer() {
        // sets other is_enemy to false, as an object cannot be enemy and player at the same time
        isPlayer = true;
        isEnemy = false;
    }
    void WorldObject::move(const float dt) {
        position += velocity * dt;
    }
    void WorldObject::update(const float dt) {
        updateVelocityAttr();
        move(dt);
    }
    void WorldObject::setVelMagnitude(const float magnitude) {
        velocity = vel_dir * magnitude;
    }

    void WorldObject::updateVelocityAttr() {
        velocity_mag = getMagnitude(velocity);
        vel_dir = normalizeVector(velocity);
    }




    // Movement Engine code
    void MovementEngine::addObject(const WorldObject &obj) {
        objects.push_back(obj);
    }



    void MovementEngine::moveAllObjects() {
        // Loop over every index of objects
        for (auto &obj: objects) {

            // if player, then call player mvm logic and pass obj
            if (obj.isPlayer) {
                playerMovementLogic(obj);
            }
            // if enemy, then call enemy mvm logic and pass obj
            else if (obj.isEnemy) {
                enemyMovementLogic(obj);
            }
        }
    }

    void MovementEngine::playerMovementLogic(WorldObject &player) {

    }
    void MovementEngine::enemyMovementLogic(WorldObject &enemy) {

    }


    // regular
    glm::vec<3, float> normalizeVector(const glm::vec3 vec) {
        return vec/getMagnitude(vec);
    }
    float getMagnitude(const glm::vec3 vec) {
        return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    }




} // engines