#include "UIinformation.h"

bool UIinformation::bPressed[256];
bool UIinformation::bClicked[256];
bool UIinformation::mPressed[2];
bool UIinformation::mClicked[2];
long long UIinformation::mPressStart[2];
long long UIinformation::mClickTime[2];
float UIinformation::wheel = 0.0f;
int UIinformation::coreAmount = 1;
sf::Vector2f UIinformation::mDeltaClick[2];
sf::Vector2f UIinformation::mLastClick[2];
sf::Vector2f UIinformation::mDeltaPressed[2];
sf::Vector2f UIinformation::mLastPressed[2];
sf::Vector2f UIinformation::mPos = sf::Vector2f(0.0f, 0.0f);
sf::RenderWindow * UIinformation::window = nullptr;
tgui::Gui * UIinformation::gui = nullptr;