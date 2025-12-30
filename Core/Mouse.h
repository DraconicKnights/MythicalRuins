#ifndef MOUSE_H
#define MOUSE_H

#include "raylib.h"

namespace MythicalRuins {
    class Mouse {
    public:
        Vector2 Position() const { return GetMousePosition(); }
        Vector2 Delta() const { return GetMouseDelta(); }
        float WheelDelta() const { return GetMouseWheelMove(); }
    };
}

#endif //MOUSE_H
