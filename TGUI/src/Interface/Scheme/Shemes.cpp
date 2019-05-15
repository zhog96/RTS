#include "Shemes.h"
#include "../UIinformation.h"

int Shemes::shemeChange = ShemesEnum::Menu;
std::vector<Button> Shemes::elements = std::vector<Button>();
std::vector<Button> Shemes::elementsPause = std::vector<Button>();
std::map<std::string, sf::Texture> Shemes::textures = std::map<std::string, sf::Texture>();

void Shemes::cleanShemes() {
    elements.clear();
    elementsPause.clear();
    UIinformation::gui->removeAllWidgets();
}

void Shemes::loadTextures() {
    //textures.emplace("button", sf::Texture());
    //textures["button"].loadFromFile("../images/button.png");
}