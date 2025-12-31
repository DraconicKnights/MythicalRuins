#include "PlayerController.h"
#include "../../Application.h"
#include "../../Render/Object/Objects/BoundingBox.h"

void MythicalRuins::PlayerController::OnStart() {
    auto* app = MythicalRuins::Application::Get();
    if (!app) return;

    auto& player = app->GetObjectController().Spawn<Player>();
    player.Pos = m_PlayerState.Pos;
    player.Size = m_PlayerState.Size;
    player.Layer = (int)RenderLayer::Actors;

    m_PlayerEntity = &player;

    auto& testPlayer = app->GetObjectController().Spawn<Player>();
    testPlayer.Pos = Vector2{ 380, 240 };
    testPlayer.Size = Vector2{ 32, 32 };
    testPlayer.Layer = (int)RenderLayer::Actors;

    auto& boundingBoxTest = app->GetObjectController().Spawn<BoundingBox>();
    boundingBoxTest.Pos = Vector2 {380, 140 };
    boundingBoxTest.Size = Vector2 { 64, 64 };
    boundingBoxTest.Layer = (int)RenderLayer::Foreground;
}

void MythicalRuins::PlayerController::OnUpdate() {

}

void MythicalRuins::PlayerController::OnFixedUpdate() {
    auto* app = MythicalRuins::Application::Get();
    if (!app) return;

    auto& input = app->GetInputController();
    float dt = app->GetEngineFixedDT();

    if (input.Down(InputAction::MoveForward)) m_PlayerState.Pos.y -= m_PlayerState.Speed * dt;
    if (input.Down(InputAction::MoveBack)) m_PlayerState.Pos.y += m_PlayerState.Speed * dt;
    if (input.Down(InputAction::MoveLeft)) m_PlayerState.Pos.x -= m_PlayerState.Speed * dt;
    if (input.Down(InputAction::MoveRight)) m_PlayerState.Pos.x += m_PlayerState.Speed * dt;

    if (input.Down(InputAction::OpenDebugConsole)) app->GetDebugConsoleController().toggle();

    auto& physics = app->GetPhysicsController();
    Vector2 desired = m_PlayerState.Pos;

    Vector2 tryX = { desired.x, m_PlayerEntity->Pos.y };
    if (physics.CanMove(m_PlayerEntity, tryX)) {
        m_PlayerEntity->Pos.x = tryX.x;
    }
    Vector2 tryY = { m_PlayerEntity->Pos.x, desired.y };
    if (physics.CanMove(m_PlayerEntity, tryY)) {
        m_PlayerEntity->Pos.y = tryY.y;
    }

    m_PlayerState.Pos = m_PlayerEntity->Pos;

}


void MythicalRuins::PlayerController::OnLateUpdate() {

}

void MythicalRuins::PlayerController::OnDestroy() {

}