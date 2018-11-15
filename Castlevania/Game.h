#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include"debug.h"
#include <dinput.h>
#include <vector>


#include "KeyboardHandler.h"

#define KEYBOARD_BUFFER_SIZE 1024
#define DIRECTINPUT_VERSION 0x0800
#define SCREEN_LEFT 0

constexpr auto WINDOW_CLASS_NAME = LR"(Castlevania)";
constexpr auto MAIN_WINDOW_TITLE = LR"(Castlevania)";

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;

constexpr auto MAX_FRAME_RATE = 90;
// #define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0) //black
 //#define BACKGROUND_COLOR D3DCOLOR_XRGB(255,255,255) //white
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)


class Game
{
private:
	static Game* instance;
	HWND hWnd; // Window handle

	LPDIRECT3D9 d3d = NULL; // direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;// Direct 3d device object

	LPDIRECT3DSURFACE9 backBuffer = NULL; 
	LPD3DXSPRITE spriteHandler = NULL;  	// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 
	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	KeyboardHandler* keyHandler;

	float xCamera;
	float yCamera;

public:
	void init(HWND hWnd);
	void draw(float x, float y, LPDIRECT3DTEXTURE9 texture,
		int left, int top, int right, int bottom, int alpha
	);

	static Game * getInstance() {
		if (instance == NULL) instance = new Game();
		return instance;
	};

	// handle direct x 
	LPDIRECT3DDEVICE9 getDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 getBackBuffer() { return backBuffer; }
	LPD3DXSPRITE getSpriteHandler() { return this->spriteHandler; }

	void initKeyboard(KeyboardHandler* handler);
	int isKeyDown(int KeyCode);
	int isKeyUp(int keyCode);
	void processKeyboard();
	void setCameraPosition(float x, float y);
	void getCameraPosition(float & x, float & y);

	~Game();
};

