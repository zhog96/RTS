#pragma once

#include <SFML/Graphics.hpp>
#include "Queue.hpp"

class Core {
private:
    bool stoped;
    Queue &q_Inter_out;
    Queue &q_Inter_in;
public:
    Core(Queue &q_Inter_out, Queue &q_Inter_in);
    int run();
    int stop();
};
