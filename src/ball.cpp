#include "ball.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;
Ball::Ball(float x, float y, color_t color,float radius,double acceleration,double speedx,double speedy) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedx = speedx;
    this->speedy= speedy;
    this->initial=0;
    this->initialx=0.02;
    this->acceleration=acceleration;
    this->accelerationx=0.002;
    this->time=0;

        float X=0.0f,Y=radius;
        int j=0;
            static  GLfloat vertex_buffer_sector1[61*9];
            static  GLfloat vertex_buffer_sector2[61*9];
            static  GLfloat vertex_buffer_sector3[61*9];
            static  GLfloat vertex_buffer_sector4[61*9];
            static  GLfloat vertex_buffer_sector5[61*9];
            static  GLfloat vertex_buffer_sector6[61*9];
            for(int i=0;i<=60;i++)
            {
                vertex_buffer_sector1[j++]=X;vertex_buffer_sector1[j++]=Y; vertex_buffer_sector1[j++]=0.0f;
                float x1=X,y1=Y;
                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_sector1[j++]=X; vertex_buffer_sector1[j++]=Y; vertex_buffer_sector1[j++]=0.0f;
                vertex_buffer_sector1[j++]=0.0f; vertex_buffer_sector1[j++]=0.0f;vertex_buffer_sector1[j++]=0.0f;

            }
            j=0;
            for(int i=0;i<=60;i++)
            {
                vertex_buffer_sector2[j++]=X;vertex_buffer_sector2[j++]=Y; vertex_buffer_sector2[j++]=0.0f;
                float x1=X,y1=Y;
                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_sector2[j++]=X; vertex_buffer_sector2[j++]=Y; vertex_buffer_sector2[j++]=0.0f;
                vertex_buffer_sector2[j++]=0.0f; vertex_buffer_sector2[j++]=0.0f;vertex_buffer_sector2[j++]=0.0f;

            }
            j=0;
            for(int i=0;i<=60;i++)
            {
                vertex_buffer_sector3[j++]=X;vertex_buffer_sector3[j++]=Y; vertex_buffer_sector3[j++]=0.0f;
                float x1=X,y1=Y;
                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_sector3[j++]=X; vertex_buffer_sector3[j++]=Y; vertex_buffer_sector3[j++]=0.0f;
                vertex_buffer_sector3[j++]=0.0f; vertex_buffer_sector3[j++]=0.0f;vertex_buffer_sector3[j++]=0.0f;

            }
            j=0;
            for(int i=0;i<=60;i++)
            {
                vertex_buffer_sector4[j++]=X;vertex_buffer_sector4[j++]=Y; vertex_buffer_sector4[j++]=0.0f;
                float x1=X,y1=Y;
                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_sector4[j++]=X; vertex_buffer_sector4[j++]=Y; vertex_buffer_sector4[j++]=0.0f;
                vertex_buffer_sector4[j++]=0.0f; vertex_buffer_sector4[j++]=0.0f;vertex_buffer_sector4[j++]=0.0f;

            }
            j=0;
            for(int i=0;i<=60;i++)
            {
                vertex_buffer_sector5[j++]=X;vertex_buffer_sector5[j++]=Y; vertex_buffer_sector5[j++]=0.0f;
                float x1=X,y1=Y;
                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_sector5[j++]=X; vertex_buffer_sector5[j++]=Y; vertex_buffer_sector5[j++]=0.0f;
                vertex_buffer_sector5[j++]=0.0f; vertex_buffer_sector5[j++]=0.0f;vertex_buffer_sector5[j++]=0.0f;

            }
            j=0;
            for(int i=0;i<=60;i++)
            {
                vertex_buffer_sector6[j++]=X;vertex_buffer_sector6[j++]=Y; vertex_buffer_sector6[j++]=0.0f;
                float x1=X,y1=Y;

                X=x1*cos(3.14/180.0) - y1*sin(3.14/180.0);
                Y=x1*sin(3.14/180.0) + y1*cos(3.14/180.0);
                vertex_buffer_sector6[j++]=X; vertex_buffer_sector6[j++]=Y; vertex_buffer_sector6[j++]=0.0f;
                vertex_buffer_sector6[j++]=0.0f; vertex_buffer_sector6[j++]=0.0f;vertex_buffer_sector6[j++]=0.0f;

            }
            this->sector1 = create3DObject(GL_TRIANGLES, 61*3, vertex_buffer_sector1, {236, 100, 75}, GL_FILL);
            this->sector2 = create3DObject(GL_TRIANGLES, 61*3, vertex_buffer_sector2, { 135, 211, 124 }, GL_FILL);
            this->sector3 = create3DObject(GL_TRIANGLES, 61*3, vertex_buffer_sector3, {0,0,139}, GL_FILL);
            this->sector4 = create3DObject(GL_TRIANGLES, 61*3, vertex_buffer_sector4, {255, 0, 255}, GL_FILL);
            this->sector5 = create3DObject(GL_TRIANGLES, 61*3, vertex_buffer_sector5, {165, 42, 42}, GL_FILL);
            this->sector6 = create3DObject(GL_TRIANGLES, 61*3, vertex_buffer_sector6, {115, 20, 62}, GL_FILL);

        
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0,0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->sector1);
    draw3DObject(this->sector2);
    draw3DObject(this->sector3);
    draw3DObject(this->sector4);
    draw3DObject(this->sector5);
    draw3DObject(this->sector6);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(float x,float y, float left, bool appear) {
    this->time+=1;
    if(this->initial)
    {
        this->speedy=this->initial-this->acceleration*this->time;
    }
    this->position.x += this->speedx;
    // if((this->position.x>=1.7 && this->position.x <= 2.0) || (this->position.x>2.9 && this->position.x <= 3.3))
    // {
    //     if(this->position.y + this->initial*this->time -0.5*this->acceleration*this->time*this->time >=-1.8)
    //     {
    //         this->position.y  = this->position.y + this->initial*this->time -0.5*acceleration*time*time;
    //     }
    //     else 
    //     {
    //             this->initial=0.01;
    //             this->time=0;
    //             this->speedy=0;
    //     } 
    // }
    if(appear)
    {

        if(left==1.0)
        {

           if(this->position.x<=(x+8.0) && this->position.x>=x && this->position.y<=(y+0.6) && this->position.y>=(y-0.6))
            {
                this->accelerationx=-abs(this->accelerationx); 
                this->position.x  = this->position.x + this->initialx*this->time + 0.5*accelerationx*time*time;
            }
        }
        else
        {
            if(this->position.x>=(x-8.0) && this->position.x<=x && this->position.y<=(y+0.6) && this->position.y>=(y-0.6))
            {            
                this->accelerationx=abs(this->accelerationx);
                this->position.x  = this->position.x + this->initialx*this->time + 0.5*accelerationx*time*time;
            }
        }
    }
    if(this->position.x>=2.1 && this->position.x<=2.9)
    {
        if(this->position.y + this->initial*this->time -0.5*this->acceleration*this->time*this->time >=-1.8)
        {
            this->position.y  = this->position.y + this->initial*this->time -0.5*acceleration*time*time;
        }
        else 
        {
                this->initial=0.02;
                this->time=0;
                this->speedy=0;
        }
    }
    else
    {


        if(this->position.x <-0.7 || this->position.x >0.7 || this->position.y>-2.0)
        {
            if(this->position.y + this->initial*this->time -0.5*this->acceleration*this->time*this->time >= -2.0)
            {
                this->position.y  = this->position.y + this->initial*this->time -0.5*acceleration*time*time;
            }
            else 
            {
                {
                    this->time=0;
                    this->speedy=0;
                    this->speedx=0;
                    this->position.y=-2.0;
                    this->initial=0;
                }

            }
        }
        else if(this->position.x>=-0.7 && this->position.x<=0.7 )
        {
            if(this->position.x<-0.03)
            {
                this->position.x+=0.01;
                this->rotation-=20;
            }
            if(this->position.x>0.03)
            {
                this->position.x-=0.01;
                this->rotation+=20;
            }
            if(this->position.y + this->initial*this->time -0.5*this->acceleration*this->time*this->time >= (-sqrt((0.7*0.7)-(this->position.x*this->position.x))-2.2))
            {
                this->position.y  = this->position.y + this->initial*this->time -0.5*acceleration*time*time;
            }
            else
            {
                    this->time=0;
                    this->speedy=0;
                    this->speedx=0;
                    this->position.y=-sqrt((0.7*0.7)-(this->position.x*this->position.x))-2.2;
                    this->initial=0;
            }
        }
    }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
