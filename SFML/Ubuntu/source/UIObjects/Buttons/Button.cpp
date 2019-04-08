#include "Button.hpp"

int Button::process() {
    sf::Vector2<double> pos(trans.getMatrix()[12], trans.getMatrix()[13]);
    // printf("Size = %lf, %lf", size.x, size.y);
    // printf("pos = %lf, %lf ; clPos = %lf, %lf\n", pos.x, pos.y, mPos.x, mPos.y);
    if(UIinformation::mPos.x <= pos.x + size.x && UIinformation::mPos.y <= pos.y + size.y && pos.x <= UIinformation::mPos.x && pos.y <= UIinformation::mPos.y) {
        if (UIinformation::clicked) UIinformation::events->push(SceneEvent(id, SceneEvent::Pressed));
        currSprite = &sprites[1];
        text.setFillColor(sf::Color::Yellow);
        focused = true;
    } else {
        currSprite = &sprites[0];
        text.setFillColor(sf::Color::White);
        focused = false;
    }

    motion();
}

int Button::motion() {
    printf("Button\n");
}

int Button::draw() {
    UIObject::draw();
    UIinformation::window->draw(text, sf::RenderStates(textTrans));
}

Button::Button(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::string text, sf::Transform textTrans, sf::Font *font) : UIObject(id, textures, trans, size) {
    printf("Created button, id : %d\n", id);
    currSprite = &sprites[0];
    this->text = sf::Text(text, *font, 60);
    this->textTrans = textTrans;

}