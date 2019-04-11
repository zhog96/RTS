#include "FunnyButton.h"
#include "source/Tools/DrawArray.h"
#include <math.h>

int FunnyButton::motion() {
    if(focused) {
        double dt = Time::delta / 1000.0;
        sf::Vector2<float> newPos = sf::Vector2f(pos) + sf::Vector2<float>(3 * sin(phi), 3 * sin(phi));
        phi += 0.01 * dt;
        if(phi > 1000.0 || phi < -1000.0) phi = asin(sin(phi));
        DrawArray::update(drawIds[0], newPos);
    } else {
        sf::Vector2<float> newPos = sf::Vector2f(pos);
        DrawArray::update(drawIds[0], newPos);
    }
}

FunnyButton::FunnyButton(int id, std::vector<sf::Vector2i> &drawIds, sf::IntRect size) : Button(id, drawIds, size) {
    pos = sf::Vector2<double>(DrawArray::getPos(drawIds[0]));
    phi = 0;
}