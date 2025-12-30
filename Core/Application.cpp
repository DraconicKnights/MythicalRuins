#include <rlImGui.h>
#include "Application.h"
#include "raylib.h"
#include "System/SystemsControllers/PlayerController.h"
#include "System/SystemsControllers/RendererController.h"
#include "System/SystemsControllers/PhysicsController.h"

MythicalRuins::Application* MythicalRuins::Application::G_Instance = nullptr;

MythicalRuins::Application::Application(const MythicalRuins::ApplicationSpecification &specification) : m_AppSpecs(specification)
{
    if (G_Instance) {
        throw std::runtime_error("Application instance already exists.");
    }
    G_Instance = this;

}

MythicalRuins::Application::~Application()
{
    if  (G_Instance == this)
        G_Instance = nullptr;
}

void MythicalRuins::Application::SetResolution(const MythicalRuins::ApplicationSpecification& specification) {
    m_AppSpecs.Width = specification.Width;
    m_AppSpecs.Height = specification.Height;

    SetWindowSize(m_AppSpecs.Width, m_AppSpecs.Height);
}

void MythicalRuins::Application::RunApp() {
    IntiApp();

    const float fixedDt = 1.0f / 60.0f;
    float accumulator = 0.0f;

    while (!WindowShouldClose()) {

        m_Dt = GetFrameTime();

        if (m_Dt > 0.25f) m_Dt = 0.25f;

        accumulator += m_Dt;

        while (accumulator >= fixedDt) {
            m_FixedDt = fixedDt;
            m_SystemManager.FixedUpdateAll();

            accumulator -= fixedDt;
        }

        m_SystemManager.UpdateAll();

        if (m_EventListener.Pressed(InputAction::DeltaRightClick)) {
            Logger::logInfo("Mouse Right Click Action Performed");
        }

        m_SystemManager.LateUpdateAll();
    }

    m_SystemManager.DestroyAll();
    CloseWindow();
}

void MythicalRuins::Application::IntiApp() {
    InitWindow(m_AppSpecs.Width, m_AppSpecs.Height, m_AppSpecs.Title);

    rlImGuiSetup(true);

    m_EventListener.BindKey(InputAction::MoveForward, KEY_W);
    m_EventListener.BindKey(InputAction::MoveBack, KEY_S);
    m_EventListener.BindKey(InputAction::MoveRight, KEY_D);
    m_EventListener.BindKey(InputAction::MoveLeft, KEY_A);

    m_EventListener.BindMouse(InputAction::DeltaLeftClick, MOUSE_BUTTON_LEFT);
    m_EventListener.BindMouse(InputAction::DeltaRightClick, MOUSE_BUTTON_RIGHT);

    SetTargetFPS(60);

    m_SystemManager.AddSystem<RendererController>();
    m_SystemManager.AddSystem<PhysicsController>();
    m_SystemManager.AddSystem<PlayerController>();
    m_SystemManager.StartAll();
}