#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class DrawArray {
private:
    static std::vector<std::vector<sf::Text>> texts;
public:
    const static int N;
    static std::vector<sf::VertexArray> layers;
    static std::vector<sf::Texture *> textures;

    static sf::Vector2i addToLayer(int layer, sf::IntRect rectPos, sf::IntRect rectText);
    static sf::Vector2i addToLayer(int layer, std::vector<sf::Vertex> &pos);
    static int erase(sf::Vector2i id);
    static int update(sf::Vector2i id, sf::Vector2f pos);
    static int setLayerTexture(int layer, sf::Texture *texture);
    static sf::Vector2f getPos(sf::Vector2i id);
    static sf::Vector2i getSize(sf::Vector2i id);
    static sf::IntRect getSourceRect(sf::Vector2i id);
    static int clear();
};
