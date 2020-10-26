#include <stdio.h>
#include <cstdint>

typedef uint32_t uint32;

#include "Input.cpp"
#include "Windows.cpp"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
  HWND window = create_and_show_window(hInstance, nCmdShow);

  MSG message;

  int hackyFramer = 0;
  while(true) {
    while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
      if(message.message == WM_QUIT) goto quit;
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    if(hackyFramer > 10000) {
      hackyFramer = 0;
      rotation += is_down(KEY_ALT) && is_down(MOUSE_L);
      PostMessage(window, WM_PAINT, 0, 0);
    }

    hackyFramer++;
  }

quit:
  printf("QUIT!");
  return 0;
}
