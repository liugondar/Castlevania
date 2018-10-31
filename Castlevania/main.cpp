#include"main.h"

Game* game;
Mario* mario;
Goomba* goomba;
SampleKeyHander * keyHandler;

/// Create keyboard handler for main program

void SampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->setState(MARIO_STATE_JUMP);
		break;
	}
}

void SampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}

void SampleKeyHander::KeyState(BYTE *states)
{
	if (game->isKeyDown(DIK_RIGHT)) {

		mario->setState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->isKeyDown(DIK_LEFT)) {
		mario->setState(MARIO_STATE_WALKING_LEFT);
	}
	else {
mario->setState(MARIO_STATE_IDLE);

	}
}

/// Create a window then display and running until exit message send
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = createGameWindow(hInstance, nCmdShow,
		320, 240);

	game = Game::getInstance();
	game->init(hWnd);

	keyHandler = new SampleKeyHander();
	game->initKeyboard(keyHandler);

	loadResources();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 
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
			update( dt);
			render();
		}
		else Sleep(tickPerFrame - dt);
	}
	return 1;
}

void loadResources() {

	TextureManager* textureManager = TextureManager::getInstance();

	textureManager->add(ID_TEX_MARIO, L"textures\\mario.png",
		D3DCOLOR_XRGB(176, 224, 248));
	textureManager->add(ID_TEX_MISC, L"textures\\misc.png",
		D3DCOLOR_XRGB(176, 224, 248));
	textureManager->add(ID_TEX_BBOX, L"textures\\bbox.png",
		D3DCOLOR_XRGB(255, 255, 255));
	textureManager->add(ID_TEX_ENEMY, L"textures\\enemies.png",
		D3DCOLOR_XRGB(3, 26, 110));



	////textures->Add(ID_ENEMY_TEXTURE, L"textures\\enemies.png", D3DCOLOR_XRGB(156, 219, 239));
	////textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(156, 219, 239));

	auto spriteManager = SpriteManager::getInstance();
	auto animationManager = AnimationManager::getInstance();

	auto textureMario = textureManager->get(ID_TEX_MARIO);
	spriteManager->add(SPRITE_MARIO_FACE_RIGHT_1, 246, 154, 259, 181, textureMario);
	spriteManager->add(SPRITE_MARIO_FACE_RIGHT_2, 275, 154, 290, 181, textureMario);
	spriteManager->add(SPRITE_MARIO_FACE_RIGHT_3, 304, 154, 321, 181, textureMario);

	spriteManager->add(SPRITE_MARIO_FACE_LEFT_1, 186, 154, 199, 181, textureMario);
	spriteManager->add(SPRITE_MARIO_FACE_LEFT_2, 155, 154, 170, 181, textureMario);
	spriteManager->add(SPRITE_MARIO_FACE_LEFT_3, 125, 154, 140, 181, textureMario);

	auto textureEnemies= textureManager->get(ID_TEX_ENEMY);
	spriteManager->add(SPRITE_GOOMBA_GO_LEFT, 5, 14, 21, 29, textureEnemies);
	spriteManager->add(SPRITE_GOOMBA_GO_RIGHT, 25, 14, 41, 29, textureEnemies);
	spriteManager->add(SPRITE_GOOMBA_DIE, 45, 21, 61, 29, textureEnemies);

	auto texMisc = textureManager->get(ID_TEX_MISC);
	spriteManager->add(SPRITE_BRICK, 408, 225, 424, 241, texMisc);

	auto animation = new Animation(100);
	animation->add(SPRITE_MARIO_FACE_LEFT_1);
	animation->add(SPRITE_MARIO_FACE_LEFT_2);
	animation->add(SPRITE_MARIO_FACE_LEFT_3);

	animationManager->add(ANIMATION_MARIO_FACE_LEFT,animation);

	animation = new Animation(100);
	animation->add(SPRITE_MARIO_FACE_RIGHT_1);
	animation->add(SPRITE_MARIO_FACE_RIGHT_2);
	animation->add(SPRITE_MARIO_FACE_RIGHT_3);
	animationManager->add(ANIMATION_MARIO_FACE_RIGHT, animation);

	animation = new Animation(100);
	animation->add(SPRITE_MARIO_FACE_LEFT_1);
	animationManager->add(ANIMATION_MARIO_IDLE_LEFT,animation);

	animation = new Animation(100);
	animation->add(SPRITE_MARIO_FACE_RIGHT_1);
	animationManager->add(ANIMATION_MARIO_IDLE_RIGHT,animation);

	animation = new Animation(1000);
	animation->add(SPRITE_GOOMBA_DIE);
	animationManager->add(ANIMATION_GOOMBA_DEAD, animation);

	animation = new Animation(300);
	animation->add(SPRITE_GOOMBA_GO_LEFT);
	animation->add(SPRITE_GOOMBA_GO_RIGHT);
	animationManager->add(ANIMATION_GOOMBA_WALKING, animation);

	animation = new Animation(100);
	animation->add(SPRITE_BRICK);
	animationManager->add(ANIMATION_BRICK_IDLE, animation);

	mario = new Mario();
	Mario::addAnimation(ANIMATION_MARIO_FACE_LEFT);
	Mario::addAnimation(ANIMATION_MARIO_FACE_RIGHT);
	Mario::addAnimation(ANIMATION_MARIO_IDLE_LEFT);
	Mario::addAnimation(ANIMATION_MARIO_IDLE_RIGHT);

	mario->setPosition(10.f, 100.f);

	Brick::addAnimation(ANIMATION_BRICK_IDLE);

	for (int i = 0; i < 5; i++)
	{
		auto *brick = new Brick();
		brick->setPosition(100 + i * 48.0f, 74);
		GameObjectManger::getInstance()->addBrick(brick);

		brick = new Brick();
		brick->setPosition(100 + i * 48.0f, 90);
		GameObjectManger::getInstance()->addBrick(brick);

		brick = new Brick();
		brick->setPosition(84 + i * 48.0f, 90);
		GameObjectManger::getInstance()->addBrick(brick);
	}

	for (int i = 0; i < 20; i++)
	{
		auto brick = new Brick();
		brick->setPosition(0 + i * 16.0f, 150);
		GameObjectManger::getInstance()->addBrick(brick);
	}
		auto brick = new Brick();
		brick->setPosition(0 + 250.f, 135);
		GameObjectManger::getInstance()->addBrick(brick);
	// and Goombas 
	for (int i = 0; i < 1; i++)
	{
		goomba = new Goomba();
		goomba->addAnimation(ANIMATION_GOOMBA_DEAD);
		goomba->addAnimation(ANIMATION_GOOMBA_WALKING);
		goomba->setPosition(10, 135);
		goomba->setState(GOOMBA_STATE_WALKING);
		GameObjectManger::getInstance()->addGomba(goomba);
	}

	GameObjectManger::getInstance()->init(mario);
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