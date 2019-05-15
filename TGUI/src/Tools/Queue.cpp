#include "Queue.hpp"

int Queue::top() {
    m.lock();
    int ret = q.front();
    m.unlock();
    return ret;
}

void Queue::pop() {
    m.lock();
    q.pop();
    m.unlock();
}

void Queue::push(int obj) {
    m.lock();
    q.push(obj);
    m.unlock();
}


bool Queue::isEmpty() {
    m.lock();
    bool res = q.empty();
    m.unlock();
    return res;
}
