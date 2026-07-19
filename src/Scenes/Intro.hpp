#pragma once

#include <string>

#include "bn_unique_ptr.h"
#include "bn_vector.h"

#include "Scene.hpp"
#include "SceneBackground.hpp"
#include "TimedSceneBackground.hpp"

constexpr int IntroBackgroundCount = 3;

class Intro : public Scene {
public:
    Intro();

    Intro(SceneType targetScene);

    void AddBackground(bn::unique_ptr<TimedSceneBackground> background);

    [[nodiscard]] virtual bn::optional<SceneType> Update();

private:
    bn::vector<bn::unique_ptr<TimedSceneBackground>, IntroBackgroundCount> mBackgrounds;
    int mCurrentBackgroundIndex;

    SceneType mTargetScene;
};
