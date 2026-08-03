#pragma once

#include "Scene.hpp"
#include "TimedSceneBackground.hpp"
#include "bn_unique_ptr.h"
#include "bn_vector.h"

constexpr int IntroBackgroundCount = 3;

class Intro : public Scene {
   public:
    Intro() = delete;
    Intro(const Intro& other) = delete;
    Intro& operator=(const Intro& other) = delete;

    Intro(SceneType targetScene);

    [[nodiscard]] virtual bn::optional<SceneType> Update();

   private:
    bn::vector<bn::unique_ptr<TimedSceneBackground>, IntroBackgroundCount> mBackgrounds;
    int mCurrentBackgroundIndex;

    SceneType mTargetScene;

    void AddBackground(bn::unique_ptr<TimedSceneBackground> background);
    void AddDefaultBackgrounds();
};
