#ifndef RENDERERCONTROLLER_H
#define RENDERERCONTROLLER_H

#include "../SystemCore.h"

namespace MythicalRuins {

    class RendererController : public SystemCore {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnDestroy() override;
    };

} // MythicalRuins

#endif //RENDERERCONTROLLER_H
