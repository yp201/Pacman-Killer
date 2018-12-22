#include "magnet.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;

Magnet::Magnet(float x, float y, float left , bool appear,int time) {
    this->position = glm::vec3(x, y, 0);
    this->left=left;
    this->appear=appear;
    this->rotation=0;
    this->time=0;
     GLfloat semione[181*9];
     GLfloat semitwo[181*9];
        float X=left*0.0f,Y=left*0.6f;
        int j=0;
        for(int i=0;i<=180;i++)
        {
          semione[j++]=X;semione[j++]=Y; semione[j++]=0.0f;
          float x1=X,y1=Y;
          X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
          Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
          semione[j++]=X; semione[j++]=Y; semione[j++]=0.0f;
          semione[j++]=0.0f; semione[j++]=0.0f;semione[j++]=0.0f;
        }
         GLfloat rectangle1[] = {
        left*0.0,  0.6, 0, // vertex 1
        left*0.0,  0.4, 0, // vertex 2
        left*0.2,  0.4, 0, // vertex 3
        left*0.0,  0.6, 0, // vertex 1
        left*0.2,  0.6, 0, // vertex 2
        left*0.2,  0.4, 0 // vertex 1
    };
         GLfloat rectangle2[] = {
        left*0.0,  -0.6, 0, // vertex 1
        left*0.0,  -0.4, 0, // vertex 2
        left*0.2,  -0.4, 0, // vertex 3
        left*0.0,  -0.6, 0, // vertex 1
        left*0.2,  -0.6, 0, // vertex 2
        left*0.2,  -0.4, 0 // vertex 1

    };  
      float A=left*0.0f,B=left*0.4f;
      int k=0;
      for(int l=0;l<=180;l++)
      {
        semitwo[k++]=A;semitwo[k++]=B; semitwo[k++]=0.0f;
        float a=A,b=B;
        A=a*cos(3.14/180.0) - b*sin(3.14/180.0);
        B=a*sin(3.14/180.0) + b*cos(3.14/180.0);
        semitwo[k++]=A; semitwo[k++]=B; semitwo[k++]=0.0f;
        semitwo[k++]=0.0f; semitwo[k++]=0.0f;semitwo[k++]=0.0f;
      }


    this->semi1 = create3DObject(GL_TRIANGLES, 181*3, semione, { 236, 100, 75 }, GL_FILL);
    this->semi2 = create3DObject(GL_TRIANGLES, 181*3, semitwo, { 0,0,0}, GL_FILL);
    this->rect1 = create3DObject(GL_TRIANGLES, 12, rectangle1, {169,169,169}, GL_FILL);
    this->rect2 = create3DObject(GL_TRIANGLES, 12, rectangle2, {169,169,169}, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0,0, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->semi1);
    draw3DObject(this->semi2);
    draw3DObject(this->rect1);
    draw3DObject(this->rect2);
}

