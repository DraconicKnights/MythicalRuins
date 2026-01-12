#ifndef INPUTEVENTLISTENER_H
#define INPUTEVENTLISTENER_H

#include <array>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include "InputActions.h"
#include "System/Singleton.h"

namespace MythicalRuins {

    class InputEventListener : public Singleton<InputEventListener> {
    public:

        void BindKey(InputAction action, int rayLibKey);
        void BindMouse(InputAction action, int mouseButton);
        bool Pressed(InputAction action) const;
        bool Down(InputAction action) const;
        bool Released(InputAction action) const;
        void OnPressed(InputAction action, std::function<void()> callback);

        void Update();

    private:
        struct EnumHash {
            template<typename T>
            std::size_t operator()(T t) const { return static_cast<std::size_t>(t); }
        };

        std::unordered_map<InputAction, int, EnumHash> m_KeyBindings;
        std::unordered_map<InputAction, int, EnumHash> m_MouseBindings;
        std::unordered_map<InputAction, std::vector<std::function<void()>>, EnumHash> m_PressedCallbacks;
    };

} // MythicalRuins

#endif //INPUTEVENTLISTENER_H
