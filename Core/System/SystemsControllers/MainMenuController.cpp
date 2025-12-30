#include "MainMenuController.h"

#include <cstdio>
#include <cstring>

#include "imgui.h"
#include "raylib.h"
#include "../../Application.h"

namespace MythicalRuins {

    struct ResolutionOption {
        int w;
        int h;
        const char* label;
    };

    static constexpr ResolutionOption kResolutions[] = {
            { 1280,  720, "1280 x 720"  },
            { 1920, 1080, "1920 x 1080" },
            { 2560, 1440, "2560 x 1440" },
    };

    static ImVec4 kErrorColor() { return ImVec4(1.0f, 0.35f, 0.35f, 1.0f); }

    void MainMenuController::OnStart() {
        m_AppliedVideo.Fullscreen = IsWindowFullscreen();
        m_AppliedVideo.TargetFps = 60;
        m_AppliedVideo.ResolutionIndex = 1;

        m_PendingVideo = m_AppliedVideo;

        m_Servers = {
                {"Local Dev Server", "127.0.0.1", 7777, 1, 16, 12},
                {"Test Server EU",   "10.0.0.42",  7777, 4, 16, 35},
                {"Arena - US",       "192.168.0.9", 7777, 8, 16, 88},
        };
    }

    void MainMenuController::OnUpdate() {
    }

    const char* MainMenuController::NetStatusToString(NetStatus s) const {
        switch (s) {
            case NetStatus::Idle:       return "Idle";
            case NetStatus::Hosting:    return "Hosting";
            case NetStatus::Connecting: return "Connecting";
            case NetStatus::Connected:  return "Connected";
            case NetStatus::Error:      return "Error";
            default:                    return "Unknown";
        }
    }

    bool MainMenuController::ValidatePort(int port, const char* contextLabel) {
        if (port < 1 || port > 65535) {
            std::snprintf(m_NetError, sizeof(m_NetError), "%s: Port must be between 1 and 65535.", contextLabel);
            m_NetStatus = NetStatus::Error;
            return false;
        }
        if (m_Ip[0] == '\0') {
            std::snprintf(m_NetError, sizeof(m_NetError), "%s: IP cannot be empty.", contextLabel);
            m_NetStatus = NetStatus::Error;
            return false;
        }
        m_NetError[0] = '\0';
        if (m_NetStatus == NetStatus::Error) m_NetStatus = NetStatus::Idle;
        return true;
    }

    void MainMenuController::RevertPendingVideo() {
        m_PendingVideo = m_AppliedVideo;
    }

    void MainMenuController::ApplyVideoSettings() {
        SetTargetFPS(m_PendingVideo.TargetFps);

        const bool isFs = IsWindowFullscreen();
        if (m_PendingVideo.Fullscreen != isFs) {
            ToggleFullscreen();
        }

        // Apply windowed resolution only when NOT fullscreen
        if (!IsWindowFullscreen()) {
            const int idx = m_PendingVideo.ResolutionIndex;
            const int safeIdx = (idx < 0) ? 0 : (idx >= (int)(sizeof(kResolutions)/sizeof(kResolutions[0])) ? (int)(sizeof(kResolutions)/sizeof(kResolutions[0])) - 1 : idx);
            SetWindowSize(kResolutions[safeIdx].w, kResolutions[safeIdx].h);
            m_PendingVideo.ResolutionIndex = safeIdx;
        }

        m_AppliedVideo = m_PendingVideo;
    }

    void MainMenuController::DrawSidebar() {
        auto SelectPage = [&](const char* label, MenuPage page) {
            const bool selected = (m_Page == page);
            if (ImGui::Selectable(label, selected, 0, ImVec2(0, 28))) {
                m_Page = page;
            }
        };

        ImGui::TextUnformatted("Menu");
        ImGui::Separator();
        SelectPage("Home",     MenuPage::Home);
        SelectPage("Settings", MenuPage::Settings);
        SelectPage("Host",     MenuPage::Host);
        SelectPage("Join",     MenuPage::Join);
        SelectPage("Servers",  MenuPage::Servers);
    }

    void MainMenuController::DrawHome() {
        auto* app = Application::Get();
        ImGui::TextUnformatted("Welcome.");
        ImGui::Spacing();

        if (ImGui::Button("Start Game", ImVec2(-1, 36))) {
            app->SetGameState(GameState::Playing);
        }

        if (ImGui::Button("Quit", ImVec2(-1, 0))) {
            CloseWindow();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Text("FPS: %d", GetFPS());
        ImGui::Text("State: %s", app->IsPlaying() ? "Playing" : "Menu");
    }

    void MainMenuController::DrawSettings() {
        ImGui::TextUnformatted("Video");
        ImGui::Separator();

        // Resolution combo
        const char* resLabels[sizeof(kResolutions)/sizeof(kResolutions[0])] = {};
        for (int i = 0; i < (int)(sizeof(kResolutions)/sizeof(kResolutions[0])); ++i)
            resLabels[i] = kResolutions[i].label;

        ImGui::Combo("Resolution", &m_PendingVideo.ResolutionIndex, resLabels, IM_ARRAYSIZE(resLabels));
        ImGui::Checkbox("Fullscreen", &m_PendingVideo.Fullscreen);
        ImGui::SliderInt("Target FPS", &m_PendingVideo.TargetFps, 30, 240);

        ImGui::Spacing();
        if (ImGui::Button("Apply", ImVec2(120, 0))) {
            ApplyVideoSettings();
        }
        ImGui::SameLine();
        if (ImGui::Button("Revert", ImVec2(120, 0))) {
            RevertPendingVideo();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::TextUnformatted("Applied");
        ImGui::Text("Fullscreen: %s", m_AppliedVideo.Fullscreen ? "Yes" : "No");
        ImGui::Text("Target FPS: %d", m_AppliedVideo.TargetFps);
        ImGui::Text("Resolution: %s", kResolutions[m_AppliedVideo.ResolutionIndex].label);
    }

    void MainMenuController::DrawHost() {
        ImGui::TextUnformatted("Host a server");
        ImGui::Separator();

        ImGui::InputInt("Port", &m_Port);
        ImGui::Text("Status: %s", NetStatusToString(m_NetStatus));
        if (m_NetStatus == NetStatus::Error && m_NetError[0] != '\0') {
            ImGui::TextColored(kErrorColor(), "%s", m_NetError);
        }

        ImGui::Spacing();
        if (ImGui::Button("Start Host", ImVec2(-1, 0))) {
            // Placeholder: validate inputs then set status
            // will call NetworkSystem->StartHost(m_Port)
            std::strcpy(m_Ip, "0.0.0.0");
            if (ValidatePort(m_Port, "Host")) {
                m_NetStatus = NetStatus::Hosting;
                // Application::Get()->SetGameState(GameState::Playing);
            }
        }
    }

    void MainMenuController::DrawJoin() {
        ImGui::TextUnformatted("Join a server");
        ImGui::Separator();

        ImGui::InputText("IP", m_Ip, sizeof(m_Ip));
        ImGui::InputInt("Port", &m_Port);

        ImGui::Text("Status: %s", NetStatusToString(m_NetStatus));
        if (m_NetStatus == NetStatus::Error && m_NetError[0] != '\0') {
            ImGui::TextColored(kErrorColor(), "%s", m_NetError);
        }

        ImGui::Spacing();
        if (ImGui::Button("Join", ImVec2(-1, 0))) {
            // Placeholder: validate inputs then set status
            // will call NetworkSystem->Connect(m_Ip, m_Port)
            if (ValidatePort(m_Port, "Join")) {
                m_NetStatus = NetStatus::Connecting;
            }
        }
    }

    void MainMenuController::DrawServers() {
        ImGui::TextUnformatted("Servers");
        ImGui::Separator();

        if (ImGui::Button("Refresh", ImVec2(120, 0))) {
            // Will Call API for Refresh List
        }

        ImGui::Spacing();

        if (ImGui::BeginTable("servers_table", 5, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("IP");
            ImGui::TableSetupColumn("Players");
            ImGui::TableSetupColumn("Ping");
            ImGui::TableSetupColumn("Port");
            ImGui::TableHeadersRow();

            for (int i = 0; i < (int)m_Servers.size(); ++i) {
                const auto& s = m_Servers[i];

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                const bool selected = (m_SelectedServer == i);
                if (ImGui::Selectable(s.Name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns)) {
                    m_SelectedServer = i;
                }
                ImGui::TableNextColumn(); ImGui::Text("%s", s.Ip.c_str());
                ImGui::TableNextColumn(); ImGui::Text("%d/%d", s.Players, s.MaxPlayers);
                ImGui::TableNextColumn(); ImGui::Text("%d", s.Ping);
                ImGui::TableNextColumn(); ImGui::Text("%d", s.Port);
            }

            ImGui::EndTable();
        }

        ImGui::Spacing();

        const bool hasSelection = (m_SelectedServer >= 0 && m_SelectedServer < (int)m_Servers.size());
        if (!hasSelection) ImGui::BeginDisabled();

        if (ImGui::Button("Join Selected", ImVec2(-1, 0)) && hasSelection) {
            const auto& s = m_Servers[m_SelectedServer];
            std::snprintf(m_Ip, sizeof(m_Ip), "%s", s.Ip.c_str());
            m_Port = s.Port;
            m_Page = MenuPage::Join;
        }

        if (!hasSelection) ImGui::EndDisabled();
    }

    void MainMenuController::BuildUI() {
        auto* app = Application::Get();
        if (!app) return;

        if (app->GetGameState() != GameState::Menu) {
            ImGui::Begin("Debug");
            ImGui::Text("FPS: %d", GetFPS());
            ImGui::Text("dt: %.4f", app->GetEngineDT());
            ImGui::End();
            return;
        }

        // Centered, responsive menu
        ImGuiViewport* vp = ImGui::GetMainViewport();
        ImVec2 size = ImVec2(vp->WorkSize.x * 0.45f, vp->WorkSize.y * 0.55f);
        if (size.x < 520) size.x = 520;
        if (size.y < 360) size.y = 360;

        ImGui::SetNextWindowPos(vp->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(size, ImGuiCond_Always);

        ImGuiWindowFlags flags =
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoMove;

        ImGui::Begin("MythicalRuins", nullptr, flags);

        // Two-column layout: sidebar + content
        ImGui::Columns(2, "menu_columns", false);
        ImGui::SetColumnWidth(0, 150.0f);
        DrawSidebar();
        ImGui::NextColumn();

        ImGui::TextUnformatted("MythicalRuins");
        ImGui::Separator();
        ImGui::Spacing();

        switch (m_Page) {
            case MenuPage::Home:     DrawHome(); break;
            case MenuPage::Settings: DrawSettings(); break;
            case MenuPage::Host:     DrawHost(); break;
            case MenuPage::Join:     DrawJoin(); break;
            case MenuPage::Servers:  DrawServers(); break;
        }

        ImGui::Columns(1);
        ImGui::End();
    }

} // namespace MythicalRuins
