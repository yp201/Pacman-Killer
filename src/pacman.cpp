#include "pacman.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;
Pacman::Pacman(float x, float y, color_t color,float radius,double acceleration,double speedx,double speedy,bool plank,double theta) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedx = speedx;
    this->speedy= speedy;
    this->initial=false;
    this->acceleration=acceleration;
    this->radius=radius;
    this->time=0;
    this->plank=plank;
    this->theta=theta;
    int full=300;
    if(plank)
        full=360;
        float X=0.0f,Y=radius;
        int j=0;
            static GLfloat vertex_buffer_data[301*9];
            X=(this->radius*sqrt(3)/2.0),Y=(this->radius*0.5);
            for(int i=0;i<=full;i++)
            {
                vertex_buffer_data[j++]=X;vertex_buffer_data[j++]=Y; vertex_buffer_data[j++]=0.0f;
                float x1=X,y1=Y;

                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_data[j++]=X; vertex_buffer_data[j++]=Y; vertex_buffer_data[j++]=0.0f;
                vertex_buffer_data[j++]=0.0f; vertex_buffer_data[j++]=0.0f;vertex_buffer_data[j++]=0.0f;

            }
            double l=0.5;

    GLfloat rectangle[] = {
        this->radius*cos(this->theta)- l*sin(this->theta), this->radius*sin(this->theta)+l*cos(this->theta), 0, // vertex 1
        this->radius*cos(this->theta)+ l*sin(this->theta), this->radius*sin(this->theta)-l*cos(this->theta), 0, // vertex 1
        (this->radius+0.05)*cos(this->theta)+ l*sin(this->theta), (this->radius+0.05)*sin(this->theta)-l*cos(this->theta) , 0, // vertex 2

        (this->radius+0.05)*cos(this->theta)+ l*sin(this->theta), (this->radius+0.05)*sin(this->theta)-l*cos(this->theta) , 0, // vertex 2
        (this->radius+0.05)*cos(this->theta)- l*sin(this->theta), (this->radius+0.05)*sin(this->theta)+l*cos(this->theta), 0, // vertex 1
        this->radius*cos(this->theta)- l*sin(this->theta), this->radius*sin(this->theta)+l*cos(this->theta), 0, // vertex 1
    };
            this->object = create3DObject(GL_TRIANGLES, (full+1)*3, vertex_buffer_data, color, GL_FILL);
            this->rect = create3DObject(GL_TRIANGLES, 6, rectangle, color, GL_FILL);

}

void Pacman::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0,0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->plank)
        draw3DObject(this->rect);

}


void Pacman::tick() {
    this->time+=1;
    if(this->initial)
    {
        this->speedy=this->initial-this->acceleration*this->time;
    }
    this->position.x += this->speedx;
    
}

bounding_box_t Pacman::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
