#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <vector>
#include <utility>
#include "SystemCore.h"
#include "../../Utils/Logger.h"
#include "Singleton.h"

namespace MythicalRuins {

    class SystemManager : public Singleton<SystemManager> {
    public:
        template<typename T, typename ...Args>
        T& AddSystem(int priority, Args &&...args) {
            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            ptr->SetPriority(priority);

            T& ref = *ptr;
            m_Systems.emplace_back(std::move(ptr));

            Logger::logDebug(("New type registered under System Manager"));
            return ref;
        }

        void AddSystem(int priority,  std::unique_ptr<SystemCore> system) {
            system->SetPriority(priority);
            m_Systems.emplace_back(std::move(system));
            Logger::logDebug("New type registered under System Manager");
        }

        template<typename T>
        T* GetSystem() {
            for (auto& system : m_Systems) {
                if (T* casted = dynamic_cast<T*>(system.get()))
                    return casted;
            }
            return nullptr;
        }

        template<typename T>
        const T* GetSystem() const {
            for (const auto& system : m_Systems) {
                if (const T* casted = dynamic_cast<const T*>(system.get()))
                    return casted;
            }

            return nullptr;
        }

        template<typename T>
        bool SystemRegistered() const {
            return GetSystem<T>() != nullptr;
        }

        void StartAll();
        void EnableAll();
        void UpdateAll();
        void FixedUpdateAll();
        void LateUpdateAll();
        void DisableAll();
        void DestroyAll();

    private:
        void SortByPriority() {
            std::sort(m_Systems.begin(), m_Systems.end(),
                      [](const auto& a, const auto& b) {
                          return a->Priority() < b->Priority();
            });
        }

        std::vector<std::unique_ptr<SystemCore>> m_Systems;
    };

} // MythicalRuins

#endif //SYSTEMMANAGER_H
