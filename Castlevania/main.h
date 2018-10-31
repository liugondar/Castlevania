#pragma once
#include "Game.h"
#include "KeyboardHandler.h"

#include "GameObject.h"
#include "GameObjectManger.h"
#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"

#include "AnimationManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"

constexpr auto WINDOW_CLASS_NAME = LR"(SampleWindow)";
constexpr auto MAIN_WINDOW_TITLE = LR"(01 - Skeleton)";

constexpr auto BRICK_TEXTURE_PATH = LR"(brick.png)";
constexpr auto MARIO_TEXTURE_PATH = LR"(mario.png)";

constexpr auto SCREEN_WIDTH = 320;
constexpr auto SCREEN_HEIGHT = 240;

constexpr auto MAX_FRAME_RATE = 90;
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)

HWND createGameWindow(HINSTANCE hInstance, int nCmdShow,
	int screenWidth, int screenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int run();
void loadResources();
void update(DWORD dt);
void render();


class SampleKeyHander : public KeyboardHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
