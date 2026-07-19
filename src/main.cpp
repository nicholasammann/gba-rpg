#include "Scenes/Scene.hpp"
#include "Scenes/TimedSceneBackground.hpp"
#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_welcome_bg.h"
#include "bn_regular_bg_items_studio_bg.h"
#include "bn_regular_bg_items_game_title_bg.h"

#include "Scenes/SceneType.hpp"
#include "Scenes/Intro.hpp"
#include "bn_unique_ptr.h"
#include <cstdlib>

int main()
{
    bn::core::init();
    bn::optional<SceneType> nextScene = SceneType::Intro;

    bn::unique_ptr<Scene> scene = bn::make_unique<Intro>(SceneType::Quit);
    if (Intro* introScene = static_cast<Intro*>(scene.get())) {
        bn::regular_bg_ptr welcomeBg = bn::regular_bg_items::welcome_bg.create_bg(0, 0);
        introScene->AddBackground(bn::make_unique<TimedSceneBackground>(welcomeBg, 3));

        bn::regular_bg_ptr studioBg = bn::regular_bg_items::studio_bg.create_bg(0, 0);
        introScene->AddBackground(bn::make_unique<TimedSceneBackground>(studioBg, 4));

        bn::regular_bg_ptr gameTitleBg = bn::regular_bg_items::game_title_bg.create_bg(0, 0);
        introScene->AddBackground(bn::make_unique<TimedSceneBackground>(gameTitleBg, 5));
    }

    while(true)
    {
        // scene update, returns type of next scene if scene should be changed
        if (scene) {
            nextScene = scene->Update();
        }

        bn::core::update();

        // check return value of scene update
            // logic for switching to next scene

        if (nextScene) {
            switch(*nextScene) {
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
