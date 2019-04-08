#include "UIObject.hpp"

UIObject::UIObject(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size,
        std::string text, sf::Transform textTrans, sf::Font *font,
        std::queue<SceneEvent> &events, sf::RenderWindow & window) : events(events), window(window){
    this->size = size;
    this->id = id;
    this->text = sf::Text(text, *font, 60);
    this->textTrans = textTrans;
    this->trans = trans;
    for(int i = 0; i < textures.size(); i++)
        sprites.push_back(sf::Sprite(*textures[i]));
    currSprite = NULL;
}

int UIObject::draw() {
    if(currSprite) {
        window.draw(*currSprite, sf::RenderStates(trans));
        window.draw(text, sf::RenderStates(textTrans));
    }
    return 0;
}