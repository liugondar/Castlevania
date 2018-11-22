#pragma once
#include "Game.h"
#include "Constants.h"
#include "KeyboardHandler.h"

#include "GameObject.h"
#include "GameObject.h"
#include "Simon.h"
#include "Whip.h"
#include "BigCandle.h"

#include "AnimationManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"



HWND createGameWindow(HINSTANCE hInstance, int nCmdShow,
	int screenWidth, int screenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int run();
void loadResources();
void loadTextures();
void loadAnimations();
void loadSimonAnimations();
void loadGameObjects();


void update(DWORD dt);
void render();


class SampleKeyHander : public KeyboardHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
