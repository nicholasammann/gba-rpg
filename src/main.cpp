#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_test_background.h"

int main()
{
    bn::core::init();
    
    bn::regular_bg_ptr regular_bg = bn::regular_bg_items::test_background.create_bg(0, 0);

    while(true)
    {
        // scene update, returns type of next scene if scene should be changed


        bn::core::update();


        // check return value of scene update
            // logic for switching to next scene
    }
}
