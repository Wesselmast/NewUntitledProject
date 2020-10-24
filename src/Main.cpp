#include <stdio.h>
#include <cstdint>

typedef uint32_t uint32;

#include "Windows.cpp"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
  create_and_show_window(hInstance, nCmdShow);

  MSG message;
  while(true) {
    while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
      if(message.message == WM_QUIT) goto quit;
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
  }

quit:
  printf("QUIT!");
  return 0;
}
