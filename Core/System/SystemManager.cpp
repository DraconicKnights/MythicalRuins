#include "SystemManager.h"

void MythicalRuins::SystemManager::StartAll() {
    for (auto& s: m_Systems) s->OnStart();
}

void MythicalRuins::SystemManager::UpdateAll() {
    for (auto& s : m_Systems) s->OnUpdate();
}

void MythicalRuins::SystemManager::FixedUpdateAll() {
    for (auto& s : m_Systems) s->OnFixedUpdate();
}

void MythicalRuins::SystemManager::LateUpdateAll() {
    for (auto& s : m_Systems) s-> OnLateUpdate();
}

void MythicalRuins::SystemManager::DestroyAll() {
    for (auto& s : m_Systems) s->OnDestroy();
    m_Systems.clear();
}