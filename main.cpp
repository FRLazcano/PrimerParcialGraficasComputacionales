#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "poligonos.h"

Circulo c(Punto(0,0),250);
Linea l(Punto(0,0),Punto(500,500));

void init(void)
{
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1000,1000,-1000,1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 }

void dibujaLinea()
{
  glClear(GL_COLOR_BUFFER_BIT);  //borra la ventana de visualizacion
  glColor3f(1.0, 0.0, 0.0);      //establece que lo que se dibuja sera rojo
  c.draw();
  c.rotacion(0.1);
  glFlush();
 }

 int main(int argc, char** argv)
 {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(1000,1000);
  glutCreateWindow("Mi primer dibujo");
  init();
  c.escalar(2,3);
  glutDisplayFunc(dibujaLinea);
  glutIdleFunc(dibujaLinea);
  glutMainLoop();

  return 0;
}
