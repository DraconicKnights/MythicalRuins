#ifndef SYSTEMCORE_H
#define SYSTEMCORE_H

namespace MythicalRuins {

    class SystemCore {
    public:
        virtual ~SystemCore() = default;

        virtual void OnStart() {}
        virtual void OnUpdate() {}
        virtual void OnFixedUpdate() {}
        virtual void OnLateUpdate() {}
        virtual void OnDestroy() {}

        bool IsEnabled() const { return Enabled; }
        void SetEnabled(bool v) { Enabled = v; }

        int Priority() const { return LoadPriority; }
        void SetPriority(int p) { LoadPriority = p; }

    private:
        bool Enabled = true;
        int LoadPriority = 0;
    };
}

#endif //SYSTEMCORE_H
