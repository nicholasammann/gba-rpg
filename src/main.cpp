#include "bn_core.h"

int main()
{
    bn::core::init();

    while(true)
    {
        // scene update, returns type of next scene if scene should be changed


        bn::core::update();


        // check return value of scene update
            // logic for switching to next scene
    }
}
