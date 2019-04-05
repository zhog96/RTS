#pragma once

class SceneEvent {
public:
    enum events {Pressed};
    int id, eCode;
    SceneEvent(int id, int eCode);
};
