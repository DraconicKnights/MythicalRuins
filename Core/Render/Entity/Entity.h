#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "../Object/Object.h"

namespace MythicalRuins {

    class Entity : public Object {
    public:
        Vector2 Velocity{0,0};

        Entity() {
            IsDynamic = true;
            Collidable = true;
        }
    };
}

#endif //ENTITY_H
