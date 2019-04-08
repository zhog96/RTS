#include "UIinformation.h"

bool UIinformation::bPressed[255];
bool UIinformation::clicked = false;
sf::Vector2<double>  UIinformation::mPos;
std::queue<SceneEvent> * UIinformation::events = NULL;
sf::RenderWindow * UIinformation::window = NULL;