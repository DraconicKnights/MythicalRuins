#include "PlayerController.h"
#include "../../Render/Object/Objects/BoundingBox.h"

void MythicalRuins::PlayerController::OnStart() {
    m_App = Application::Get();

    m_ObjectLoader = ObjectLoaderManager::Get();
    m_InputListener = InputEventListener::Get();
    m_SystemManager = SystemManager::Get();

    auto& player = m_ObjectLoader->Spawn<Player>();
    player.Pos = m_PlayerState.Pos;
    player.Size = m_PlayerState.Size;
    player.Layer = (int)RenderLayer::Actors;

    m_PlayerEntity = &player;

    auto& testPlayer = m_ObjectLoader->Spawn<Player>();
    testPlayer.Pos = Vector2{ 380, 240 };
    testPlayer.Size = Vector2{ 32, 32 };
    testPlayer.Layer = (int)RenderLayer::Actors;

    auto& boundingBoxTest = m_ObjectLoader->Spawn<BoundingBox>();
    boundingBoxTest.Pos = Vector2 {380, 140 };
    boundingBoxTest.Size = Vector2 { 64, 64 };
    boundingBoxTest.Layer = (int)RenderLayer::Foreground;
}

void MythicalRuins::PlayerController::OnUpdate() {

}

void MythicalRuins::PlayerController::OnFixedUpdate() {


    float dt = m_App->GetEngineFixedDT();

    if (m_InputListener->Down(InputAction::MoveForward)) m_PlayerState.Pos.y -= m_PlayerState.Speed * dt;
    if (m_InputListener->Down(InputAction::MoveBack)) m_PlayerState.Pos.y += m_PlayerState.Speed * dt;
    if (m_InputListener->Down(InputAction::MoveLeft)) m_PlayerState.Pos.x -= m_PlayerState.Speed * dt;
    if (m_InputListener->Down(InputAction::MoveRight)) m_PlayerState.Pos.x += m_PlayerState.Speed * dt;

    auto* physics = m_SystemManager->GetSystem<PhysicsController>();
    Vector2 desired = m_PlayerState.Pos;

    Vector2 tryX = { desired.x, m_PlayerEntity->Pos.y };
    if (physics->CanMove(m_PlayerEntity, tryX)) {
        m_PlayerEntity->Pos.x = tryX.x;
    }
    Vector2 tryY = { m_PlayerEntity->Pos.x, desired.y };
    if (physics->CanMove(m_PlayerEntity, tryY)) {
        m_PlayerEntity->Pos.y = tryY.y;
    }

    m_PlayerState.Pos = m_PlayerEntity->Pos;

}


void MythicalRuins::PlayerController::OnLateUpdate() {

}

void MythicalRuins::PlayerController::OnDisable() {
    m_App = nullptr;
    m_ObjectLoader = nullptr;
    m_InputListener = nullptr;
    m_SystemManager = nullptr;
}


void MythicalRuins::PlayerController::OnDestroy() {

}
