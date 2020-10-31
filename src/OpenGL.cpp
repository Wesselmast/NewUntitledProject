#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct Object {
  uint32 vertexBuffer;
  uint32 vertexArray;
  uint32 program;
};

#include "Text.cpp"

static Object triangle;
static Object text;

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

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  text_init();

  //triangle.program = load_shaders("res/shaders/defaultV.shader", "res/shaders/defaultF.shader"); 
  

  text.program = load_shaders("res/shaders/textV.shader", "res/shaders/textF.shader");
  
  glGenVertexArrays(1, &text.vertexArray);
  glGenBuffers(1, &text.vertexBuffer);
  glBindVertexArray(text.vertexArray); 
  glBindBuffer(GL_ARRAY_BUFFER, text.vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, 0, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

 // const float vertices[] = {
 //   -1.0f, -1.0f, 0.0f,
 //    1.0f, -1.0f, 0.0f,
 //    0.0f,  1.0f, 0.0f,
 // };

 // glGenBuffers(1, &triangle.vertexBuffer);
 // glBindBuffer(GL_ARRAY_BUFFER, triangle.vertexBuffer);
 // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
  //show_triangle(0.8f, 0.1f, 0.1f);
  render_text(&text, "First", 0.0f, 0.0f, 0.0, 0.2f, 1.0f);
  viewport_border();

  glViewport(w * leftPercent, 0, w * (1.0f - leftPercent), h/2);
  glLoadIdentity();
  glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
  //show_triangle(0.1f, 0.8f, 0.1f);
  render_text(&text, "Second", 0.0f, 0.0f, 1.0f, 0.0f, 0.2f);
  viewport_border();

  glViewport(w * leftPercent, h/2, w * (1.0f - leftPercent), h/2);
  glLoadIdentity();
  //show_triangle(0.1f, 0.1f, 0.8f);
  render_text(&text, "Third", 0.0f, 0.0f, 0.2f, 1.0f, 0.0f);
  viewport_border();

  glFlush();
}

