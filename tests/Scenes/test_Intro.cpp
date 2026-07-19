#include <gtest/gtest.h>

#include "Scenes/Intro.hpp"
#include "Scenes/SceneType.hpp"


/*

Intro
- Transition from first to last background after set amount of time
- Update should decrement internal timer by delta time
- Signal done from Intro update function after last background is finished


SceneBackground
- Constructed with one valid Butano background

SceneBackground-> TimedSceneBackground
- Internal timer, signal from update function when timer reaches 0
- LATER: Option for fade in/out over time (in update function)

*/


// GTest macro structure: TEST(TestSuiteName, TestName)
TEST(IntroTest, BackgroundTransitions) {
    Intro introScene;

    introScene.SetIntroText("MyIntroText");

    EXPECT_EQ("MyIntroText", introScene.GetIntroText());
}

TEST(IntroTest, SceneChange) {
    Intro introScene;
    
    EXPECT_FALSE(introScene.Update());
    
    introScene.SetIntroText("NextLevel");

    EXPECT_TRUE(introScene.Update()) << "Intro Scene change did not trigger after setting IntroText to NextLevel" << std::endl;
}
