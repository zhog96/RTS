#pragma once
#include <SFML/System.hpp>

class Time {
private:
    static sf::Clock clock;
public:
    static int delta;
    static int time;

    static int update();
    static int staticUpdate();
};
