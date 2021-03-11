#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <cstddef>
#include <iostream>

class Punto{
  public:
    float coord[2];

    Punto(float x, float y);
    void traslacion(float x, float y);
    void rotacion(float a);
    void escalar(float x, float y);
};

Punto::Punto(float x, float y){
  coord[0]=x;
  coord[1]=y;
}

void Punto::traslacion(float x, float y){
  coord[0]+=x;
  coord[1]+=y;
}

void Punto::rotacion(float a){
  float rad=a*22/(180*7);
  float r1,r2;
  r1=coord[0]*cos(rad)-coord[1]*sin(rad);
  r2=coord[0]*sin(rad)+coord[1]*cos(rad);
  coord[0]=r1;
  coord[1]=r2;
}

void Punto::escalar(float x, float y){
  coord[0]*=x;
  coord[1]*=y;
}

class Linea{

  public:
  Punto puntos[2];

  Linea();
  Linea(Punto p0, Punto p1);
  void draw();
  void rotacion(float a);
  void traslacion(float x,float y);
  void escalar(float x, float y);
  int selectZone();
};

Linea::Linea():
puntos{Punto(0,0),Punto(0,0)}
{

}

Linea::Linea(Punto p0, Punto p1)
:puntos{p0,p1}
{}

void Linea::rotacion(float a){
  puntos[0].rotacion(a);
  puntos[1].rotacion(a);
}

void Linea::traslacion(float x, float y){
  puntos[0].traslacion(x,y);
  puntos[1].traslacion(x,y);
}

void Linea::escalar(float x,float y){
  puntos[0].escalar(x,y);
  puntos[1].escalar(x,y);
}

int Linea::selectZone(){
  float dx=puntos[1].coord[0]-puntos[0].coord[0];
  float dy=puntos[1].coord[1]-puntos[0].coord[1];
  if(dx>=0 && dy>=0){
    if(dx>dy)
      return 0;
    else
      return 1;
  }
  else if(dx<0 && dy>=0){
    if(abs(dx)>dy)
      return 3;
    else
      return 2;
  }
  else if(dx<0 && dy<0){
    if(abs(dx)>abs(dy))
      return 4;
    else
      return 5;
  }
  else if(dx>=0 && dy<0){
    if(dx>abs(dy))
      return 7;
    else
      return 6;
  }
  return NULL;
}

void Linea::draw(){
  float x,y,x0,y0,x1,y1,dx,dy;
  int z=selectZone();
  switch (z) {
    case 0:
      x0=puntos[0].coord[0];
      y0=puntos[0].coord[1];
      x1=puntos[1].coord[0];
      y1=puntos[1].coord[1];
      break;

    case 1:
      x0=puntos[0].coord[1];
      y0=puntos[0].coord[0];
      x1=puntos[1].coord[1];
      y1=puntos[1].coord[0];
      break;

    case 2:
      x0=puntos[0].coord[1];
      y0=-puntos[0].coord[0];
      x1=puntos[1].coord[1];
      y1=-puntos[1].coord[0];
      break;

    case 3:
      x0=-puntos[0].coord[0];
      y0=puntos[0].coord[1];
      x1=-puntos[1].coord[0];
      y1=puntos[1].coord[1];
      break;

    case 4:
      x0=-puntos[0].coord[0];
      y0=-puntos[0].coord[1];
      x1=-puntos[1].coord[0];
      y1=-puntos[1].coord[1];
      break;

    case 5:
      x0=-puntos[0].coord[1];
      y0=-puntos[0].coord[0];
      x1=-puntos[1].coord[1];
      y1=-puntos[1].coord[0];
      break;

    case 6:
      x0=-puntos[0].coord[1];
      y0=puntos[0].coord[0];
      x1=-puntos[1].coord[1];
      y1=puntos[1].coord[0];
      break;

    case 7:
      x0=puntos[0].coord[0];
      y0=-puntos[0].coord[1];
      x1=puntos[1].coord[0];
      y1=-puntos[1].coord[1];
      break;
  }
  glBegin(GL_POINTS);
  int dX = x1-x0;
    int dY = y1-y0;

    x=x0;
    y=y0;
    int d= 2*dY-dX;

    int dE=2*dY,dNE=2*(dY-dX);

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

    if(z==0) glVertex2f(x,y);
    else if(z==1) glVertex2f(y,x);
    else if(z==2) glVertex2f(-y,x);
    else if(z==3) glVertex2f(-x,y);
    else if(z==4) glVertex2f(-x,-y);
    else if(z==5) glVertex2f(-y,-x);
    else if(z==6) glVertex2f(y,-x);
    else if(z==7) glVertex2f(x,-y);

    }
  glEnd();
}

class Circulo{
  public:
    Punto centro;
    float radio;
    Linea lineas[360];
    Circulo(Punto p, float r);
    void traslacion(float x, float y);
    void rotacion(float a);
    void escalar(float x, float y);
    void draw();
};

Circulo::Circulo(Punto p, float r):
centro(p),radio(r)
{
  float rad,rad2;
  for(int i=0; i<360; i++){
    printf("%f  %f\n",rad,rad2 );
    rad=(float)i*335/(180*113);
    rad2=((float)i+1)*22/(180*7);
    lineas[i]=Linea(Punto(p.coord[0]+r*cos(rad), p.coord[1]+r*sin(rad)),Punto(p.coord[0]+r*cos(rad2),p.coord[1]+r*sin(rad2)));
  }
}

void Circulo::traslacion(float x, float y){
  for(int i=0; i<360;i++){
    lineas[i].traslacion(x,y);
  }
}

void Circulo::rotacion(float a){
  for(int i=0; i<360;i++){
    lineas[i].rotacion(a);
  }
}

void Circulo::escalar(float x, float y){
  for(int i=0; i<360;i++){
    lineas[i].escalar(x,y);
  }
}

void Circulo::draw(){
  for(int i=0; i<360;i++){
    lineas[i].draw();
  }
}
