#pragma once
#include <SFML/System.hpp>

class Time {
private:
    static sf::Clock clock;
public:
    static long long delta;
    static long long time;

    static long long update();
    static long long staticUpdate();
};
