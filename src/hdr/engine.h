//
// Created by Abhistrator on 31/01/25.
//

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <glm/glm.hpp>

namespace engines {
    class WorldObject {
    public:
        glm::vec3 position;
        glm::vec3 size;
        bool isEnemy;

        WorldObject(glm::vec3 pos, glm::vec3 sz, bool enemy = false)
            : position(pos), size(sz), isEnemy(enemy) {}
    };

    class MovementEngine {
    public:

    };

} // engines

#endif //MOVEMENT_H
