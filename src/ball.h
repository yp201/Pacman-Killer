#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, float radius,double acceleration, double speedx,double speedy);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x,float y, float left,bool appear);
    double speedx;
    double speedy;
    double acceleration;
    double accelerationx;
    double time;
    double initial;
    double initialx;
    float radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *sector1;
    VAO *sector2;
    VAO *sector3;
    VAO *sector4;
    VAO *sector5;
    VAO *sector6;
    VAO *temp;



};

#endif // BALL_H
