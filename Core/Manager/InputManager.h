#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include "../System/SystemCore.h"
#include "../InputEventListener.h"

namespace MythicalRuins {

    class InputManager : public SystemCore {
    public:

        void OnStart() override;
        void OnDisable() override;
        void OnDestroy() override;

    private:
        InputEventListener* m_InputListener = nullptr;
    };

} // MythicalRuins

#endif //INPUTMANAGER_H
