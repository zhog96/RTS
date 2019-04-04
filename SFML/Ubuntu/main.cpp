#include <stdio.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <unistd.h>
#include <sys/types.h>

#include "Interface.hpp"
#include "Core.hpp"
#include "Queue.hpp"

Queue Core_Inter, Inter_Core;

Core core(Core_Inter, Inter_Core);
Interface interface(Inter_Core, Core_Inter);

void interfaceDaemon() {
    printf("interfaceDaemon start\n");
    interface.run();
    printf("interfaceDaemon stop\n");
}

void coreDaemon() {
    printf("coreDaemon start\n");
    core.run();
    printf("coreDaemon stop\n");
}

int main() {
    sf::Thread thread(&interfaceDaemon);
    thread.launch();
    sf::Thread thread2(&coreDaemon);
    thread2.launch();
    thread.wait();
    core.stop();
    thread2.wait();
    printf("main is done\n");
    return EXIT_SUCCESS;
}

