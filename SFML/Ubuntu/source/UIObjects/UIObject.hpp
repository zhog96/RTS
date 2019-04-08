#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "UIObject.hpp"
#include "source/Scenes/SceneEvent.hpp"



class UIObject {
protected:
    std::queue<SceneEvent> &events;
    sf::Vector2<double> size;
    sf::Transform trans;
    std::vector<sf::Sprite> sprites;
    sf::Sprite *currSprite;
    sf::Text text;
    sf::Transform textTrans;
    sf::RenderWindow &window;
    int id;
public:
    UIObject(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::string text, sf::Transform textTrans, sf::Font *font,
            std::queue<SceneEvent> &events, sf::RenderWindow &window);
    int draw();
};
