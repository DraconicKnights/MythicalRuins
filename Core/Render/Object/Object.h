#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cstdint>
#include <unordered_set>

namespace MythicalRuins {

    enum RenderLayer : int {
        Background = 0,
        Tiles = 100,
        Actors = 200,
        Foreground = 300
    };
    
    inline bool LayerBlockMovement(RenderLayer layer) {
        switch (layer) {
            case RenderLayer::Actors:
            case RenderLayer::Foreground:
                return true;
            case RenderLayer::Background:
            case RenderLayer::Tiles:
            default:
                return false;
        }
    }

    class Object {
    public:
        Vector2 Pos{0, 0};
        Vector2 Size{32, 32};

        virtual ~Object() = default;
        virtual void Update() {}
        virtual void Render() {}

        virtual void OnTrigger(Object* other) {}
        virtual void OnTriggerEnter(Object* other) {}
        virtual void OnTriggerStay(Object* other) {}
        virtual void OnTriggerExit(Object* other) {}

        int Layer = (int)RenderLayer::Actors;

        bool Collidable = false;
        bool IsTrigger = false;
        bool IsDynamic = false;

        uint32_t CollisionMask = 0xFFFFFFFF;
        uint32_t CollisionLayer = 1 << 0;

        Rectangle Bounds() const {
            return Rectangle{ Pos.x, Pos.y, Size.x, Size.y };
        }

        std::string GetName() { return m_Name; }
        void SetName(std::string name) { m_Name = name; }

        std::unordered_set<Object*>& GetPrevTriggers() { return m_PreviousTriggers; }

    private:
        std::string m_Name;
        std::unordered_set<Object*> m_PreviousTriggers;
    };
}

#endif //OBJECT_H
