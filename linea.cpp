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
  float matriz[2][2]={{cos(rad),-sin(rad)},{sin(rad),cos(rad)}};
  float resultado[2]={0,0};
  for(int i=0; i<2;i++){
    for(int j=0;j<2;j++){
      resultado[i]+=coord[j]*matriz[i][j];
    }
  }
  coord[0]=resultado[0];
  coord[1]=resultado[1];
}

void Punto::escalar(float x, float y){
  coord[0]=x;
  coord[1]=y;
}

class Linea{

  public:
  Punto puntos[2];

  Linea(Punto p0, Punto p1);
  void draw();
  void rotacion(float a);
  void traslacion(float x,float y);
  void escalar(float x, float y);
};

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

void Linea::draw(){
  float x,y;
  float dx=puntos[1].coord[0]-puntos[0].coord[0];
  float dy=puntos[1].coord[1]-puntos[0].coord[1];
  float m=(dy)/(dx);
  float p=2*dy-dx;

  x=puntos[0].coord[0];
  y=puntos[0].coord[1];

  glBegin(GL_POINTS);
  while(x<=puntos[1].coord[0]){
    if(p>=1){
      y++;
      p=p+2*dy-2*dx;
    }else{
      y=y;
      p=p+2*dy-2*dx;
    }
    glVertex2f(x,y);
    x++;
  }
  glEnd();
}

struct Nodo{
  Linea l;
  struct Nodo * next;
};

class Circulo{
  public:
    Punto centro;
    float radio;
    Nodo * inicio;
    Circulo(Punto p, float r);
    void traslacion(float x, float y);
    void rotacion(float a);
    void escalar(float x, float y);
    void draw();
};

Circulo::Circulo(Punto p, float r):
centro(p),radio(r)
{
  Nodo *actual=inicio;
  float rad,rad2;
  for(int i=0; i<359; i++){
    rad=i*22/(180*7);
    rad2=(i+1)*22/(180*7);
    Punto p0(p.coord[0]+cos(rad),p.coord[1]+sin(rad));
    Punto p1(p.coord[0]+cos(rad2),p.coord[1]+sin(rad2));
    actual->l=Linea(p0,p1);
    struct Nodo * nuevo = (struct Nodo * ) malloc(sizeof(struct Nodo));
    actual->next=nuevo;
    actual=actual->next;
  }
  actual=NULL;
}

void Circulo::traslacion(float x, float y){
  Nodo *actual=inicio;
  while(actual!=NULL){
    actual->l.traslacion(x,y);
    actual=actual->next;
  }
}

void Circulo::rotacion(float a){
  Nodo *actual=inicio;
  while(actual!=NULL){
    actual->l.rotacion(a);
    actual=actual->next;
  }
}

void Circulo::escalar(float x, float y){
  Nodo *actual=inicio;
  while(actual!=NULL){
    actual->l.escalar(x,y);
    actual=actual->next;
  }
}

void Circulo::draw(){
  Nodo *actual=inicio;
  while(actual!=NULL){
    actual->l.draw();
    actual=actual->next;
  }
}

int main(){
  return 0;
}
