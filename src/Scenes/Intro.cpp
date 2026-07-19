#include "Intro.hpp"
#include "SceneType.hpp"
#include "SceneBackground.hpp"

Intro::Intro() : mCurrentBackgroundIndex(0), mTargetScene(SceneType::Intro) {
}

Intro::Intro(SceneType targetScene) : mTargetScene(targetScene) {
}

void Intro::AddBackground(bn::unique_ptr<TimedSceneBackground> background) {
    BN_ASSERT(mBackgrounds.size() <= IntroBackgroundCount, "Trying to add Intro background when already at max number");
    background->GetButanoBackground().set_visible(false);
    mBackgrounds.push_back(std::move(background));
}

[[nodiscard]] bn::optional<SceneType> Intro::Update() {
    bn::optional<SceneType> result;

    if (mCurrentBackgroundIndex < mBackgrounds.size()) {
        // Make sure current background is visible
        mBackgrounds[mCurrentBackgroundIndex]->GetButanoBackground().set_visible(true);

        if (mBackgrounds[mCurrentBackgroundIndex]->Update()) {
            // Hide current background
            mBackgrounds[mCurrentBackgroundIndex]->GetButanoBackground().set_visible(false);

            // Move to next background
            ++mCurrentBackgroundIndex;
        }
    }
    else {
        result = mTargetScene;
    }

    return result;
}
