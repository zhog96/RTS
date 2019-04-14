#include "UIObject.hpp"
#include "UIinformation.h"

UIObject::UIObject(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds) {
    this->id = id;
    this->drawIds = *drawIds;
    if(textIds == NULL) this->textIds = std::vector<sf::Vector2i>();
    else this->textIds = *textIds;
    forDelete = false;
}

int UIObject::destructed() {
    return forDelete;
}