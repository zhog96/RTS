#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "../Element/Button.h"

class MenuSheme {
private:
    static void play();
    static void exit();
public:
    static void update();
    static void loadSheme();
};
