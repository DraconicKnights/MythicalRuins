#include "PhysicsController.h"
#include "../../Application.h"
#include "../../Render/Object/Object.h"

void MythicalRuins::PhysicsController::OnStart() {

}

void MythicalRuins::PhysicsController::OnUpdate() {

}

void MythicalRuins::PhysicsController::OnFixedUpdate() {

}

void MythicalRuins::PhysicsController::OnLateUpdate() {

}

void MythicalRuins::PhysicsController::OnDestroy() {

}

bool MythicalRuins::PhysicsController::CanMove(MythicalRuins::Object* obj, Vector2 newPos) {
    Rectangle newBounds = {
            newPos.x,
            newPos.y,
            obj->Size.x,
            obj->Size.y
    };

    auto* app = MythicalRuins::Application::Get();
    if (!app) return false;

    auto& objectCtr = app->GetObjectController();

    for (const auto& otherPtr : objectCtr.GetAllObjects()) {
        Object* other = otherPtr.get();

        if (other == obj) continue;

        if (other->IsTrigger) {
            bool overlapping = CheckCollisionRecs(newBounds, other->Bounds());
            bool wasOverlapping = obj->GetPrevTriggers().contains(other);

            if (overlapping && !wasOverlapping) {
                // ENTER
                obj->OnTriggerEnter(other);
                other->OnTriggerEnter(obj);
                obj->GetPrevTriggers().insert(other);
            }
            else if (overlapping && wasOverlapping) {
                // STAY
                obj->OnTriggerStay(other);
                other->OnTriggerStay(obj);
            }
            else if (!overlapping && wasOverlapping) {
                // EXIT
                obj->OnTriggerExit(other);
                other->OnTriggerExit(obj);
                obj->GetPrevTriggers().erase(other);
            }

            continue;
        }

        if (!other->Collidable) continue;
        if (!LayersCollide(obj, other)) continue;


        if (CheckCollisionRecs(newBounds, other->Bounds())) {
            return false;
        }
    }

    return true;
}

// Going to be honest this is more experimental atm
bool MythicalRuins::PhysicsController::LayersCollide(const MythicalRuins::Object *a, const MythicalRuins::Object *b) {
    return (a->CollisionLayer & b->CollisionMask) != 0 &&
           (b->CollisionLayer & a->CollisionMask) != 0;
}
