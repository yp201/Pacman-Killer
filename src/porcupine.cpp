#include "porcupine.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;

Porcupine::Porcupine(float x, float y, int count,float speed) {
    this->position = glm::vec3(x, y, 0);
    this->count=count;
    this->speed=speed;
    this->alive=true;
    static  GLfloat porcupine[50];
    int j=0;
    for(int i=0;i<count;i++)
    {
      porcupine[j++]=i*0.1;porcupine[j++]=0;porcupine[j++]=0; 
      porcupine[j++]=(i+1)*0.1;porcupine[j++]=0.0;porcupine[j++]=0;
      porcupine[j++]=((i+1)*0.1 +(i*0.1))/2;porcupine[j++]=0.5;porcupine[j++]=0;
    }
    
    this->porc = create3DObject(GL_TRIANGLES, count*3,porcupine, {169,169,169}, GL_FILL);

}

void Porcupine::tick() {

    this->position.x=this->position.x-this->speed;
    if(this->position.x<=-4.1)
        this->speed=-this->speed;
    if(this->position.x+this->count*0.1>=4.1)
        this->speed=-this->speed;

}


void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0,0, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->porc);
}

