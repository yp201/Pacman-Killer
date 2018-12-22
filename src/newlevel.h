#include "main.h"

#ifndef NEWLEVEL_H
#define NEWLEVEL_H


class Newlevel {
public:
    Newlevel() {}
    Newlevel(float x, float);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *rectangle;
    VAO *triangle;


};

#endif // NEWLEVEL_H
