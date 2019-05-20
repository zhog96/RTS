#include "Time.h"

sf::Clock Time::clock;
long long Time::delta = 0;
long long Time::time = clock.getElapsedTime().asMicroseconds();
long long Time::update() {
    delta = clock.getElapsedTime().asMicroseconds() - time;
    time = clock.getElapsedTime().asMicroseconds();
}
long long Time::staticUpdate() {
    delta = clock.getElapsedTime().asMicroseconds() - time;
}

