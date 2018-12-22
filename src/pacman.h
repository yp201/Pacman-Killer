#include "main.h"

#ifndef PACMAN_H
#define PACMAN_H


class Pacman {
public:
    Pacman() {}
    Pacman(float x, float y, color_t color, float radius,double acceleration, double speedx,double speedy,bool plank,double theta);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    double speedy;
    double acceleration;
    double time;
    double initial;
    double theta;
    float radius;
    bool plank;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *rect;


};

#endif // PACMAN_H
