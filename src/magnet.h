#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, float left, bool appear,int time);
    glm::vec3 position;
    float left;
    int time;
    float rotation;
    bool appear;
    void draw(glm::mat4 VP);
private:
    VAO *rect1;
    VAO *rect2;
    VAO *semi1;
    VAO *semi2;

};

#endif // MAGNET_H
