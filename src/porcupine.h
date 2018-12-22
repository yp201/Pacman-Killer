#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine {
public:
    Porcupine() {}
    Porcupine(float x, float y, int count,float speed);
    glm::vec3 position;
    int count;
    float speed;
    bool alive;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *porc;

};

#endif // PORCUPINE_H
