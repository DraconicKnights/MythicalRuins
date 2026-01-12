#include "InputManager.h"
#include "raylib.h"
#include "../Application.h"

void MythicalRuins::InputManager::OnStart() {

    m_InputListener = InputEventListener::Get();

    m_InputListener->BindKey(InputAction::MoveForward, KEY_W);
    m_InputListener->BindKey(InputAction::MoveBack, KEY_S);
    m_InputListener->BindKey(InputAction::MoveRight, KEY_D);
    m_InputListener->BindKey(InputAction::MoveLeft, KEY_A);

    m_InputListener->BindKey(InputAction::OpenDebugConsole, KEY_F10);

    m_InputListener->BindMouse(InputAction::DeltaLeftClick, MOUSE_BUTTON_LEFT);
    m_InputListener->BindMouse(InputAction::DeltaRightClick, MOUSE_BUTTON_RIGHT);
}

void MythicalRuins::InputManager::OnDisable() {
    m_InputListener = nullptr;
}

void MythicalRuins::InputManager::OnDestroy() {

}

