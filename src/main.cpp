#include <cstdlib>

#include "Scenes/Intro.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/SceneType.hpp"
#include "Scenes/TimedSceneBackground.hpp"
#include "bn_core.h"
#include "bn_regular_bg_items_game_title_bg.h"
#include "bn_regular_bg_items_studio_bg.h"
#include "bn_regular_bg_items_welcome_bg.h"
#include "bn_regular_bg_ptr.h"
#include "bn_unique_ptr.h"

int main() {
    bn::core::init();
    bn::optional<SceneType> nextScene = SceneType::Intro;

    bn::unique_ptr<Scene> scene = bn::make_unique<Intro>(SceneType::Quit);

    while (true) {
        if (scene) {
            nextScene = scene->Update();
        }

        bn::core::update();

        if (nextScene) {
            switch (*nextScene) {
                case SceneType::Intro:
                    break;
                case SceneType::Title:
                    break;
                case SceneType::Game:
                    break;
                case SceneType::Credits:
                    break;
                case SceneType::Quit:
                    BN_ERROR("QUIT GAME");
                    return 0;
                    break;
                default:
                    BN_ERROR("Invalid next scene: ", (int)*nextScene);
            }
        }
    }
}
