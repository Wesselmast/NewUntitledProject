#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

#include <ft2build.h>
#include FT_FREETYPE_H

void show_triangle(float r, float g, float b) {
  glBegin(GL_TRIANGLES);
  glColor3f(r, g, b);
  glVertex2i( 0,  1);
  glVertex2i(-1, -1);
  glVertex2i( 1, -1);
  glEnd();

  glLoadIdentity();
  glLineWidth(4.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.8f, 0.8f, 0.8f);
  glVertex2i(-1,  1);
  glVertex2i(-1, -1);
  glVertex2i( 1, -1);
  glVertex2i( 1,  1);
  glEnd();
}

void display_viewports(int w, int h, float leftPercent, float rotation) {
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(0, 0, w * leftPercent, h);
  glLoadIdentity();
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  show_triangle(0.8f, 0.1f, 0.1f);

  glViewport(w * leftPercent, 0, w * (1.0f - leftPercent), h/2);
  glLoadIdentity();
  glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
  show_triangle(0.1f, 0.8f, 0.1f);

  glViewport(w * leftPercent, h/2, w * (1.0f - leftPercent), h/2);
  glLoadIdentity();
  show_triangle(0.1f, 0.1f, 0.8f);

  glFlush();
}

