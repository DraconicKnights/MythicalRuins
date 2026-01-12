#include <rlImGui.h>
#include "RendererController.h"

void MythicalRuins::RendererController::OnStart() {
    m_App = MythicalRuins::Application::Get();

    m_ObjectLoader = ObjectLoaderManager::Get();
    m_Systems = SystemManager::Get();

    m_Tilemap = m_Systems->GetSystem<TileMap>();
    m_Debug = m_Systems->GetSystem<DebugConsoleController>();
}

void MythicalRuins::RendererController::OnUpdate() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    if (m_App->IsPlaying()) {
        for (const auto& e : m_ObjectLoader->GetAllObjects()) {
            e->Render();
        }

    }

    rlImGuiBegin();

    rlImGuiEnd();

    EndDrawing();
}

void MythicalRuins::RendererController::OnDisable() {
    m_App = nullptr;
    m_ObjectLoader = nullptr;
    m_Systems = nullptr;
    m_Tilemap = nullptr;
    m_Debug = nullptr;
}

void MythicalRuins::RendererController::OnDestroy() {

}
