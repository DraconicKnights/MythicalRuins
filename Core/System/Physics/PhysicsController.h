#ifndef PHYSICSCONTROLLER_H
#define PHYSICSCONTROLLER_H

#include <vector>
#include "../SystemCore.h"
#include "../../Render/Object/Object.h"
#include "../../World/ObjectLoaderManager.h"

namespace MythicalRuins {

    class PhysicsController : public SystemCore {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnLateUpdate() override;
        void OnDisable() override;
        void OnDestroy() override;

        bool CanMove(Object* obj, Vector2 newPos);
        bool LayersCollide(const Object* a, const Object* b);
    private:

        ObjectLoaderManager* m_ObjectLoader = nullptr;
    };

} // MythicalRuins

#endif //PHYSICSCONTROLLER_H
