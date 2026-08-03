#include <cstdlib>

#include "Scenes/Intro.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/SceneType.hpp"
#include "Scenes/Title.hpp"
#include "Visual/common_fixed_8x16_sprite_font.h"
#include "Visual/common_fixed_8x8_sprite_font.h"
#include "Visual/common_variable_8x16_sprite_font.h"
#include "Visual/common_variable_8x8_sprite_font.h"
#include "bn_core.h"
#include "bn_sprite_text_generator.h"
#include "bn_unique_ptr.h"

int main() {
    bn::core::init();
    bn::optional<SceneType> nextScene = SceneType::Intro;

    // Text generators
    bn::sprite_text_generator smallTextGenerator(common::fixed_8x8_sprite_font);
    smallTextGenerator.set_bg_priority(1);
    // smallTextGenerator.set_center_alignment();

    bn::sprite_text_generator bigTextGenerator(common::fixed_8x16_sprite_font);
    bigTextGenerator.set_bg_priority(1);
    // bigTextGenerator.set_center_alignment();

    // Starting Scene = Intro
    // bn::unique_ptr<Scene> scene = bn::make_unique<Intro>(SceneType::Title);

    // Start on Title
    bn::unique_ptr<Scene> scene = bn::make_unique<Title>(bigTextGenerator);

    while (true) {
        if (scene) {
            nextScene = scene->Update();
        }

        bn::core::update();

        if (nextScene) {
            switch (*nextScene) {
                case SceneType::Intro:
                    scene.reset(new Intro(SceneType::Title));
                    break;
                case SceneType::Title:
                    scene.reset(new Title(bigTextGenerator));
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
