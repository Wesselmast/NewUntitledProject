#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Object {
  uint32 vertexBuffer;
  uint32 program;
};

static Object triangle;

uint32 load_shaders(const char* vertexPath, const char* fragmentPath) {
  uint32 vertexShader   = glCreateShader(GL_VERTEX_SHADER);
  uint32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  uint32 program = glCreateProgram();

  int result;
  int info;

  std::string vSourceStr = load_file(vertexPath);
  std::string fSourceStr = load_file(fragmentPath);


  const char* vertexSource = vSourceStr.c_str();
  const char* fragmentSource = fSourceStr.c_str(); 

  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &info);
  if(info > 0) {
    char error[info + 1];
    glGetShaderInfoLog(vertexShader, info, NULL, error);
    printf("VERTEX: %s\n", error);
  }
  
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &info);
  if(info > 0) {
    char error[info + 1];
    glGetShaderInfoLog(fragmentShader, info, NULL, error);
    printf("FRAGMENT: %s\n", error);
  }  

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program; 
}

void opengl_init() {
  glewExperimental = true;
  if(glewInit() != GLEW_OK) {
    printf("glew is bogged!");
  }

  triangle.program = load_shaders("res/shaders/defaultV.shader", "res/shaders/defaultF.shader"); 

  uint32 vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray); 

  const float vertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  };

  glGenBuffers(1, &triangle.vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void show_triangle(float r, float g, float b) {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.vertexBuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glUseProgram(triangle.program);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  glUseProgram(0);
  glDisableVertexAttribArray(0);
}

void viewport_border() {
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
  viewport_border();

  glViewport(w * leftPercent, 0, w * (1.0f - leftPercent), h/2);
  glLoadIdentity();
  glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
  show_triangle(0.1f, 0.8f, 0.1f);
  viewport_border();

  glViewport(w * leftPercent, h/2, w * (1.0f - leftPercent), h/2);
  glLoadIdentity();
  show_triangle(0.1f, 0.1f, 0.8f);
  viewport_border();

  glFlush();
}

