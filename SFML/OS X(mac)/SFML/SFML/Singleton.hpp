#pragma once

#include <stdio.h>

//Класс, наследники которого могут существовать лишь в единственном экземпляре
class Singleton {
private:
    static bool IsCreated;
public:
    Singleton();
    ~Singleton();
};
