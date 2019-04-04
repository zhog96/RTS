#include "Interface.hpp"

#include <stdio.h>
#include <string>

Interface::Interface(Queue &q_Core_out, Queue &q_Core_in) : q_Core_out(q_Core_out), q_Core_in(q_Core_in) {
    window.create(sf::VideoMode(1920, 1080), "SFML window");
    //Check GPU, keyboard, ...

    font.loadFromFile("fonts/font.ttf");
}

void Interface::MainMenu(int button, sf::Texture & textureBG, sf::Texture & textureB1, sf::Texture & textureB2) {
    //Background
    sf::Sprite spriteBG(textureBG);
    window.draw(spriteBG);

    //Title
    sf::Text title("RTS Main Menu", Interface::font, 150);
    title.setFillColor(sf::Color::Cyan);
    sf::Transform titleTranslate;
    titleTranslate.translate(400, 50);
    sf::RenderStates titleRS(titleTranslate);
    window.draw(title, titleRS);

    //Buttons
    sf::Sprite spriteB1(button?textureB2:textureB1), spriteB2(button?textureB1:textureB2);
    sf::Transform B1translate, B2translate;
    B1translate.translate(630, 400);
    B2translate.translate(630, 700);
    sf::RenderStates B1RS(B1translate), B2RS(B2translate);
    window.draw(spriteB1, B1RS);
    window.draw(spriteB2, B2RS);
    sf::Text textB1("Play", Interface::font, 60), textB2("Exit", Interface::font, 60);
    textB1.setFillColor(button?sf::Color::White:sf::Color::Yellow);
    textB2.setFillColor(!button?sf::Color::White:sf::Color::Yellow);
    sf::Transform trTextB1, trTextB2;
    trTextB1.translate(670, 450);
    trTextB2.translate(670, 750);
    sf::RenderStates textB1RS(trTextB1), textB2RS(trTextB2);
    window.draw(textB1, textB1RS);
    window.draw(textB2, textB2RS);
}

int Interface::run() {
    sf::Clock deltaClock;
    // state of the system : MainMenu, Game, ...
    enum {MainMenu, something_else};
    int state = MainMenu;

    // Main Menu variables
    int MainMenuButton = 0;
    sf::Texture MainMenuTextureBG, MainMenuTextureB1, MainMenuTextureB2;
    MainMenuTextureBG.loadFromFile("textures/MainMenu/MainMenuBG.jpg");
    MainMenuTextureB1.loadFromFile("textures/MainMenu/buttonPressed.png");
    MainMenuTextureB2.loadFromFile("textures/MainMenu/buttonNotPressed.png");

    while(window.isOpen()) {
        sf::Event event;
        sf::Mouse mouse;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                q_Core_out.push(event.key.code);
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (state == MainMenu && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)) {
                    MainMenuButton = !MainMenuButton;
                } else if (state == MainMenu && MainMenuButton == 1 && event.key.code == sf::Keyboard::Return) {
                    window.close();
                } else if (state == MainMenu && MainMenuButton == 0 && event.key.code == sf::Keyboard::Return) {
                    state = something_else;
                } else if (state == something_else && event.key.code == sf::Keyboard::Space) {
                    state = MainMenu;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mouse.getPosition(window).x < 1230 && mouse.getPosition(window).x > 630 && mouse.getPosition(window).y > 400 && mouse.getPosition(window).y < 600) {
                        state = something_else;
                    } else if (mouse.getPosition(window).x < 1230 && mouse.getPosition(window).x > 630 && mouse.getPosition(window).y > 700 && mouse.getPosition(window).y < 900) {
                        window.close();
                    }
                }
            }

        }

        if(!q_Core_in.isEmpty()) {
            int k = q_Core_in.top();
            q_Core_in.pop();
            printf("%d\n", k);
        }

        if (state == MainMenu) {
            if (mouse.getPosition(window).x < 1230 && mouse.getPosition(window).x > 630 && mouse.getPosition(window).y > 400 && mouse.getPosition(window).y < 600) {
                MainMenuButton = 0;
            } else if (mouse.getPosition(window).x < 1230 && mouse.getPosition(window).x > 630 && mouse.getPosition(window).y > 700 && mouse.getPosition(window).y < 900) {
                MainMenuButton = 1;
            }
            Interface::MainMenu(MainMenuButton, MainMenuTextureBG, MainMenuTextureB1, MainMenuTextureB2);
        } else if (state == something_else) {
            sf::Text title("Work in progress (kind of)\n Press ESC to close\n the window\n or SPACE to go back to\n main menu", Interface::font, 120);
            title.setFillColor(sf::Color::Green);
            sf::Transform titleTranslate;
            titleTranslate.translate(100, 50);
            sf::RenderStates titleRS(titleTranslate);
            window.draw(title, titleRS);
        }

        sf::Time dt = deltaClock.restart();
        window.display();
        window.clear();
    }
}
