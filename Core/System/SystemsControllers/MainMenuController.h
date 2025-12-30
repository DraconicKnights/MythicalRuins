#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

#include <cstdint>
#include <string>
#include <vector>
#include "../SystemCore.h"

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

    class MainMenuController : public SystemCore  {
    public:
        void OnStart() override;
        void OnUpdate() override;

        void BuildUI();

        MenuPage GetPage() const { return m_Page; }
        void SetPage(MenuPage menuPage) { m_Page = menuPage; }

    private:
        MenuPage m_Page = MenuPage::Home;

        VideoSettings m_AppliedVideo{};
        VideoSettings m_PendingVideo{};

        char m_Ip[64] = "127.0.0.1";
        int  m_Port = 7777;
        NetStatus m_NetStatus = NetStatus::Idle;
        char m_NetError[128] = "";

        std::vector<ServerInfo> m_Servers;
        int m_SelectedServer = -1;

    private:
        void DrawSidebar();
        void DrawHome();
        void DrawSettings();
        void DrawHost();
        void DrawJoin();
        void DrawServers();

        void ApplyVideoSettings();
        void RevertPendingVideo();
        bool ValidatePort(int port, const char* contextLabel);

        const char* NetStatusToString(NetStatus s) const;
    };

} // MyhticalRuins

#endif //MAINMENUCONTROLLER_H
