#include <SFML/Graphics.hpp>
#include <vector>

class DrawArray {
private:
    const static int N;
    static std::vector<sf::VertexArray> layers;
    static std::vector<sf::Texture *> textures;
public:
    static sf::Vector2i addToLayer(sf::Vector2i id, sf::IntRect rectPos, sf::IntRect rectText);
    static sf::Vector2i addToLayer(sf::Vector2i id, std::vector<sf::Vertex> &pos);
    static int update(sf::Vector2i id, sf::Vector2f pos);
    static int setLayerTexture(int layer, sf::Texture *texture);
    static sf::Vector2i getPos(sf::Vector2i id);
    static int draw();
};
