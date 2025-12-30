#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"
#include "../../Object/Object.h"

namespace MythicalRuins {

    class Player : public Entity {
    public:
        Player() {
            SetName("Player");
        }

        void Render() override;
        void OnTrigger(Object* other) override;
    };

} // MythicalRuins

#endif //PLAYER_H
