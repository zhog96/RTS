#include "FunnyButton.h"
#include "source/UIObjects/DrawArray.h"
#include <math.h>

int FunnyButton::motion() {
    if(focused) {
        double dt = Time::delta / 1000.0;
        sf::Vector2<float> newPos = sf::Vector2f(pos) + sf::Vector2<float>(3 * sin(phi), 3 * sin(phi));
        sf::Vector2<float> newTextPos = sf::Vector2f(textpos) + sf::Vector2<float>(1.5 * sin(phi), 1.5 * sin(phi));
        phi += 0.01 * dt;
        if(phi > 1000.0 || phi < -1000.0) phi = asin(sin(phi));
        DrawArray::update(drawIds[0], newPos);
        DrawArray::updateText(textIds[0], newTextPos);
    } else {
        DrawArray::update(drawIds[0], sf::Vector2f(pos));
        DrawArray::updateText(textIds[0], sf::Vector2f(textpos));
    }
}

FunnyButton::FunnyButton(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds) : Button(id, drawIds, textIds) {
    phi = 0;
}