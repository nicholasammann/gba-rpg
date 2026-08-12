#pragma once

#include "Scene.hpp"
#include "SceneBackground.hpp"
#include "bn_sprite_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_unique_ptr.h"
#include "bn_vector.h"

namespace bn {
class sprite_text_generator;
}

class Title : public Scene {
   public:
    Title() = delete;
    Title(const Title& other) = delete;
    Title& operator=(const Title& other) = delete;

    Title(bn::sprite_text_generator& textGenerator);

    [[nodiscard]] virtual bn::optional<SceneType> Update();

   private:
    enum class TitlePage { Home, NewGame, LoadGame, Credits, Exit };

    bn::unique_ptr<SceneBackground> mBackground;
    TitlePage mPage;
    TitlePage mTargetPage;
    SceneType mTargetScene;

    bn::sprite_ptr mCursorSprite;
    bn::optional<bn::sprite_move_to_action> mCursorMoveAction;

    enum HomeButtons { NewGame, LoadGame, Credits, Exit };

    int mMenuIndex = 0;

    bn::sprite_text_generator mHugeTextGenerator;
    bn::sprite_text_generator& mTextGenerator;
    bn::vector<bn::sprite_ptr, 10> mGameTitleSprites;
    bn::vector<bn::sprite_ptr, 6> mNewGameSprites;
    bn::vector<bn::sprite_ptr, 7> mLoadGameSprites;
    bn::vector<bn::sprite_ptr, 6> mCreditsSprites;
    bn::vector<bn::sprite_ptr, 4> mExitSprites;
    // submenu sprites here

    enum ConfirmationButtons { Yes, No };
    // yes + no confirmation
    bn::vector<bn::sprite_ptr, 3> mYesSprites;
    bn::vector<bn::sprite_ptr, 2> mNoSprites;

    void SetPageSpritesVisibility(TitlePage page, bool isVisible);
};
