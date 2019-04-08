#include "Core.hpp"

bool Core::stoped = false;

int Core::initCore() {}

int Core::run() {
    while(!stoped) {
        //printf("Hey from Core\n");
        sf::sleep(sf::milliseconds(30));
        /*if(!q_Inter_in.isEmpty()) {
            int k = q_Inter_in.top();
            q_Inter_in.pop();
            k++;
            q_Inter_out.push(k);
        }*/
    }
}

int Core::stop() {
    stoped = true;
}
