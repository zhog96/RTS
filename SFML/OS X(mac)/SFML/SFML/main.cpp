#include <stdio.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

// This class is not for using, fun only
class SomeAnimation {
    sf::Sprite& sprite;
    sf::Vector2<int> tileSize;
    int cadr = 0;
    int line = 0;
    int micros;
    int cadrCount;
    int microsPerCadr;
    bool freeze = true;
public:
    SomeAnimation(sf::Texture& texture, sf::Vector2<float> position, sf::IntRect texture_rect, int microsPerCadr, int cadrCount) : sprite(* (new sf::Sprite(texture))) {
        sprite.setPosition(position);
        sprite.setTextureRect(texture_rect);
        sprite.setScale(3.0, 3.0);
        tileSize = sf::Vector2<int>(texture_rect.width, texture_rect.height);
        this->cadrCount = cadrCount;
        this->microsPerCadr = microsPerCadr;
    }
    
    void move(sf::Vector2<float> dr) {
        sprite.setPosition(sprite.getPosition() + dr);
    }
    
    void changeLine(int line) {
        this->line = line;
    }
    
    void setFreeze(bool freeze) {
        this->freeze = freeze;
    }
    
    void update(sf::Time dt) {
        if(!freeze) {
            micros += dt.asMicroseconds();
            micros %= cadrCount * microsPerCadr;
            cadr = micros / microsPerCadr;
        }
    }
    
    void draw(sf::RenderWindow& window) {
        sprite.setTextureRect(sf::IntRect(tileSize.x * cadr, tileSize.y * line, tileSize.x, tileSize.y));
        window.draw(sprite);
    }
};

// This class is not for using, fun only
class SomeThing {
    SomeAnimation& animation;
    float speed;
public:
    SomeThing(SomeAnimation& animation) : animation(* (new SomeAnimation(animation))) {
        speed = 350.0;
    }
    
    void update(sf::Time dt) {
        float dx = 0.0, dy = 0.0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dy -= dt.asMicroseconds() * (speed / 1000000);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dy += dt.asMicroseconds() * (speed / 1000000);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dx -= dt.asMicroseconds() * (speed / 1000000);
            dy = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dx += dt.asMicroseconds() * (speed / 1000000);
            dy = 0;
        }
        
        if(dy > 0) animation.changeLine(0);
        if(dx < 0) animation.changeLine(1);
        if(dx > 0) animation.changeLine(2);
        if(dy < 0) animation.changeLine(3);
        if(dx * dx + dy * dy == 0) animation.setFreeze(true);
        else animation.setFreeze(false);
        
        animation.move(sf::Vector2<float>(dx, dy));
        animation.update(dt);
    }
    
    void draw(sf::RenderWindow& window) {
        animation.draw(window);
    }
};

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");

    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "image.axd.png")) {
        return EXIT_FAILURE;
    }
    
    SomeAnimation animation(texture, sf::Vector2<float>(100.0, 100.0), sf::IntRect(0, 0, 107, 106), 150000, 3);
    SomeThing something(animation);
    
    sf::Clock deltaClock;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        sf::Time dt = deltaClock.restart();
        
        something.update(dt);
        
        window.clear();
        
        something.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}
