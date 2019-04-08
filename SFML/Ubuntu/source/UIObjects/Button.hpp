#pragma once
#include "UIObject.hpp"

class Button : public UIObject {
public:
    Button(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::string text, sf::Transform textTrans, sf::Font *font, std::queue<SceneEvent> &events, sf::RenderWindow &window) : UIObject(id, textures, trans, size, text, textTrans, font, events, window) {
        printf("Created button, id : %d\n", id);
        currSprite = &sprites[0];
    }
    
    int process(sf::Vector2<double> mPos, bool click) {
        sf::Vector2<double> pos(trans.getMatrix()[12], trans.getMatrix()[13]);
       // printf("Size = %lf, %lf", size.x, size.y);
       // printf("pos = %lf, %lf ; clPos = %lf, %lf\n", pos.x, pos.y, mPos.x, mPos.y);
        if(mPos.x <= pos.x + size.x && mPos.y <= pos.y + size.y && pos.x <= mPos.x && pos.y <= mPos.y) {
            if (click) events.push(SceneEvent(id, SceneEvent::Pressed));
            currSprite = &sprites[1];
            text.setFillColor(sf::Color::Yellow);
        } else {
            currSprite = &sprites[0];
            text.setFillColor(sf::Color::White);
        }
    }
};
