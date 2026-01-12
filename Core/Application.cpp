#include <rlImGui.h>
#include "Application.h"
#include "raylib.h"
#include "System/SystemsControllers/PlayerController.h"
#include "System/SystemsControllers/RendererController.h"
#include "System/Physics/PhysicsController.h"
#include "Manager/InputManager.h"

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

    std::cout << "Before InitApp\n";
    IntiApp();
    std::cout << "After InitApp\n";

    const float fixedDt = 1.0f / 60.0f;
    float accumulator = 0.0f;

    m_SystemManager.EnableAll();

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

    m_SystemManager.DisableAll();

    m_SystemManager.DestroyAll();
    CloseWindow();
}

void MythicalRuins::Application::IntiApp() {
    InitWindow(m_AppSpecs.Width, m_AppSpecs.Height, m_AppSpecs.Title);

    Logger::setLogLevel(LogLevel::Debug);

    rlImGuiSetup(true);

    SetTargetFPS(60);

    m_GameState = GameState::Playing;

    // Core Systems
    m_SystemManager.AddSystem<InputManager>(0);

    m_SystemManager.AddSystem<TileMap>(10);
    m_SystemManager.AddSystem<RendererController>(20);
    m_SystemManager.AddSystem<PhysicsController>(30);
    m_SystemManager.AddSystem<PlayerController>(40);

    std::cout << "Before StartAll\n";
    m_SystemManager.StartAll();
    std::cout << "After StartAll\n";
}