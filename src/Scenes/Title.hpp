#pragma once

#include "Scene.hpp"
#include "SceneBackground.hpp"
#include "bn_sprite_ptr.h"
#include "bn_unique_ptr.h"
#include "bn_vector.h"

namespace bn {
class sprite_text_generator;
}

enum class TitleState { TitleDisplay, MainMenu, QuitConfirmation };

class Title : public Scene {
   public:
    Title() = delete;
    Title(const Title& other) = delete;
    Title& operator=(const Title& other) = delete;

    Title(bn::sprite_text_generator& textGenerator);

    [[nodiscard]] virtual bn::optional<SceneType> Update();

   private:
    enum class TitlePages { Home, NewGame, LoadGame, Credits, Exit };

    bn::unique_ptr<SceneBackground> mBackground;
    TitleState mState;
    SceneType mTargetScene;

    bn::sprite_ptr mCursorSprite;
    int mMenuIndex = 0;

    bn::sprite_ptr mGameTitleSprite;

    bn::sprite_text_generator& mHugeTextGenerator;
    bn::sprite_text_generator& mTextGenerator;
    bn::vector<bn::sprite_ptr, 6> mGameTitleSprites;
    bn::vector<bn::sprite_ptr, 6> mNewGameSprites;
    bn::vector<bn::sprite_ptr, 7> mLoadGameSprites;
    bn::vector<bn::sprite_ptr, 6> mCreditsSprites;
    bn::vector<bn::sprite_ptr, 4> mExitSprites;
    // submenu sprites here
};
