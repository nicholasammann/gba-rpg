#include "SceneBackground.hpp"

SceneBackground::SceneBackground(bn::regular_bg_ptr butanoBackground) : mButanoBackground(butanoBackground) {
}

bn::regular_bg_ptr SceneBackground::GetButanoBackground() const {
    return mButanoBackground;
}
