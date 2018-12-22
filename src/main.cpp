#include <bits/stdc++.h>
#include "main.h"
#include "timer.h"
#include "water.h"
#include "ball.h"
#include "ground.h"
#include "platform.h"
#include "trampolin.h"
#include "porcupine.h"
#include "magnet.h"
#include "pacman.h"
#include "newlevel.h"
#include "score.h"
#include <unistd.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball;
vector<Pacman> pacmans;
Water water;
Score score1,score2;
Score leveldigit;
Trampolin trampolin;
Ground ground;
Platform platform;
Newlevel newlevel;
vector<Porcupine> porcupines;
Magnet magnet;
extern bool cannon_keyboard_input, drag_pan;
extern double drag_oldx, drag_oldy;
int totalporcupines=2;
int totalpacmans=20;
int score=0;
int level=1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    platform.draw(VP);
    ground.draw(VP);
    water.draw(VP);
    trampolin.draw(VP);
    
    if(magnet.appear)
    {
      magnet.draw(VP);
    }
    for(int i=0;i<porcupines.size();i++)
    {
      if(porcupines[i].alive)
        porcupines[i].draw(VP);
      
    }
    ball.draw(VP);
    for(int i=0;i<pacmans.size();i++)
    {
        pacmans[i].draw(VP);
    }
    if(score<0)
    {
      score2.draw(VP,10);
      score1.draw(VP,abs(score));
    }
    else
    {
      score1.draw(VP,score%10);
      score2.draw(VP,(score/10)%10);
    }
    leveldigit.draw(VP,level);
}


void tick_input(GLFWwindow *window,int l) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int pan_right=glfwGetKey(window, GLFW_KEY_RIGHT);
    int pan_left=glfwGetKey(window, GLFW_KEY_LEFT);
     if (drag_pan) {
        if (drag_oldx == -1 || drag_oldy == -1) {
            glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
        } else {
            double newx, newy;
            glfwGetCursorPos(window, &newx, &newy);
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            // ball.position.x += 8 * (newx - drag_oldx) / (width * screen_zoom);
            if(8 * (newx - drag_oldx) / (width * screen_zoom)<0)
              left=1;
            else if(8 * (newx - drag_oldx) / (width * screen_zoom)>0)
              right=1;
            if(8 * (newy - drag_oldy) / (height * screen_zoom)<0)
              up=1;

            drag_oldx = newx;
            drag_oldy = newy;
            // reset_screen(0.0);
    }
    if(l==1)
      left=1;
    else if(l==-1)
      right=1;

    if(pan_right)
    {
      screen_center_x+=0.2;
      reset_screen(0.0);
    }
    if(pan_left)
    {
      if(screen_center_x>0)
        screen_center_x-=0.2;
      reset_screen(0.0);  
    }

        if(up && ball.position.y<=-2.0 && (ball.position.x>=-0.7 || ball.position.x<=0.7))   
        {
          ball.time=0;
          ball.initial=0.015;
        }
        if(up && ball.position.x>=-0.7 && ball.position.x<=0.7 && ball.position.y<=-2.0)
        {
          ball.time=0;
          ball.initial=0.012;
        }

        if (left && ball.position.y<=-2.0) 
        {
          ball.speedx=0;
          ball.rotation=ball.rotation+10;
          ball.position.x-=0.05;
          if(ball.position.x<=screen_center_x-2 )
          {
            if(screen_center_x>0)
                screen_center_x-=0.07;
            reset_screen(0.0);
          }
          if(ball.position.x<=-3.7)
            {
              ball.position.x+=0.05;
            }
          for(int i=0;i<porcupines.size();i++)
          {
            if((porcupines[i].alive) && (abs(ball.position.x-(porcupines[i].position.x+porcupines[i].count*0.1))<=0.25) && (ball.position.y <= -2.0) && (ball.position.y >= -2.2)  )
            {
              
              ball.position.x+=0.05;
            }
          }
          
          if(ball.position.x<=3.3 && ball.position.x>=1.7 && ball.position.y<=-2.0)
          {
            ball.position.x+=0.05;
          }
          if(ball.position.x>=-0.7 && ball.position.x<=0.7 && ball.position.y<=-2.0)
          {
            ball.position.x+=0.05;
            ball.position.x-=0.03;
            ball.position.y=-sqrt((0.7*0.7)-(ball.position.x*ball.position.x))-2.2;
          }
        }
        else if(left && ball.position.y>-2.0)
        {
          ball.speedx=-0.02;
        }

        if (right && ball.position.y<=-2.0) {
            ball.speedx=0;
            ball.position.x=ball.position.x+0.05;
            ball.rotation=ball.rotation- 10;
            if(ball.position.x>=screen_center_x+2)
            {
              screen_center_x+=0.07;
              reset_screen(0.0);
            }
            for(int i=0;i<porcupines.size();i++)
            {
              if((porcupines[i].alive) && (abs(ball.position.x-(porcupines[i].position.x))<=0.25) && (ball.position.y<=-2.0)  && (ball.position.y >= -2.2))
              {
                ball.position.x-=0.05;
              }
            }

           
            if (ball.position.x<=3.3 && ball.position.x>=1.7 && ball.position.y<=-2.0)
            {
              ball.position.x-=0.05;
            }
            if(ball.position.x>=-0.7 && ball.position.x<=0.7 && ball.position.y<=-2.0)
            {
              ball.position.x-=0.05;
              ball.position.x+=0.03;
              ball.position.y=-sqrt((0.7*0.7)-(ball.position.x*ball.position.x))-2.2;

            }

        }
        else if(right && ball.position.y>-2.0)
        {
          ball.speedx=0.02;
        }
        int drag_pan = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
   
}
}

void tick_elements() {

    if((score%(15-2*level))==0 && score && (!magnet.appear))
    {
      float y=(rand() %31)/10.0;
      float x=(rand() %65 )/10.0-3.0;
      if(x>0)
      {
        magnet=Magnet(x,y,-1.0,true,0);
      }
      else
      {
        magnet=Magnet(x,y,1.0,true,0);
      }
      magnet.appear=true;
      magnet.time=600;
    }
    if(magnet.time)
    {
      magnet.time--;
      if(!magnet.time)
        magnet.appear=false;
    }
    ball.tick(magnet.position.x,magnet.position.y, magnet.left,magnet.appear);
    vector <Pacman>::iterator it;
    vector <Porcupine>:: iterator porc;
    for(porc = porcupines.begin(); porc!=porcupines.end(); porc++)
    {
      (*porc).tick();
      if((ball.position.x >=(*porc).position.x) && (ball.position.x <=((*porc).position.x+(*porc).count*0.1)) && (ball.position.y<=-1.7)    && (ball.speedy<0) && ((*porc).alive))
      {
        (*porc).alive=false;
        score-=2;
        setLevel();
        // string Score= "score = "+ to_string(score);
        // glfwSetWindowTitle(window, const_cast<char*>(Score.c_str()));
      }
      if((ball.position.x >=(*porc).position.x) && (ball.position.x <=((*porc).position.x+(*porc).count*0.1)) && (ball.position.y<=-1.9) && (ball.position.y>=-2.2) && (ball.speedy==0) && ((*porc).alive))
      {
        score-=4;
        (*porc).alive=false;
        setLevel();
        // string Score= "score = "+ to_string(score);
        // glfwSetWindowTitle(window, const_cast<char*>(Score.c_str()));
      }
    }
    if(porcupines.size()< totalporcupines*level)
    {
      for(int i=0;i<totalporcupines*level-porcupines.size();i++)
      {
        float x=(rand() %45)/10.0-1.0;
        int spikes=(rand()% 5 +1);
        double speedx=(rand() % (2*level) +1)/100.0;
        porcupines.push_back(Porcupine(x,-2.2,spikes,speedx));
      }
    }
    int pacmancount=0;
    for(int i=0;i<pacmans.size();i++)
    {
      if(pacmans[i].position.x>=-5.0 && pacmans[i].position.x<=4.2)
        pacmancount++;
    }
    if(pacmancount<totalpacmans/level)
    {
      for(int i=0;i<(totalpacmans/level-pacmancount);i++)
      {
        float y=(rand() %50)/10.0-1.0;
        int plank=(rand() % 2);
        float radius= (rand() % 20 +1)/100.0+0.05;
        double speedx=(rand() % (3*level) +1)/100.0;
        int color=(rand()% 4 +1);
        double theta=(rand()% 151 +1)*(3.14159/180.0);
        if(plank)
        {          
          if(color==1)
            pacmans.push_back( Pacman(-4,y,COLOR_YELLOW,radius,0.0,0.01,0.0,true,theta));
          else if(color==2)
            pacmans.push_back( Pacman(-4,y,COLOR_MAGENTA,radius,0.0,speedx,0.0,true,theta));
          else if (color==3)
            pacmans.push_back( Pacman(-4,y,COLOR_BLUE,radius,0.0,speedx,0.0,true,theta));
        } 
        else
        {
          if(color==1)
            pacmans.push_back( Pacman(-4,y,COLOR_YELLOW,radius,0.0,speedx,0.0,false,theta));
          else if(color==2)
            pacmans.push_back( Pacman(-4,y,COLOR_MAGENTA,radius,0.0,speedx,0.0,false,theta));
          else if (color==3)
            pacmans.push_back( Pacman(-4,y,COLOR_BLUE,radius,0.0,speedx,0.0,false,theta));
        } 

      }
    }
    for(int i=0;i<pacmans.size();i++)
    {
        pacmans[i].tick();
    }
    for(it = pacmans.begin(); it != pacmans.end();it++)
    {
        if(!(*it).plank)
        { 
          if (detect_collision((*it).bounding_box(), ball.bounding_box())) {
        //   if(ball.speedy < 0 && (ball.initial*ball.initial/2*ball.acceleration)>((*it).position.y+(*it).radius+ball.radius) && ball.time>(ball.initial/ball.acceleration))
          // if(abs(ball.position.x-(*it).position.x)<0.2 && abs((abs(ball.position.y-(*it).position.y)-ball.radius+(*it).radius))<=0.2 && ball.speedy<0)  
            if( ball.speedy < 0  && (ball.position.y-ball.radius)>(*it).position.y)  
            {
              ball.initial=0.012;
              ball.speedy=0;
              ball.time=0;
              (*it).position.x=-5.0;
              score+=1;
              setLevel();
            }
          }
        }
        else if((*it).plank)
        {
          double theta=60.0*(3.14159/180.0);
          double alpha=atan2(ball.speedy,ball.speedx);
          double slope=-cos(theta)/sin(theta);
          double speed=sqrt((ball.speedy*ball.speedy)+(ball.speedx*ball.speedx));
          float xmin=(*it).position.x+(((*it).radius)+0.5)*cos(theta)-0.5*sin(theta);
          float ymin=(*it).position.y+(((*it).radius)+0.5)*sin(theta)+0.5*cos(theta);
          float xmax=(*it).position.x+(((*it).radius)+0.5)*cos(theta)+0.5*sin(theta);
          float ymax=(*it).position.y+(((*it).radius)+0.5)*sin(theta)-0.5*sin(theta);
          if(ball.position.x<=xmax &&  ball.position.x>=xmin && ball.speedy<0 )
          {
            if(abs(ball.position.y-((slope*(ball.position.x-xmin))+ymin))<=0.25)
            {
              double reflection_angle=2*theta-alpha;
              ball.speedx=reflection_angle*speed;
              ball.speedy=reflection_angle*speed;
              (*it).position.x=-5.0;
              score+=1;
              setLevel();

            }
          }
          else
          {
            if (detect_collision((*it).bounding_box(), ball.bounding_box())) {
        //   if(ball.speedy < 0 && (ball.initial*ball.initial/2*ball.acceleration)>((*it).position.y+(*it).radius+ball.radius) && ball.time>(ball.initial/ball.acceleration))
          // if(abs(ball.position.x-(*it).position.x)<0.2 && abs((abs(ball.position.y-(*it).position.y)-ball.radius+(*it).radius))<=0.2 && ball.speedy<0)  
            if( ball.speedy < 0  && (ball.position.y-ball.radius)>(*it).position.y)  
            {
              ball.initial=0.012;
              ball.speedy=0;
              ball.time=0;
              (*it).position.x=-5.0;
              score+=1;
              setLevel();

            }
          }
          }

        }        
           if((*it).position.x>400)
          {
              (*it).position.x=-5.0;
          }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ground=Ground(0,-2.4,COLOR_GREEN);
    platform=Platform(0,-2.4,COLOR_BROWN);
    water =   Water(0,-2.2, COLOR_AQUA);
    magnet =   Magnet(2.5,1.5,1.0,false,0);
    newlevel= Newlevel(0.0,0.0);
    score2=Score(-3.6,-3.0);
    score1=Score(-3.0,-3.0);
    leveldigit=Score(-3.5,-3.5);

    // porcupines.push_back(Porcupine(1,-2.2,5,0.01));
    // porcupines.push_back(Porcupine(-2,-2.2,3,0.01));
    // pacmans.push_back( Pacman(-3,-1,COLOR_YELLOW,0.2,0.0,0.0,0.0,true));


    ball = Ball(-3.0, -1.9, COLOR_RED,0.3,0.001,0.0,0.0);
    trampolin= Trampolin(2.5,-1.6,COLOR_RED,0.4);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);


    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window,0);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) ;
}
void setLevel(){
    if(score<10)
      level=1;
    else if(score<20)
      level=2;
    else if(score<30)
      level=3;
    else if(score<40)
      level=4;
    else if(score<50)
      level=5;
    else if(score<60)
      level=6;

  string Score= "score = "+ to_string(score) + "  level " + to_string(level);
        glfwSetWindowTitle(window, const_cast<char*>(Score.c_str()));

}


void reset_screen(float zoom) {
    setLevel();
    screen_zoom+=zoom;
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
