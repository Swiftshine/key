#include <revolution/OS.h>
#include "gfl/gfl.h"
#include "gfl/gflSound.h"
#include "fluff/game/Game.h"

void main(int argc, char* argv[]) {
    OSSetResetCallback(Game::OnReset);
    gfl::Init();
    gfl::SoundFadeCtrl::SetInstance(gfl::Sound::Instance()->GetSoundFadeCtrl());
    Game::Init();
    Game::Run();
    Game::Cleanup();
    gfl::SoundFadeCtrl::SetInstance(nullptr);
    gfl::Cleanup();
}