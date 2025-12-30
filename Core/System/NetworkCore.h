#ifndef NETWORKCORE_H
#define NETWORKCORE_H

#include <cstdint>
#include "SystemCore.h"

namespace MythicalRuins {

    class NetworkCore : public SystemCore {
    public:
        uint32_t NetId = 0;
        bool isOwner;

        virtual void OnNetworkSpawn() {}
        virtual void onNetworkDespawn() {}
    };
}

#endif //NETWORKCORE_H
