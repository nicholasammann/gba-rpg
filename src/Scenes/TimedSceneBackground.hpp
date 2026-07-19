#pragma once

#include "bn_timer.h"

#include "SceneBackground.hpp"

class TimedSceneBackground : public SceneBackground {
public:
    TimedSceneBackground(bn::regular_bg_ptr butanoBackground, uint64_t secondsToDisplay);

    [[nodiscard]] bool Update();

private:
    bn::timer mTimer;
    uint64_t mTicks;
    uint64_t mSecondsToDisplay;
    bool mIsFirstUpdate;

};

