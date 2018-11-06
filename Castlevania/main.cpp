#include"main.h"

Game* game;
Mario* mario;
Goomba* goomba;
Simon* simon;
SampleKeyHander * keyHandler;

 //Create keyboard handler for main program

void SampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	simon->handleOnKeyDown(KeyCode);
}

void SampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	simon->handleOnKeyRelease(KeyCode);
}

void SampleKeyHander::KeyState(BYTE *states)
{
	simon->handleOnKeyPress(states);
}

/// Create a window then display and running until exit message send
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = createGameWindow(hInstance, nCmdShow,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::getInstance();
	game->init(hWnd);

	keyHandler = new SampleKeyHander();
	game->initKeyboard(keyHandler);

	loadResources();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	run();

	return 0;
}

HWND createGameWindow(HINSTANCE hInstance, int nCmdShow,
	int screenWidth, int screenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			screenWidth,
			screenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);
	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int run() {
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		auto now = GetTickCount();
		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render

		auto dt = now - frameStart;
		if (dt >= tickPerFrame) {
			frameStart = now;
			game->processKeyboard();
			update(dt);
			render();
		}
		else Sleep(tickPerFrame - dt);
	}
	return 1;
}

void loadResources() {

	loadTextures();
	loadAnimations();
	loadGameObjects();

}

void loadTextures()
{
	TextureManager* textureManager = TextureManager::getInstance();

	textureManager->add(ID_TEX_MISC, L"textures\\misc.png",
		D3DCOLOR_XRGB(176, 224, 248));
	textureManager->add(ID_TEX_BBOX, L"textures\\bbox.png",
		D3DCOLOR_XRGB(255, 255, 255));
	textureManager->add(ID_TEX_SIMON, TEXTURE_SIMON_PATH,
		D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_BRICK_2, ENTRANCE_GROUND_BRICK_SCREEN_2);
	textureManager->add(ID_TEX_BACKGROUND_LV1, TEXTURE_LVL1_BACKGROUND_PATH);
	textureManager->add(ID_TEX_ENTRANCE_BACKGROUND, TEXTURE_ENTRANCE_BACKGROUND_PATH);

	auto spriteManager = SpriteManager::getInstance();
	auto textureSimon = textureManager->get(ID_TEX_SIMON);
	// spriteManager->add(SPRITE_SIMON_MOVING_RIGHT_1, 305*2, 9*2, 305*2 + SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);
	// spriteManager->add(SPRITE_SIMON_MOVING_RIGHT_2, 279*2, 9*2, 279*2 + SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);
	// spriteManager->add(SPRITE_SIMON_MOVING_RIGHT_3, 251*2, 9*2, 254*2 + SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);
	// spriteManager->add(SPRITE_SIMON_MOVING_LEFT_1, 979, 18, 979+ SIMON_MOVING_WIDTH, 16+ SIMON_MOVING_HEIGHT, textureSimon);
	// spriteManager->add(SPRITE_SIMON_MOVING_LEFT_2, 1033, 18, 1033+ SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);
	// spriteManager->add(SPRITE_SIMON_MOVING_LEFT_3, 1083, 18, 1083+ SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);


	spriteManager->add(SPRITE_SIMON_MOVING_RIGHT_1, 432, 0, 432 + SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_MOVING_RIGHT_2, 373, 0, 373 + SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_MOVING_RIGHT_3, 311, 0, 311 + SIMON_MOVING_WIDTH, 16 + SIMON_MOVING_HEIGHT, textureSimon);

	spriteManager->add(SPRITE_SIMON_MOVING_LEFT_1, 491, 0, 491 + SIMON_MOVING_WIDTH, 0 + SIMON_MOVING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_MOVING_LEFT_2, 552, 0, 552 + SIMON_MOVING_WIDTH, 0 + SIMON_MOVING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_MOVING_LEFT_3, 604, 0, 604 + SIMON_MOVING_WIDTH, 0 + SIMON_MOVING_HEIGHT, textureSimon);


	spriteManager->add(SPRITE_SIMON_SIT_FACE_RIGHT, 194, 16, 194 + SIMON_SITTING_WIDTH, 16 + SIMON_SITTING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_SIT_FACE_LEFT, 728, 16, 728 + SIMON_SITTING_WIDTH, 16 + SIMON_SITTING_HEIGHT, textureSimon);

	spriteManager->add(SPRITE_SIMON_HITTING_LEFT1, 791, 0, 791 + SIMON_HITTING_WIDTH, 0 + SIMON_HITTING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_HITTING_LEFT2, 850, 0, 850 + SIMON_HITTING_WIDTH, 0 + SIMON_HITTING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_HITTING_LEFT3, 898, 0, 898 + SIMON_HITTING_WIDTH, 0 + SIMON_HITTING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_HITTING_RIGHT1, 118, 0, 118 + SIMON_HITTING_WIDTH, 0 + SIMON_HITTING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_HITTING_RIGHT2, 67, 0, 67+ SIMON_HITTING_WIDTH, 0 + SIMON_HITTING_HEIGHT, textureSimon);
	spriteManager->add(SPRITE_SIMON_HITTING_RIGHT3, 11, 0, 11 + SIMON_HITTING_WIDTH, 0 + SIMON_HITTING_HEIGHT, textureSimon);


	auto texMisc = textureManager->get(ID_TEX_MISC);
	spriteManager->add(SPRITE_BRICK, 408, 225, 424, 241, texMisc);

	auto texBrick2 = textureManager->get(ID_TEX_BRICK_2);
	spriteManager->add(SPRITE_BRICK_2, 0, 0, BRICK_2_SIZE, BRICK_2_SIZE, texBrick2);
}

void loadAnimations()
{
	auto animationManager = AnimationManager::getInstance();
	auto animation = new Animation(100);
	animation->add(SPRITE_BRICK_2);
	animationManager->add(ANIMATION_BRICK_IDLE, animation);

	/* Simon animations */
	loadSimonAnimations();
}

void loadSimonAnimations()
{
	auto animationManager = AnimationManager::getInstance();
	auto animation = new Animation(100);
	animation->add(SPRITE_SIMON_MOVING_RIGHT_1);
	animation->add(SPRITE_SIMON_MOVING_RIGHT_2);
	animation->add(SPRITE_SIMON_MOVING_RIGHT_3);
	animationManager->add(ANIMATION_SIMON_WALKING_RIGHT, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIMON_MOVING_LEFT_1);
	animation->add(SPRITE_SIMON_MOVING_LEFT_2);
	animation->add(SPRITE_SIMON_MOVING_LEFT_3);
	animationManager->add(ANIMATION_SIMON_WALKING_LEFT, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_SIMON_HITTING_LEFT1);
	animation->add(SPRITE_SIMON_HITTING_LEFT2);
	animation->add(SPRITE_SIMON_HITTING_LEFT3);
	animation->add(SPRITE_SIMON_MOVING_LEFT_1);
	animationManager->add(ANIMATION_SIMON_HITTING_LEFT, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_SIMON_HITTING_RIGHT1);
	animation->add(SPRITE_SIMON_HITTING_RIGHT2);
	animation->add(SPRITE_SIMON_HITTING_RIGHT3);
	animation->add(SPRITE_SIMON_MOVING_RIGHT_1);
	animationManager->add(ANIMATION_SIMON_HITTING_RIGHT, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIMON_MOVING_RIGHT_1);
	animationManager->add(ANIMATION_SIMON_IDLE_FACE_RIGHT, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIMON_MOVING_LEFT_1);
	animationManager->add(ANIMATION_SIMON_IDLE_FACE_LEFT, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIMON_SIT_FACE_RIGHT);
	animationManager->add(ANIMATION_SIMON_SIT_FACE_RIGHT, animation);
	animation = new Animation(100);
	animation->add(SPRITE_SIMON_SIT_FACE_LEFT);
	animationManager->add(ANIMATION_SIMON_SIT_FACE_LEFT, animation);
}

void loadGameObjects()
{

	simon = new Simon();
	Simon::addAnimation(ANIMATION_SIMON_WALKING_RIGHT);
	Simon::addAnimation(ANIMATION_SIMON_WALKING_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_IDLE_FACE_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_IDLE_FACE_RIGHT);
	Simon::addAnimation(ANIMATION_SIMON_SIT_FACE_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_SIT_FACE_RIGHT);
	Simon::addAnimation(ANIMATION_SIMON_HITTING_LEFT);
	Simon::addAnimation(ANIMATION_SIMON_HITTING_RIGHT);

	simon->setPosition(10.f, 100.f);
	simon->setState(STATE_SIMON_IDLE);

	GameObjectManger::getInstance()->addSimon(simon);

	Brick::addAnimation(ANIMATION_BRICK_IDLE);

	for (int i = 0; i < 50; i++)
	{
		auto brick = new Brick();
		brick->setPosition(0 + i * 16.0f, 384);
		GameObjectManger::getInstance()->addBrick(brick);
	}
}


void update(DWORD dt) {
	GameObjectManger::getInstance()->update(dt);
}

void render() {
	LPDIRECT3DDEVICE9 d3ddv = game->getDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->getBackBuffer();
	LPD3DXSPRITE spriteHandler = game->getSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		GameObjectManger::getInstance()->render();
		spriteHandler->End();
		d3ddv->EndScene();
	}
	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}