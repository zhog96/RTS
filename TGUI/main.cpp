#include <stdio.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <unistd.h>
#include <sys/types.h>

#include "src/Interface/Interface.hpp"
#include "src/Core/Core.hpp"
#include "src/Tools/Queue.hpp"

void interfaceDaemon() {
    Interface::initInterface();
    printf("interfaceDaemon start\n");
    Interface::run();
    printf("interfaceDaemon stop\n");
}

void coreDaemon() {
    Core::initCore();
    printf("coreDaemon start\n");
    Core::run();
    printf("coreDaemon stop\n");
}

int main() {
    sf::Thread thread(&interfaceDaemon);
    thread.launch();
    sf::Thread thread2(&coreDaemon);
    thread2.launch();
    thread.wait();
    Core::stop();
    thread2.wait();
    printf("main is done\n");
    //interfaceDaemon();
    return EXIT_SUCCESS;
}