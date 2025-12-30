#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <vector>
#include <utility>
#include "SystemCore.h"
#include "../../Utils/Logger.h"

namespace MythicalRuins {

    class SystemManager {
    public:
        template<typename T, typename ...Args>
        T& AddSystem(Args &&...args) {
            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *ptr;
            m_Systems.emplace_back(std::move(ptr));
            Logger::logDebug(("New type registered under System Manager"));
            return ref;
        }

        void StartAll();
        void UpdateAll();
        void FixedUpdateAll();
        void LateUpdateAll();
        void DestroyAll();

    private:
        std::vector<std::unique_ptr<SystemCore>> m_Systems;
    };

} // MythicalRuins

#endif //SYSTEMMANAGER_H
