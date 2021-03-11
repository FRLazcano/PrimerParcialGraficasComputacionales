#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<stdio.h>

static int slices = 16;
static int stacks = 16;

// #include<bits/stdc++.h>
// using namespace std;

/* GLUT callback Handlers */
int x,y,click=0;
bool check=true;
int x0,x1,y0,y1;
static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawLine_0(int x0, int y0, int x1, int y1,int z)
{
    int dX = x1-x0;
    int dY = y1-y0;

    int x=x0,y=y0;
    int d= 2*dY-dX;

    int dE=2*dY,dNE=2*(dY-dX);

    glVertex2i(x,y);

    while(x<x1)
    {

        if(d<0)
        {
            x++;
            d+=dE;
        }
        else
        {
            x++;
            y++;
            d+=dNE;
        }

    if(z==0) glVertex2i(x,y);
    else if(z==1) glVertex2i(y,x);
    else if(z==2) glVertex2i(-y,x);
    else if(z==3) glVertex2i(-x,y);
    else if(z==4) glVertex2i(-x,-y);
    else if(z==5) glVertex2i(-y,-x);
    else if(z==6) glVertex2i(y,-x);
    else if(z==7) glVertex2i(x,-y);

    }

}

int selectZone(int x0, int y0, int x1, int y1){

int dX = x1-x0;
    int dY = y1-y0;

    int z;



    if(dX>=0 && dY>=0)
    {
        if(dX>dY)
            return 0;
        else
            return 1;
    }
    else if(dX<0 && dY>=0)
    {
        if(abs(dX)>dY)
            return 3;
        else
           return 2;
    }
    else if(dX<0 && dY<0)
    {
        if(abs(dX)>abs(dY))
           return 4;
        else
           return 5;
    }
    else if(dX>=0 && dY<0)
    {
        if(dX>abs(dY))
            return 7;
        else
            return 6;
    }
}



void lineDraw(int x0, int y0, int x1, int y1)
{
    int dX = x1-x0;
    int dY = y1-y0;

    int z;



    if(dX>=0 && dY>=0)
    {
        if(dX>dY)
            z=0;
        else
            z=1;
    }
    else if(dX<0 && dY>=0)
    {
        if(abs(dX)>dY)
            z=3;
        else
            z=2;
    }
    else if(dX<0 && dY<0)
    {
        if(abs(dX)>abs(dY))
            z=4;
        else
            z=5;
    }
    else if(dX>=0 && dY<0)
    {
        if(dX>abs(dY))
            z=7;
        else
            z=6;
    }



    //printf("Zone =  %d\n",z);
    if(z==0){

        glColor3f(1,0,0);

        drawLine_0(x0,y0,x1,y1,z);
    }
    else if(z==1){

        glColor3f(0,1,0);

        drawLine_0(y0,x0,y1,x1,z);
    }
    else if(z==2){

        glColor3f(0,0,1);

        drawLine_0(y0,-x0,y1,-x1,z);
    }
    else if(z==3){

        glColor3f(1,1,0);

        drawLine_0(-x0,y0,-x1,y1,z);
    }
    else if(z==4){

        glColor3f(1,0,1);

        drawLine_0(-x0,-y0,-x1,-y1,z);
    }
    else if(z==5){

        glColor3f(0,1,1);

        drawLine_0(-y0,-x0,-y1,-x1,z);
    }
    else if(z==6){

        glColor3f(1,1,1);

        drawLine_0(-y0,x0,-y1,x1,z);
    }
    else if(z==7){

         glColor3f(.5,.6,.4);

        drawLine_0(x0,-y0,x1,-y1,z);
    }



}

static void display(void){
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();
    glBegin(GL_POINTS);
    // glVertex2i(x, y+1);
    // glVertex2i(x, y);
    if(click==2) lineDraw(x0,y0,x1,y1);



    glEnd();
    glutSwapBuffers();
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       check=true;

        x = mousex-320;
        y = 240-mousey;

        if(click==0){
          x0=x;
          y0=y;
          click=1;
        }
        else if(click==1){
            x1=x;
            y1=y;
            click=2;
            if(selectZone(x0,y0,x1,y1)==0) printf("RED\n");
            if(selectZone(x0,y0,x1,y1)==1) printf("GREEN\n");
            if(selectZone(x0,y0,x1,y1)==2) printf("BLUE\n");
            if(selectZone(x0,y0,x1,y1)==3) printf("YeLLOw\n");
            if(selectZone(x0,y0,x1,y1)==4) printf("PURPLE\n");
            if(selectZone(x0,y0,x1,y1)==5) printf("SKY BLUE\n");
            if(selectZone(x0,y0,x1,y1)==6) printf("WHITE\n");
            if(selectZone(x0,y0,x1,y1)==7) printf("BROWN\n");
        }
        else{
            x0=x;
          y0=y;
          click=1;
        }


        printf("%d %d\n",x,y);

        }

   else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//undo(clear)the drawing
           {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
      check = false;
     }
glutPostRedisplay();
     }
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMainLoop();

    return EXIT_SUCCESS;
}
