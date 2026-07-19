#include "Intro.hpp"
#include "SceneType.hpp"
#include "SceneBackground.hpp"

Intro::Intro() : mTargetScene(SceneType::Intro), mCurrentBackgroundIndex(0) {
}

Intro::Intro(SceneType targetScene) : mTargetScene(targetScene) {
}

void Intro::AddBackground(bn::unique_ptr<TimedSceneBackground> background) {
    BN_ASSERT(mBackgrounds.size() >= IntroBackgroundCount, "Trying to add Intro background when already at max number");
    mBackgrounds.push_back(std::move(background));
}

[[nodiscard]] bn::optional<SceneType> Intro::Update() {
    bn::optional<SceneType> result;

    if (mCurrentBackgroundIndex < mBackgrounds.size()) {
        if (mBackgrounds[mCurrentBackgroundIndex]->Update()) {
            ++mCurrentBackgroundIndex;
        }
    }
    else {
        result = mTargetScene;
    }

    return result;
}
