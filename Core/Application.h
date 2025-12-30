#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <utility>
#include <stdexcept>
#include "InputEventListener.h"
#include "System/SystemCore.h"
#include "raylib.h"
#include "System/SystemManager.h"
#include "World/ObjectLoaderManager.h"
#include "System/SystemsControllers/MainMenuController.h"
#include "System/SystemsControllers/PhysicsController.h"

namespace MythicalRuins {

    struct ApplicationSpecification {
        int Width = 1920;
        int Height = 1080;
        const char* Title = "Test";
    };

    enum GameState {
        Menu,
        Playing,
    };

    class Application {
    public:
        static Application* Get() { return G_Instance; }
        static Application& GetRef() {
            if (!G_Instance) throw std::runtime_error("Application instance not created.");
            return *G_Instance;
        }

        Application(const ApplicationSpecification& specification = ApplicationSpecification());
        ~Application();

        void RunApp();

        void SetResolution(const ApplicationSpecification& specification);

        bool IsPlaying() const { return m_GameState == GameState::Playing; }
        GameState GetGameState() const { return m_GameState; }
        void SetGameState(GameState gameState) { m_GameState = gameState; }

        float GetEngineDT() const { return m_Dt; }
        float GetEngineFixedDT() const { return m_FixedDt; }

        ApplicationSpecification GetAppSpecs() const { return m_AppSpecs; }
        InputEventListener& GetInputController() { return m_EventListener; }
        MainMenuController& GetMenuController() { return m_MenuController; }
        ObjectLoaderManager& GetObjectController() { return m_ObjectLoader; }
        PhysicsController& GetPhysicsController() { return m_PhysicsController; }

    private:
        void IntiApp();

        static Application* G_Instance;

        GameState m_GameState = GameState::Menu;

        float m_Dt;
        float m_FixedDt;

        ApplicationSpecification m_AppSpecs;
        InputEventListener m_EventListener;
        MainMenuController m_MenuController;
        SystemManager m_SystemManager;
        ObjectLoaderManager m_ObjectLoader;
        PhysicsController m_PhysicsController;
    };

} // MythicalRuins

#endif //APPLICATION_H
