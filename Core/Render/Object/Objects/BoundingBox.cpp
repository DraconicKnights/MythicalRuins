#include "BoundingBox.h"
#include "../../../../Utils/Logger.h"

void MythicalRuins::BoundingBox::Render() {
    DrawRectangleLines(
            (int)Pos.x,
            (int)Pos.y,
            (int)Size.x,
            (int)Size.y,
            RED
            );
}

void MythicalRuins::BoundingBox::OnTrigger(MythicalRuins::Object *other) {
    Logger::logInfo("BoundingBox Triggered by: ");
}

void MythicalRuins::BoundingBox::OnTriggerEnter(MythicalRuins::Object *other) {
    Logger::logInfo("BoundingBox Triggered by enter state: ");
}

void MythicalRuins::BoundingBox::OnTriggerExit(MythicalRuins::Object *other) {
    Logger::logInfo("BoundingBox Triggered by exit state: ");
}
