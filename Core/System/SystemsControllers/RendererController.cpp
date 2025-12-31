#include <rlImGui.h>
#include "RendererController.h"
#include "../../Application.h"

void MythicalRuins::RendererController::OnStart() {

}

void MythicalRuins::RendererController::OnUpdate() {
    auto* app = MythicalRuins::Application::Get();
    if (!app) return;

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    if (app->IsPlaying()) {
        for (const auto &e: app->GetObjectController().GetAllObjects()) {
            e->Render();
        }
    }

    rlImGuiBegin();
    app->GetMenuController().BuildUI();
    app->GetDebugConsoleController().render();
    rlImGuiEnd();

    EndDrawing();
}

void MythicalRuins::RendererController::OnDestroy() {

}