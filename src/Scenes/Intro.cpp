#include "Intro.hpp"

#include "SceneBackground.hpp"
#include "SceneType.hpp"
#include "bn_regular_bg_items_game_title_bg.h"
#include "bn_regular_bg_items_studio_bg.h"
#include "bn_regular_bg_items_welcome_bg.h"

Intro::Intro() : mCurrentBackgroundIndex(0), mTargetScene(SceneType::Intro) {
    AddDefaultBackgrounds();
}

Intro::Intro(SceneType targetScene) : mTargetScene(targetScene) {
    AddDefaultBackgrounds();
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
    } else {
        result = mTargetScene;
    }

    return result;
}

void Intro::AddDefaultBackgrounds() {
    bn::regular_bg_ptr welcomeBg = bn::regular_bg_items::welcome_bg.create_bg(0, 0);
    AddBackground(bn::make_unique<TimedSceneBackground>(welcomeBg, 3));

    bn::regular_bg_ptr studioBg = bn::regular_bg_items::studio_bg.create_bg(0, 0);
    AddBackground(bn::make_unique<TimedSceneBackground>(studioBg, 4));

    bn::regular_bg_ptr gameTitleBg = bn::regular_bg_items::game_title_bg.create_bg(0, 0);
    AddBackground(bn::make_unique<TimedSceneBackground>(gameTitleBg, 5));
}
