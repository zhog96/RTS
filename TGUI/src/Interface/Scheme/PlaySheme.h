#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "../Element/Button.h"

class PlaySheme {
private:
    static bool paused;
    static void exit();
    static void unpause();
public:
    static void update();
    static void loadSheme();
};