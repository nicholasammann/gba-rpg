#pragma once

#include "bn_timers.h"
#include "TimedSceneBackground.hpp"

TimedSceneBackground::TimedSceneBackground(bn::regular_bg_ptr butanoBackground, uint64_t secondsToDisplay) : 
SceneBackground(butanoBackground),
mTicks(0),
mSecondsToDisplay(secondsToDisplay) {
}

[[nodiscard]] bool TimedSceneBackground::Update() {
    bool result = false;

    mTicks += mTimer.elapsed_ticks_with_restart();
    uint64_t seconds = mTicks / bn::timers::ticks_per_second();

    if (seconds >= mSecondsToDisplay) {
        result = true;
    }

    return result;
}