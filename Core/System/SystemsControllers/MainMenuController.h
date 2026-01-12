#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

#include <cstdint>
#include <string>
#include <vector>

#include "../SystemCore.h"
#include "raylib.h"

namespace MythicalRuins {

    enum class MenuPage : std::uint8_t { Home, Settings, Host, Join, Servers };
    enum class NetStatus : std::uint8_t { Idle, Hosting, Connecting, Connected, Error };

    struct VideoSettings {
        int  ResolutionIndex = 1;
        bool Fullscreen = false;
        int  TargetFps = 60;
    };

    struct ServerInfo {
        std::string Name;
        std::string Ip;
        int Port = 7777;
        int Players = 0;
        int MaxPlayers = 16;
        int Ping = 0;
    };

    class MainMenuController : public SystemCore {
    public:

        const char* GetName() override { return "MainMenuController"; }
    };

} // namespace MythicalRuins

#endif // MAINMENUCONTROLLER_H
