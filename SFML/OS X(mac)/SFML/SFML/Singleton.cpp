#include "Singleton.hpp"

bool Singleton::IsCreated = false;

Singleton::Singleton() {
    if(IsCreated) return NULL;
    Singleton::IsCreated = true;
}

Singleton::~Singleton() {
    Singleton::IsCreated = false;
}
