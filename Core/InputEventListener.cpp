#include "InputEventListener.h"
#include "raylib.h"

void MythicalRuins::InputEventListener::BindKey(MythicalRuins::InputAction action, int rayLibKey) {
    m_KeyBindings[action] = rayLibKey;
}

void MythicalRuins::InputEventListener::BindMouse(MythicalRuins::InputAction action, int mouseButton) {
    m_MouseBindings[action] = mouseButton;
}

bool MythicalRuins::InputEventListener::Pressed(MythicalRuins::InputAction action) const {
    if (auto it = m_KeyBindings.find(action); it != m_KeyBindings.end()) {
        if (IsKeyPressed(it->second)) return true;
    }
    if (auto it = m_MouseBindings.find(action); it != m_MouseBindings.end()) {
        if (IsMouseButtonPressed(it->second)) return true;
    }
    return false;
}

bool MythicalRuins::InputEventListener::Down(MythicalRuins::InputAction action) const {
    if (auto it = m_KeyBindings.find(action); it != m_KeyBindings.end()) {
        if (IsKeyDown(it->second)) return true;
    }
    if (auto it = m_MouseBindings.find(action); it != m_MouseBindings.end()) {
        if (IsMouseButtonDown(it->second)) return true;
    }
    return false;
}

bool MythicalRuins::InputEventListener::Released(MythicalRuins::InputAction action) const {
    if (auto it = m_KeyBindings.find(action); it != m_KeyBindings.end()) {
        if (IsKeyReleased(it->second)) return true;
    }
    if (auto it = m_MouseBindings.find(action); it != m_MouseBindings.end()) {
        if (IsMouseButtonReleased(it->second)) return true;
    }
    return false;
}

void MythicalRuins::InputEventListener::OnPressed(MythicalRuins::InputAction action, std::function<void()> callback) {
    m_PressedCallbacks[action].push_back(std::move(callback));
}

void MythicalRuins::InputEventListener::Update() {
    // Dispatch for key bindings
    for (const auto& [action, key] : m_KeyBindings) {
        if (IsKeyPressed(key)) {
            if (auto it = m_PressedCallbacks.find(action); it != m_PressedCallbacks.end()) {
                for (auto& cb : it->second) cb();
            }
        }
    }

    // Dispatch for mouse bindings
    for (const auto& [action, button] : m_MouseBindings) {
        if (IsMouseButtonPressed(button)) {
            if (auto it = m_PressedCallbacks.find(action); it != m_PressedCallbacks.end()) {
                for (auto& cb : it->second) cb();
            }
        }
    }
}