#include "main.h"

#ifndef TRAMPOLIN_H
#define TRAMPOLIN_H


class Trampolin {
public:
    Trampolin() {}
    Trampolin(float x, float y, color_t color, float radius);
    glm::vec3 position;

    void draw(glm::mat4 VP);
private:
    VAO *rect1;
    VAO *rect2;
    VAO *semi;
};

#endif // TRAMPOLIN_H
