#include "Core.hpp"

Core::Core(Queue &q_Inter_out, Queue &q_Inter_in) : q_Inter_out(q_Inter_out), q_Inter_in(q_Inter_in) {
    stoped = false;
}

int Core::run() {
    while(!stoped) {
        //printf("Hey from Core\n");
        sf::sleep(sf::milliseconds(10));
        if(!q_Inter_in.isEmpty()) {
            int k = q_Inter_in.top();
            q_Inter_in.pop();
            k++;
            q_Inter_out.push(k);
        }
    }
}

int Core::stop() {
    stoped = true;
}
