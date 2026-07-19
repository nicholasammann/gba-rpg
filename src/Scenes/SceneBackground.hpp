#pragma once

#include "bn_regular_bg_ptr.h"

class SceneBackground {
public:
    SceneBackground(bn::regular_bg_ptr butanoBackground);
    bn::regular_bg_ptr GetButanoBackground() const;

protected:
    bn::regular_bg_ptr mButanoBackground;

};

