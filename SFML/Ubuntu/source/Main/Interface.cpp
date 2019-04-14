#include "Interface.hpp"

#include <stdio.h>
#include <string>
#include <SFML/System.hpp>

#include "source/UIObjects/UIinformation.h"
#include "source/Tools/Time.h"
#include "source/UIObjects/DrawArray.h"
#include "source/GameObjects/GameInformation.h"
#include "source/Scenes/GameScene.h"

sf::RenderWindow Interface::window;
Scene * Interface::scene = NULL;

/*
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct{
    float x,y,z;
}Vertex;

Vertex * Vertices;
GLuint myVBOID;

void initGL() {

    Vertices[0].x = 0.f;
    Vertices[0].y = 0.f;
    Vertices[0].z = 0.f;

    Vertices[1].x = 1.f;
    Vertices[1].y = 0.f;
    Vertices[1].z = 0.f;

    Vertices[2].x = 1.f;
    Vertices[2].y = 1.f;
    Vertices[2].z = 0.f;

    glGenBuffers(1, &myVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, myVBOID);
    glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), Vertices, GL_STATIC_DRAW);
    delete [] Vertices;
}

void drawGL() {
    glBindBuffer(GL_ARRAY_BUFFER, myVBOID);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}







//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


//trololo

int Interface::initInterface() {
    window.create(sf::VideoMode(1920, 1080), "SFML window");
    UIinformation::window = &window;
    scene = new MenuScene();
    //Check GPU, keyboard, ...
}

int Interface::run() {
    window.setFramerateLimit(60);

    Time::update();
    Time::update();
    while(window.isOpen()) {

        sf::Event event;
        sf::Mouse mouse;

        UIinformation::clicked = false;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    UIinformation::clicked = true;
                }
            }
        }

        UIinformation::mPos = sf::Vector2<double>(mouse.getPosition(window));

        Time::update();
        scene->process();

        /*if(!q_Core_in.isEmpty()) {
            int k = q_Core_in.top();
            q_Core_in.pop();
            printf("%d\n", k);
        }*/

        window.clear();
        DrawArray::draw();
        scene->draw();//???

        window.display();

        switch (scene->getChange()) {
            case UIinformation::Scenes::MenuScene:
                delete scene;
                DrawArray::clear();
                scene = new MenuScene();
                break;
            case UIinformation::Scenes::GameScene:
                delete scene;
                DrawArray::clear();
                scene = new GameScene();
                break;
            case UIinformation::Scenes::Exit:
                DrawArray::clear();
                GameInformation::IntCoreQ.push(ICMessage(ICMessage::typesI::endStep, -1, -1, -1, -1));
                window.close();
                break;
        }
    }
} //fporjgoijtrhoietjhoiejtwhoipwtjhpoitwjhpoiwjrhptiojopi

//geptoirjoijtrhoirjthoirjthoijhrio