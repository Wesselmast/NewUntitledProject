#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define PROC_DEFAULT DefWindowProc(window, msg, wParam, lParam);

void show_triangle() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2i(0,  1);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2i(-1, -1);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2i(1, -1);

  glEnd();
  glFlush();
}

LRESULT CALLBACK window_proc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
  static PAINTSTRUCT paint;

  switch(msg) {
    case WM_PAINT: {
      show_triangle();
      BeginPaint(window, &paint);
      EndPaint(window, &paint);
      return PROC_DEFAULT;
    }
    case WM_SIZE: {
      glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
      PostMessage(window, WM_PAINT, 0, 0);
      return PROC_DEFAULT;  
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      return PROC_DEFAULT;
    }
    case WM_CLOSE: {
      DestroyWindow(window);   
      return PROC_DEFAULT;
    }
  }
  return PROC_DEFAULT;
}

void create_and_show_window(HINSTANCE hInstance, int nCmdShow) {
  const char* className = "CustomFloatingWindow";

  WNDCLASS windowClass = {};
  windowClass.lpfnWndProc   = window_proc;
  windowClass.hInstance     = hInstance;
  windowClass.lpszClassName = className;

  RegisterClass(&windowClass);

  HWND window = CreateWindowEx(
      0,
      className,
      "Triangle",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
      0,
      0,
      hInstance,
      0
      );
  if(!window) return;

  HDC hdc = GetDC(window);

  PIXELFORMATDESCRIPTOR pfd;
  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  int pf = ChoosePixelFormat(hdc, &pfd);
  if(!pf) return;
  if(SetPixelFormat(hdc, pf, &pfd) == FALSE) return;
  DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  
  HGLRC hrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, hrc);

  ShowWindow(window, nCmdShow);
}
