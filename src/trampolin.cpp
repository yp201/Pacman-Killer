#include "trampolin.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;

Trampolin::Trampolin(float x, float y, color_t color, float radius) {
    this->position = glm::vec3(x, y, 0);
    static  GLfloat vertex_buffer_data[181*9];
        float X=-0.4f,Y=0.0f;
        int j=0;
        for(int i=0;i<=180;i++)
        {
            vertex_buffer_data[j++]=X;vertex_buffer_data[j++]=Y; vertex_buffer_data[j++]=0.0f;
            float x1=X,y1=Y;

            X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
            Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
            vertex_buffer_data[j++]=X; vertex_buffer_data[j++]=Y; vertex_buffer_data[j++]=0.0f;
            vertex_buffer_data[j++]=0.0f; vertex_buffer_data[j++]=0.0f;vertex_buffer_data[j++]=0.0f;

        }
   static const GLfloat rectangle1[] = {
       -0.4, 0.0, 0, // vertex 1
       -0.5,  -0.6, 0, // vertex 2
       -0.5,  0.0, 0, // vertex 3

       -0.4, 0.0, 0, // vertex 1
       -0.5,  -0.6, 0, // vertex 2
       -0.4, -0.6, 0 // vertex 1
   };
       static const GLfloat rectangle2[] = {
       0.4, 0.0, 0, // vertex 1
       0.5,  -0.6, 0, // vertex 2
       0.5,  0.0, 0, // vertex 3

       0.4,  0.0, 0, // vertex 3
       0.5, -0.6, 0, // vertex 4
       0.4, -0.6, 0 // vertex 1
   };


    this->semi = create3DObject(GL_TRIANGLES, 181*3, vertex_buffer_data, color, GL_FILL);
    this->rect1 = create3DObject(GL_TRIANGLES, 12, rectangle1, color, GL_FILL);
    this->rect2 = create3DObject(GL_TRIANGLES, 12, rectangle2, color, GL_FILL);

}

void Trampolin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0,0, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->semi);
    draw3DObject(this->rect1);
    draw3DObject(this->rect2);
}

