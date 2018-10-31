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

public:
	void init(HWND hWnd);
	void draw(float x, float y, LPDIRECT3DTEXTURE9 texture,
		int left,int right, int top, int bottom,int alpha=255);

	static Game * getInstance() {
		if (instance == NULL) instance = new Game();
		return instance;
	};

	// handle direct x 
	LPDIRECT3DDEVICE9 getDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 getBackBuffer() { return backBuffer; }
	LPD3DXSPRITE getSpriteHandler() { return this->spriteHandler; }

	// Handle keyboard
	void processKeyboard();
	int isKeyDown(int keyCode);
	void initKeyboard(KeyboardHandler* handler);

	~Game();
};

