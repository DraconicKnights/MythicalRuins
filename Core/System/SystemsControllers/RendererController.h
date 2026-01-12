#ifndef RENDERERCONTROLLER_H
#define RENDERERCONTROLLER_H

#include "../SystemCore.h"
#include "../../Application.h"

namespace MythicalRuins {

    class RendererController : public SystemCore {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnDisable() override;
        void OnDestroy() override;

        const char* GetName() override { return "RendererController"; }

    private:

        Application* m_App = nullptr;
        ObjectLoaderManager* m_ObjectLoader = nullptr;
        SystemManager* m_Systems = nullptr;
        TileMap* m_Tilemap = nullptr;
        DebugConsoleController* m_Debug = nullptr;

    };

} // MythicalRuins

#endif //RENDERERCONTROLLER_H
