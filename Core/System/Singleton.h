#ifndef MYTHICALRUINS_SINGLETON_H
#define MYTHICALRUINS_SINGLETON_H

#include <stdexcept>

namespace MythicalRuins {
    template<typename T>
    class Singleton {
    public:
        static T* Get() { return G_Instance;}
        static void SetInstance(T* instance) {
            if (G_Instance && G_Instance != instance) {
                throw std::runtime_error("Singleton already set for this type");
            }
            G_Instance = instance;
        }

        static T& GetRef() {
            if (!G_Instance) throw std::runtime_error("Client Singleton Object Instance Not Set");
            return *G_Instance;
        }

    protected:
        Singleton() {
            SetInstance(static_cast<T*>(this));
        }

    private:
        static inline T* G_Instance = nullptr;
    };
}

#endif //MYTHICALRUINS_SINGLETON_H
