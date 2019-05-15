#include "Interface.hpp"

#include <stdio.h>
#include <string>
#include <iostream>
#include <TGUI/TGUI.hpp>

#include "Scheme/Shemes.h"
#include "UIinformation.h"
#include "Scheme/MenuSheme.h"
#include "Scheme/PlaySheme.h"
#include "Time.h"

int Interface::initInterface() {

}

int Interface::run() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "TGUI window");
    UIinformation::window = &window;
    UIinformation::window->setVerticalSyncEnabled(true);
    tgui::Gui gui(window);
    UIinformation::gui = &gui;
    Shemes::loadTextures();
    window.setFramerateLimit(60);

    void (*update)() = nullptr;

    // Main loop
    while (window.isOpen())
    {
        UIinformation::mPos = sf::Vector2f(sf::Mouse::getPosition(window));

        for(int i = 0; i < 256; i++) {
            if(!UIinformation::bPressed[i]) UIinformation::bClicked[i] = false;
        }
        for(int i = 0; i < 2; i++) {
            if(!UIinformation::mPressed[i]) UIinformation::mClicked[i] = false;
        }
        for(int i = 0; i < 2; i++) {
            if(!UIinformation::mPressed[i]) UIinformation::mLastPressed[i] = UIinformation::mPos;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {

            // When the window is closed, the application ends
            if (event.type == sf::Event::Closed)
                window.close();
                // When the window is resized, the view is changed
            else if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
                gui.setView(window.getView());
            } else if (event.type == sf::Event::KeyPressed) {
                //printf("Keyboard::Pressed: %d\n", event.key.code);
                if(0 <= event.key.code < 256) {
                    UIinformation::bPressed[event.key.code] = true;
                    UIinformation::bClicked[event.key.code] = false;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                if(0 <= event.key.code < 256) {
                    if(UIinformation::bPressed[event.key.code]) {
                        UIinformation::bClicked[event.key.code] = true;
                    }
                    UIinformation::bPressed[event.key.code] = false;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                //printf("Mouse::Pressed: %d\n", event.key.code);
                if(0 <= event.key.code < 2) {
                    UIinformation::mPressed[event.key.code] = true;
                    UIinformation::mClicked[event.key.code] = false;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if(0 <= event.key.code < 2) {
                    if(UIinformation::mPressed[event.key.code]) {
                        UIinformation::mClicked[event.key.code] = true;
                    }
                    UIinformation::mPressed[event.key.code] = false;
                }
            }

            // Pass the event to all the widgets
            gui.handleEvent(event);
        }

        for(int i = 0; i < 2; i++) {
            if(UIinformation::mClicked[i]) {
                UIinformation::mDeltaClick[i] = UIinformation::mPos - UIinformation::mLastClick[i];
                UIinformation::mLastClick[i] = UIinformation::mPos;
                //printf("%f %f\n", UIinformation::mDeltaClick[0].x, UIinformation::mDeltaClick[0].y);
            }
            if(UIinformation::mPressed[i]) {
                UIinformation::mDeltaPressed[i] = UIinformation::mPos - UIinformation::mLastPressed[i];
                UIinformation::mLastPressed[i] = UIinformation::mPos;
                //printf("%f %f\n", UIinformation::mDeltaPressed[0].x, UIinformation::mDeltaPressed[0].y);
            } else {
                UIinformation::mDeltaPressed[i] = sf::Vector2f(0.f, 0.f);
            }
        }

        Time::update();
        if(update != nullptr) update();

        switch (Shemes::shemeChange) {
            case ShemesEnum::None :
                break;
            case ShemesEnum::Menu :
                try
                {
                    Shemes::cleanShemes();
                    update = MenuSheme::update;
                    MenuSheme::loadSheme();
                }
                catch (const tgui::Exception& e)
                {
                    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                    return 1;
                }
                break;
            case ShemesEnum::Play :
                try
                {
                    Shemes::cleanShemes();
                    update = PlaySheme::update;
                    PlaySheme::loadSheme();
                }
                catch (const tgui::Exception& e)
                {
                    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                    return 1;
                }
                break;
            case ShemesEnum::Exit :
                Shemes::elements.clear();
                gui.removeAllWidgets();
                window.close();
                break;
        }

        window.clear();

        // Draw all created widgets
        gui.draw();

        window.display();
    }
}
