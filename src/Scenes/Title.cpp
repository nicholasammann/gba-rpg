#include "Title.hpp"

#include "SceneType.hpp"
#include "bn_regular_bg_items_main_menu.h"
#include "bn_sprite_items_menu_cursor.h"
#include "bn_sprite_text_generator.h"

constexpr bn::fixed TITLE_X = -20;
constexpr bn::fixed TITLE_Y = -34;

constexpr bn::fixed TEXT_X = -28;
constexpr bn::fixed TEXT_Y_ROOT = 34;
constexpr bn::fixed TEXT_Y_SPACING = 12;

Title::Title(bn::sprite_text_generator& textGenerator)
    : mTargetScene(SceneType::Quit),
      mCursorSprite(bn::sprite_items::menu_cursor.create_sprite(0, 0)),
      mHugeTextGenerator(fixed),
      mTextGenerator(textGenerator) {
    bn::regular_bg_ptr titleBg = bn::regular_bg_items::main_menu.create_bg(0, 0);
    mBackground = bn::make_unique<SceneBackground>(titleBg);

    (common::fixed_8x16_sprite_font);
    bigTextGenerator.set_bg_priority(1);

    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT, "NEW GAME", mNewGameSprites);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + TEXT_Y_SPACING, "LOAD GAME", mLoadGameSprites);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + 2 * TEXT_Y_SPACING, "CREDITS", mCreditsSprites);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + 3 * TEXT_Y_SPACING, "EXIT", mExitSprites);

    // Set cursor to new game
    mCursorSprite.set_position(mNewGameSprites[0].x() - 28, mNewGameSprites[0].y());
    mCursorSprite.set_scale(0.75);
}

[[nodiscard]] bn::optional<SceneType> Title::Update() {
    bn::optional<SceneType> result;

    if (false) {
        result = mTargetScene;
    }

    return result;
}
