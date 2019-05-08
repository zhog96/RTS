
#pragma once

#include <SFML/Graphics.hpp>
#include "source/Tools/Queue.hpp"
#include "source/Tools/ICMessage.h"

class Core {
public:
    static bool stopped;

    static int initCore();
    static int run();
    static int stop();
    static int processMessage(ICMessage * m);
};