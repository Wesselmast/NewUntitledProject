#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define PROC_DEFAULT DefWindowProc(window, msg, wParam, lParam);

static int w = 1920;
static int h = 1080;

void show_triangle() {
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.2f);
  glVertex2i(0,  1);
  glColor3f(0.0f, 0.2f, 1.0f);
  glVertex2i(-1, -1);
  glColor3f(0.0f, 0.2f, 1.0f);
  glVertex2i(1, -1);
  glEnd();
}

static float rotation = 0.0f;

void display_viewports() {
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glViewport(0, 0, w/2, h);
  glLoadIdentity();
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  show_triangle();

  glViewport(w/2, 0, w/2, h/2);
  glLoadIdentity();
  glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
  show_triangle();

  glViewport(w/2, h/2, w/2, h/2);
  glLoadIdentity();
  show_triangle();

  glFlush();
}

LRESULT CALLBACK window_proc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
  static PAINTSTRUCT paint;

  switch(msg) {
    case WM_PAINT: {
      display_viewports();
      BeginPaint(window, &paint);
      EndPaint(window, &paint);
      return PROC_DEFAULT;
    }
    case WM_SIZE: {
      w = LOWORD(lParam);
      h = HIWORD(lParam);
      return PROC_DEFAULT;  
    }
    case WM_LBUTTONDOWN: { set_key_state(MOUSE_L, 1); return PROC_DEFAULT; }
    case WM_MBUTTONDOWN: { set_key_state(MOUSE_M, 1); return PROC_DEFAULT; }
    case WM_RBUTTONDOWN: { set_key_state(MOUSE_R, 1); return PROC_DEFAULT; }

    case WM_LBUTTONUP:   { set_key_state(MOUSE_L, 0); return PROC_DEFAULT; }
    case WM_MBUTTONUP:   { set_key_state(MOUSE_M, 0); return PROC_DEFAULT; }
    case WM_RBUTTONUP:   { set_key_state(MOUSE_R, 0); return PROC_DEFAULT; }

    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP: {   
      int isDown = !((lParam & (1 << 31)) != 0);
      set_key_state(wParam, isDown);
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

HWND create_and_show_window(HINSTANCE hInstance, int nCmdShow) {
  const char* className = "CustomFloatingWindow";

  WNDCLASS windowClass = {};
  windowClass.lpfnWndProc   = window_proc;
  windowClass.hInstance     = hInstance;
  windowClass.lpszClassName = className;

  RegisterClass(&windowClass);

  HWND window = CreateWindowEx(
      0,
      className,
      "VimTest",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
      0,
      0,
      hInstance,
      0
      );
  if(!window) return nullptr;

  HDC hdc = GetDC(window);

  PIXELFORMATDESCRIPTOR pfd;
  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  int pf = ChoosePixelFormat(hdc, &pfd);
  if(!pf) return nullptr;
  if(SetPixelFormat(hdc, pf, &pfd) == FALSE) return nullptr;
  DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  
  HGLRC hrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, hrc);

  ShowWindow(window, nCmdShow);
  
  return window;
}
