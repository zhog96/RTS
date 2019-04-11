#include "UIObject.hpp"
#include "UIinformation.h"

UIObject::UIObject(int id, std::vector<sf::Vector2i> &drawIds, sf::IntRect size) {
    this->size = size;
    this->id = id;
    this->drawIds = drawIds;
}