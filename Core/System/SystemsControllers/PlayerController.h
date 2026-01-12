#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "raylib.h"
#include "../SystemCore.h"
#include "../../Render/Entity/Entites/Player.h"
#include "../../World/ObjectLoaderManager.h"
#include "../../InputEventListener.h"
#include "../SystemManager.h"
#include "../../Application.h"

namespace MythicalRuins {

    struct PlayerState {
        Vector2 Pos{200, 200};
        Vector2 Size{32, 32};
        float Speed = 250.0f;
    };

    class PlayerController : public SystemCore {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnLateUpdate() override;
        void OnDisable() override;
        void OnDestroy() override;

        const char* GetName() override { return "PlayerController}"; }
    private:
        Application* m_App = nullptr;
        ObjectLoaderManager* m_ObjectLoader = nullptr;
        InputEventListener* m_InputListener = nullptr;
        SystemManager* m_SystemManager = nullptr;

        PlayerState m_PlayerState;
        Player* m_PlayerEntity;
    };

} // MythicalRuins

#endif //PLAYERCONTROLLER_H
