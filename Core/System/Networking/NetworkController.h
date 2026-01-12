#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <winsock.h>
#include <thread>
#include <vector>
#include <queue>
#include "../SystemCore.h"

namespace MythicalRuins {

    class NetworkController : public SystemCore {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnDestroy() override;

        const char* GetName() override { return "NetworkController"; }

    private:
    };

} // MysticalRuins

#endif //NETWORKCONTROLLER_H
