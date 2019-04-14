#include "Time.h"

sf::Clock Time::clock;
int Time::delta = 0;
int Time::time = clock.getElapsedTime().asMicroseconds();
int Time::update() {
    delta = clock.getElapsedTime().asMicroseconds() - time;
    time = clock.getElapsedTime().asMicroseconds();
}
int Time::staticUpdate() {
    delta = clock.getElapsedTime().asMicroseconds() - time;
}

