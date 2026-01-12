#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include "../Render/Object/Object.h"
#include "../System/Singleton.h"

namespace MythicalRuins {

    class ObjectLoaderManager : public Singleton<ObjectLoaderManager> {
    public:
        template<typename T, typename... Args>
        T& Spawn(Args&&... args) {
            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *ptr;
            m_Objects.emplace_back(std::move(ptr));
            return ref;
        }

        const std::vector<std::unique_ptr<Object>>& GetAllObjects() const { return m_Objects; }
    private:
        std::vector<std::unique_ptr<Object>> m_Objects;
    };

} // MythicalRuins

#endif //WORLD_H
