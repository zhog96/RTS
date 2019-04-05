#pragma once
#include "UIObject.hpp"

class Button : public UIObject {
public:
    Button(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::queue<SceneEvent> &events, sf::RenderWindow &window) : UIObject(id, textures, trans, size, events, window) {
        printf("Created button, id : %d\n", id);
        currSprite = &sprites[0];
    }
    
    int process(sf::Vector2<double> clPos) {
        sf::Vector2<double> pos(trans.getMatrix()[12], trans.getMatrix()[13]);
        if(clPos.x <= pos.x + size.x && clPos.y <= pos.y + size.y && pos.x <= clPos.x && pos.y <= clPos.y) {
            events.push(SceneEvent(id, SceneEvent::Pressed));
        }
        
    }
};
