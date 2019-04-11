#include "Button.hpp"
#include "source/Tools/DrawArray.h"

int Button::process() {
    sf::Vector2<int> pos = DrawArray::getPos(drawIds[0]);
    if(UIinformation::mPos.x <= pos.x + size.width && UIinformation::mPos.y <= pos.y + size.height && pos.x <= UIinformation::mPos.x && pos.y <= UIinformation::mPos.y) {
        if (UIinformation::clicked) UIinformation::events->push(SceneEvent(id, SceneEvent::Pressed));
        focused = true;
    } else {
        focused = false;
    }
    motion();
}

int Button::motion() {
    //printf("Button\n");
}

Button::Button(int id, std::vector<sf::Vector2i> &drawIds, sf::IntRect size) : UIObject(id, drawIds, size) {}