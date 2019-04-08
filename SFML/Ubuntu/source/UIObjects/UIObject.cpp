#include "UIObject.hpp"
#include "UIinformation.h"

UIObject::UIObject(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size) {
    this->size = size;
    this->id = id;
    this->trans = trans;
    for(int i = 0; i < textures.size(); i++)
        sprites.push_back(sf::Sprite(*textures[i]));
    currSprite = NULL;
    focused = false;
}

int UIObject::draw() {
    if(currSprite) {
        UIinformation::window->draw(*currSprite, sf::RenderStates(trans));
    }
    return 0;
}