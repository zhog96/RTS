#pragma once

#include <queue>

#include <SFML/System.hpp>

class Queue {
private:
    std::queue<int> q;
    sf::Mutex m;
public:
    int top();
    void pop();
    void push(int obj);
    bool isEmpty();
};
