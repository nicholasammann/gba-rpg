#include "Title.hpp"

#include "SceneType.hpp"
#include "Visual/fixed_32x64_sprite_font.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_main_menu.h"
#include "bn_sprite_items_game_title.h"
#include "bn_sprite_items_menu_cursor.h"
#include "bn_sprite_text_generator.h"

constexpr bn::fixed TITLE_X = -116;
constexpr bn::fixed TITLE_Y = -34;
constexpr bn::fixed TITLE_SPACING = 28;

constexpr bn::fixed TEXT_X = -28;
constexpr bn::fixed TEXT_Y_ROOT = 34;
constexpr bn::fixed TEXT_Y_SPACING = 12;

Title::Title(bn::sprite_text_generator& textGenerator)
    : mPage(TitlePage::Home),
      mTargetPage(TitlePage::Home),
      mTargetScene(SceneType::Quit),
      mCursorSprite(bn::sprite_items::menu_cursor.create_sprite(0, 0)),
      mHugeTextGenerator(fixed_32x64_sprite_font),
      mTextGenerator(textGenerator) {
    bn::regular_bg_ptr titleBg = bn::regular_bg_items::main_menu.create_bg(0, 0);
    mBackground = bn::make_unique<SceneBackground>(titleBg);

    // Game Title
    mHugeTextGenerator.generate(TITLE_X, TITLE_Y, "F", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 1 * TITLE_SPACING, TITLE_Y, "O", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 2 * TITLE_SPACING, TITLE_Y, "R", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 3 * TITLE_SPACING, TITLE_Y, "S", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 4 * TITLE_SPACING, TITLE_Y, "O", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 5 * TITLE_SPACING, TITLE_Y, "O", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 6 * TITLE_SPACING, TITLE_Y, "T", mGameTitleSprites);
    mHugeTextGenerator.generate(TITLE_X + 7 * TITLE_SPACING, TITLE_Y, "H", mGameTitleSprites);

    // mTextGenerator.set_bg_priority(1);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT, "NEW GAME", mNewGameSprites);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + TEXT_Y_SPACING, "LOAD GAME", mLoadGameSprites);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + 2 * TEXT_Y_SPACING, "CREDITS", mCreditsSprites);
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + 3 * TEXT_Y_SPACING, "EXIT", mExitSprites);

    // Yes and No
    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT, "YES", mYesSprites);
    for (bn::sprite_ptr& sprite : mYesSprites) {
        sprite.set_visible(false);
    }

    mTextGenerator.generate(TEXT_X, TEXT_Y_ROOT + TEXT_Y_SPACING, "NO", mNoSprites);
    for (bn::sprite_ptr& sprite : mNoSprites) {
        sprite.set_visible(false);
    }

    // Set cursor to new game
    mCursorSprite.set_position(mNewGameSprites[0].x() - 22, mNewGameSprites[0].y());
    mCursorSprite.set_scale(0.6);
}

[[nodiscard]] bn::optional<SceneType> Title::Update() {
    bn::optional<SceneType> result;

    if (mCursorMoveAction) {
        mCursorMoveAction->update();

        if (mCursorMoveAction->done()) {
            mCursorMoveAction.reset();
        }
    } else if (mPage == TitlePage::Home) {
        if (bn::keypad::up_pressed() || bn::keypad::down_pressed()) {
            if (bn::keypad::up_pressed()) {
                if (mMenuIndex == HomeButtons::NewGame) {
                    mMenuIndex = HomeButtons::Exit;
                } else {
                    mMenuIndex -= 1;
                }
            } else {
                if (mMenuIndex == HomeButtons::Exit) {
                    mMenuIndex = HomeButtons::NewGame;
                } else {
                    mMenuIndex += 1;
                }
            }

            switch (mMenuIndex) {
                case HomeButtons::NewGame:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mNewGameSprites[0].y());
                    break;

                case HomeButtons::LoadGame:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mLoadGameSprites[0].y());
                    break;

                case HomeButtons::Credits:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mCreditsSprites[0].y());
                    break;

                case HomeButtons::Exit:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mExitSprites[0].y());
                    break;

                default:
                    BN_ERROR("Invalid menu index: ", mMenuIndex);
                    break;
            }
        } else if (bn::keypad::a_pressed()) {
            switch (mMenuIndex) {
                case HomeButtons::NewGame:
                    mTargetPage = TitlePage::NewGame;
                    break;
                case HomeButtons::LoadGame:
                    mTargetPage = TitlePage::LoadGame;
                    break;
                case HomeButtons::Credits:
                    mTargetPage = TitlePage::Credits;
                    break;
                case HomeButtons::Exit:
                    mTargetPage = TitlePage::Exit;
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mYesSprites[0].y());
                    break;
                default:
                    BN_ERROR("Invalid menu index: ", mMenuIndex);
                    break;
            }
        }
    } else if (mPage == TitlePage::NewGame) {
        if (bn::keypad::up_pressed() || bn::keypad::down_pressed()) {
            if (mMenuIndex == ConfirmationButtons::Yes) {
                mMenuIndex = ConfirmationButtons::No;
            } else {
                mMenuIndex = ConfirmationButtons::Yes;
            }

            switch (mMenuIndex) {
                case ConfirmationButtons::Yes:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mYesSprites[0].y());
                    break;

                case ConfirmationButtons::No:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mNoSprites[0].y());
                    break;

                default:
                    BN_ERROR("Invalid menu index: ", mMenuIndex);
                    break;
            }
        } else if (bn::keypad::a_pressed()) {
            switch (mMenuIndex) {
                case ConfirmationButtons::Yes:
                    mTargetScene = SceneType::Game;
                    break;
                case ConfirmationButtons::No:
                    mTargetPage = TitlePage::Home;
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mNewGameSprites[0].y());
                    break;
                default:
                    BN_ERROR("Invalid menu index: ", mMenuIndex);
                    break;
            }
        }
    } else if (mPage == TitlePage::Exit) {
        if (bn::keypad::up_pressed() || bn::keypad::down_pressed()) {
            if (mMenuIndex == ConfirmationButtons::Yes) {
                mMenuIndex = ConfirmationButtons::No;
            } else {
                mMenuIndex = ConfirmationButtons::Yes;
            }

            switch (mMenuIndex) {
                case ConfirmationButtons::Yes:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mYesSprites[0].y());
                    break;

                case ConfirmationButtons::No:
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mNoSprites[0].y());
                    break;

                default:
                    BN_ERROR("Invalid menu index: ", mMenuIndex);
                    break;
            }
        } else if (bn::keypad::a_pressed()) {
            switch (mMenuIndex) {
                case ConfirmationButtons::Yes:
                    mTargetPage = TitlePage::Home;
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mNewGameSprites[0].y());
                    break;
                case ConfirmationButtons::No:
                    mTargetPage = TitlePage::Home;
                    mCursorMoveAction.emplace(mCursorSprite, 3, mCursorSprite.x(), mNewGameSprites[0].y());
                    break;
                default:
                    BN_ERROR("Invalid menu index: ", mMenuIndex);
                    break;
            }
        }
    }

    // Change page if target page is different than our current page
    if (mTargetPage != mPage) {
        // Hide + disable current sprites
        SetPageSpritesVisibility(mPage, false);

        // Show + enable target sprites
        SetPageSpritesVisibility(mTargetPage, true);

        mPage = mTargetPage;
        mMenuIndex = 0;
    }

    return result;
}

void Title::SetPageSpritesVisibility(TitlePage page, bool isVisible) {
    switch (page) {
        case TitlePage::Home:
            for (bn::sprite_ptr& sprite : mGameTitleSprites) {
                sprite.set_visible(isVisible);
            }
            for (bn::sprite_ptr& sprite : mNewGameSprites) {
                sprite.set_visible(isVisible);
            }
            for (bn::sprite_ptr& sprite : mLoadGameSprites) {
                sprite.set_visible(isVisible);
            }
            for (bn::sprite_ptr& sprite : mCreditsSprites) {
                sprite.set_visible(isVisible);
            }
            for (bn::sprite_ptr& sprite : mExitSprites) {
                sprite.set_visible(isVisible);
            }
            break;
        case TitlePage::NewGame:
            for (bn::sprite_ptr& sprite : mYesSprites) {
                sprite.set_visible(isVisible);
            }
            for (bn::sprite_ptr& sprite : mNoSprites) {
                sprite.set_visible(isVisible);
            }
            break;
        case TitlePage::LoadGame:
            break;
        case TitlePage::Credits:
            break;
        case TitlePage::Exit:
            for (bn::sprite_ptr& sprite : mYesSprites) {
                sprite.set_visible(isVisible);
            }
            for (bn::sprite_ptr& sprite : mNoSprites) {
                sprite.set_visible(isVisible);
            }
            break;
        default:
            BN_ERROR("Invalid page: ", static_cast<int>(page));
            break;
    }
}
