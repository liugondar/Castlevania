#ifndef __INPUT_H__
#define	__INPUT_H__

#include <dinput.h>

int InitDirectInput();
int InitKeyboard(HWND);
void PollKeyboard();

int IsKeyDown(int key);	

int IsKeyRelease(int key);
int IsKeyPress(int key);

void KillKeyboard();

#endif // !__INPUT_H__