#ifndef INPUTACTIONS_H
#define INPUTACTIONS_H

namespace MythicalRuins {

    enum class InputAction {
        // Movement and Player Actions
        MoveForward,
        MoveRight,
        MoveLeft,
        MoveBack,
        DeltaLeftClick,
        DeltaRightClick,

        // Debug Actions
        OpenDebugConsole,

        // Util Actions
        Quit
    };

} // namespace MythicalRuins

#endif //INPUTACTIONS_H
