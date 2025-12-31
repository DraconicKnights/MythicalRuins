#include <rlImGui.h>
#include "Player.h"
#include "../../../Application.h"

void  MythicalRuins::Player::Render() {
    DrawRectangleV(Pos, Size, DARKBLUE);
}

void MythicalRuins::Player::OnTrigger(Object* other) {
    Logger::logInfo("Player touched trigger: ");
}
