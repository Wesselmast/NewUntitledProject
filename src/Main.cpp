#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <chrono>

typedef uint32_t uint32;

void full_path(char* buffer, const char* fileName);

#include "File.cpp"
#include "Input.cpp"
#include "Windows.cpp"

typedef BOOL fptr_wglSwapIntervalEXT(int interval);

void l_pressed_down() {
  if(leftPercent + 0.05 < 0.95) {
    leftPercent += 0.05;
  }
}

void h_pressed_down() {
  if(leftPercent - 0.05 > 0.05) {
    leftPercent -= 0.05;
  }
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
  HWND window = create_and_show_window(hInstance, nCmdShow);

  MSG message;

  register_key_down(KEY_L, &l_pressed_down);
  register_key_down(KEY_H, &h_pressed_down);
  
  fptr_wglSwapIntervalEXT* wglSwapInterval = (fptr_wglSwapIntervalEXT*)wglGetProcAddress("wglSwapIntervalEXT");
  if(!wglSwapInterval) return 0; //add assert

  std::chrono::high_resolution_clock timer;
  double time = 0.0;
  double dt = 0.015;
  float speed = 50.0f;
  
  opengl_init();
  
  while(true) {
    auto start = timer.now();
    while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
      if(message.message == WM_QUIT) goto quit;
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    tick_input();

    bool rotate = (is_down(KEY_ALT) && is_down(MOUSE_L));
    rotation += rotate * dt * speed;
    PostMessage(window, WM_PAINT, 0, 0);
    
    wglSwapInterval(1);
    
    dt = std::chrono::duration<double>(timer.now() - start).count();
    time += dt;
  }

quit:
  unregister_key_down(KEY_L, &l_pressed_down);
  unregister_key_down(KEY_H, &h_pressed_down);
  printf("QUIT!");
  return 0;
}
