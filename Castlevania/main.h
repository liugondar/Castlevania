#pragma once
#include "Game.h"
#include "KeyboardHandler.h"


HWND createGameWindow(HINSTANCE hInstance, int nCmdShow,
	int screenWidth, int screenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int run();
void loadResources();
void loadTextures();
void loadAnimations();
void loadSimonAnimations();

void update(DWORD dt);
void render();


class SampleKeyHander : public KeyboardHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
