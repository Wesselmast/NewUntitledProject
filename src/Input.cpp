#pragma once

enum {
  MOUSE_L = 0x01,
  MOUSE_R = 0x02,
  MOUSE_M = 0x04,
  
  KEY_BACKSPACE = 0x08,
  KEY_TAB 	= 0x09,
  KEY_DELETE 	= 0x0C,
  KEY_ENTER 	= 0x0D,
  KEY_SHIFT 	= 0x10,
  KEY_CTRL 	= 0x11,
  KEY_ALT 	= 0x12,
  KEY_PAUSE 	= 0x13,
  KEY_CAPSLOCK 	= 0x14,
  KEY_ESCAPE 	= 0x1B,
  KEY_SPACE 	= 0x20,
  
  KEY_0 	= 0x30,
  KEY_1 	= 0x31,
  KEY_2 	= 0x32,
  KEY_3 	= 0x33,
  KEY_4 	= 0x34,
  KEY_5 	= 0x35,
  KEY_6 	= 0x36,
  KEY_7 	= 0x37,
  KEY_8 	= 0x38,
  KEY_9 	= 0x39,
  
  KEY_A 	= 0x41,
  KEY_B 	= 0x42,
  KEY_C 	= 0x43,
  KEY_D 	= 0x44,
  KEY_E 	= 0x45,
  KEY_F 	= 0x46,
  KEY_G 	= 0x47,
  KEY_H 	= 0x48,
  KEY_I 	= 0x49,
  KEY_J 	= 0x4A,
  KEY_K 	= 0x4B,
  KEY_L 	= 0x4C,
  KEY_M 	= 0x4D,
  KEY_N 	= 0x4E,
  KEY_O 	= 0x4F,
  KEY_P 	= 0x50,
  KEY_Q 	= 0x51,
  KEY_R 	= 0x52,
  KEY_S 	= 0x53,
  KEY_T 	= 0x54,
  KEY_U 	= 0x55,
  KEY_V 	= 0x56,
  KEY_W		= 0x57,
  KEY_X 	= 0x58,
  KEY_Y 	= 0x59,
  KEY_Z 	= 0x5A,
};

static bool input[128];

void set_key_state(int key, bool isDown) {
  input[key] = isDown;
}

bool is_down(int key) {
  return input[key];
}
