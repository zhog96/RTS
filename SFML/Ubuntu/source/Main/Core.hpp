#pragma once

#include <SFML/Graphics.hpp>
#include "source/Tools/Queue.hpp"

class Core {
public:
    static bool stoped;

    static int initCore();
    static int run();
    static int stop();
};
