#include "Button.hpp"
#include "source/UIObjects/DrawArray.h"

int Button::process() {
    sf::Vector2<int> pos = sf::Vector2i(DrawArray::getPos(drawIds[0]));
    sf::Vector2<int> size = DrawArray::getSize(drawIds[0]);
    if(UIinformation::mPos.x <= pos.x + size.x && UIinformation::mPos.y <= pos.y + size.y && pos.x <= UIinformation::mPos.x && pos.y <= UIinformation::mPos.y) {
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

Button::Button(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds) : UIObject(id, drawIds, textIds) {
    sf::Vector2i size = DrawArray::getSize(this->drawIds[0]);
    pos = sf::Vector2<double>(DrawArray::getPos((*drawIds)[0]));
    if (textIds->size() > 0) {
        sf::Vector2i textSize = DrawArray::getTextSize(this->textIds[0]);
        textpos = sf::Vector2<double>(sf::Vector2i(pos) + (size / 2 - textSize / 2));
        printf("%d %d\n", DrawArray::getTextSize(this->textIds[0]).x, textSize.y);
        DrawArray::updateText(this->textIds[0], sf::Vector2f(textpos));
    }
}
