#ifndef DEBUGCONSOLECONTROLLER_H
#define DEBUGCONSOLECONTROLLER_H

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <deque>
#include <chrono>
#include <mutex>
#include <sstream>
#include "../SystemCore.h"
#include "imgui.h"
#include "../../../Utils/Logger.h"

namespace MythicalRuins {

    class DebugConsoleController : public SystemCore {
    public:

        void OnStart() override;
        void OnUpdate() override;
        void OnDestroy() override;

    private:
    };

} // MythicalRuins

#endif //DEBUGCONSOLECONTROLLER_H