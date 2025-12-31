#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <winsock.h>
#include <thread>
#include "../SystemCore.h"

namespace MythicalRuins {

    struct ClientInfo {
        SOCKET socket;
        int playerIdentifier;
        std::thread clientThread;
        bool IsConnected;
    };

    class NetworkController : public SystemCore {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnDestroy() override;

        void Start();
        void Shutdown();
    };

} // MysticalRuins

#endif //NETWORKCONTROLLER_H
