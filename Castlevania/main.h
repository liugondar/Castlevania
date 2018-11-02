#pragma once
#include "Game.h"
#include "Constants.h"
#include "KeyboardHandler.h"
#include "Input.h"

#include "GameObject.h"
#include "GameObjectManger.h"
#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "Simon.h"

#include "AnimationManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"

constexpr auto WINDOW_CLASS_NAME = LR"(Castlevania)";
constexpr auto MAIN_WINDOW_TITLE = LR"(Castlevania)";

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;

constexpr auto MAX_FRAME_RATE = 90;
// #define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0) //black
 //#define BACKGROUND_COLOR D3DCOLOR_XRGB(255,255,255) //white
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)


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
