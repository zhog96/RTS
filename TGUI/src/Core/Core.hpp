
#pragma once

#include "../Tools/Queue.hpp"

class Core {
public:
    static bool stoped;

    static int initCore();
    static int run();
    static int stop();
    //static int processMessage(ICMessage m);
};