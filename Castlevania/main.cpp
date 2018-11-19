#include"main.h"
#include "DaggerItem.h"
#include "DaggerSubWeapon.h"
#include "BurnEffect.h"
#include "CollisionEffect.h"

Game* game;
SampleKeyHander * keyHandler;

//Create keyboard handler for main program

void SampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	GameObjectManger::getInstance()->onKeyDown(KeyCode);
}

void SampleKeyHander::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	GameObjectManger::getInstance()->onKeyUp(KeyCode);
}

void SampleKeyHander::KeyState(BYTE *states)
{
	GameObjectManger::getInstance()->keyState(states);
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
	auto textureManager = TextureManager::getInstance();

	textureManager->add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textureManager->add(ID_TEX_SIMON, TEXTURE_SIMON_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_EMPTY, TEXTURE_EMPTY_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_WHIP, TEXTURE_WHIP_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_DAGGER, TEXTURE_DAGGER_PATH, D3DCOLOR_XRGB(255, 0, 255));

	textureManager->add(ID_TEX_BIG_CANDLE, TEXTURE_BIG_CANDLE_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_BRICK_2, ENTRANCE_GROUND_BRICK_SCREEN_2);
	textureManager->add(ID_TEX_BACKGROUND_LV1, TEXTURE_LVL1_BACKGROUND_PATH);
	textureManager->add(ID_TEX_ENTRANCE_BACKGROUND, TEXTURE_ENTRANCE_BACKGROUND_PATH);

	textureManager->add(ID_TEX_HEART_ITEM, TEXTURE_HEART_ITEM_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_WHIP_ITEM, TEXTURE_WHIP_ITEM_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_KNIFE_ITEM, TEXTURE_KNIFE_ITEM_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_BURN_EFFECT, TEXTURE_BURN_EFFECT_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textureManager->add(ID_TEX_COLLISION_EFFECT, TEXTURE_COLLISION_EFFECT_PATH, D3DCOLOR_XRGB(255, 0, 255));

	auto spriteManager = SpriteManager::getInstance();
	const auto texSim = textureManager->get(ID_TEX_SIMON);

	spriteManager->add(SPRITE_SIM_MOVE_R1, 436, 2, 468, 64, texSim);
	spriteManager->add(SPRITE_SIM_MOVE_R2, 375, 2, 404, 64, texSim);
	spriteManager->add(SPRITE_SIM_MOVE_R3, 314, 2, 345, 64, texSim);

	spriteManager->add(SPRITE_SIM_MOVE_L1, 492, 2, 492 + SIM_MOVE_W, 64, texSim);
	spriteManager->add(SPRITE_SIM_MOVE_L2, 557, 2, 557 + SIM_MOVE_W, 64, texSim);
	spriteManager->add(SPRITE_SIM_MOVE_L3, 616, 2, 616 + SIM_MOVE_W, 64, texSim);


	spriteManager->add(SPRITE_SIM_SIT_R, 196, 16, 196 + SIM_SIT_W, 16 + SIM_SIT_H, texSim);
	spriteManager->add(SPRITE_SIM_SIT_L, 732, 16, 732 + SIM_SIT_W, 16 + SIM_SIT_H, texSim);

	spriteManager->add(SPRITE_SIM_HIT_L1, 792, 2, 792 + SIM_HIT_W, 2 + SIM_HIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_L2, 852, 2, 852 + SIM_HIT_W, 2 + SIM_HIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_L3, 901, 2, 901 + SIM_HIT_W, 2 + SIM_HIT_H, texSim);

	spriteManager->add(SPRITE_SIM_HIT_R1, 121, 0, 121 + 48, 0 + SIM_HIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_R2, 76, 0, 76 + 32, 0 + SIM_HIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_R3, 14, 0, 14 + 45, 0 + SIM_HIT_H, texSim);

	spriteManager->add(SPRITE_SIM_HIT_WHEN_SIT_L1, 912, 82, 912 + SIM_HIT_WHEN_SIT_W, 82 + SIM_HIT_WHEN_SIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_WHEN_SIT_L2, 492, 148, 492 + SIM_HIT_WHEN_SIT_W, 148 + SIM_HIT_WHEN_SIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_WHEN_SIT_L3, 540, 148, 540 + SIM_HIT_WHEN_SIT_W, 148 + SIM_HIT_WHEN_SIT_H, texSim);

	spriteManager->add(SPRITE_SIM_HIT_WHEN_SIT_R1, 0, 82, 0 + SIM_HIT_WHEN_SIT_W, 82 + SIM_HIT_WHEN_SIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_WHEN_SIT_R2, 436, 148, 436 + SIM_HIT_WHEN_SIT_W, 148 + SIM_HIT_WHEN_SIT_H, texSim);
	spriteManager->add(SPRITE_SIM_HIT_WHEN_SIT_R3, 376, 148, 376 + SIM_HIT_WHEN_SIT_W, 148 + SIM_HIT_WHEN_SIT_H, texSim);


	const auto texBrick2 = textureManager->get(ID_TEX_BRICK_2);
	spriteManager->add(SPRITE_BRICK_2, 0, 0, BRICK_2_SIZE, BRICK_2_SIZE, texBrick2);

	const auto texWhip = textureManager->get(ID_TEX_WHIP);
	
	spriteManager->add(SPRITE_WHIP_LV1_L1, 24, 2, 24 + 99, 2 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV1_L2, 179, 2, 179 + 63, 2 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV1_L3, 282 + WHIP_LV1_HITTING_W, 2, 282, 2 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV1_R1, 734, 2, 734 - WHIP_LV1_READY_W, 2 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV1_R2, 589, 2, 589 - WHIP_LV1_START_HIT_W, 2 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV1_R3, 430, 0, 430 + 88, 2 + SIM_HIT_H, texWhip);

	spriteManager->add(SPRITE_WHIP_LV2_L1, 24, 70, 24 + 99, 70 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV2_L2, 179, 70, 179 + 63, 70 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV2_L3, 282 + WHIP_LV2_HITTING_W, 70, 282, 70 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV2_R1, 734, 70, 734 - WHIP_LV2_READY_W, 70 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV2_R2, 589, 70, 589 - WHIP_LV2_START_HIT_W, 70 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV2_R3, 430, 70, 430 + 88, 70 + SIM_HIT_H, texWhip);


	spriteManager->add(SPRITE_WHIP_LV3_L1, 24, 138, 24 + 99, 138 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV3_L2, 179, 138, 179 + 63, 138  + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV3_L3, 250+ WHIP_LV3_HITTING_W, 138, 250, 138 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV3_R1, 734, 138, 734 - WHIP_LV3_READY_W, 138 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV3_R2, 589, 138, 589 - WHIP_LV3_START_HIT_W, 138 + SIM_HIT_H, texWhip);
	spriteManager->add(SPRITE_WHIP_LV3_R3, 430, 138, 430 + 120, 138 + SIM_HIT_H, texWhip);

	const auto texDagger = textureManager->get(ID_TEX_DAGGER);
	spriteManager->add(SPRITE_DAGGER_L, 0, 0, 32,18, texDagger);
	spriteManager->add(SPRITE_DAGGER_R, 32, 0, 64,18, texDagger);

	const auto texEmpty = textureManager->get(ID_TEX_EMPTY);
	spriteManager->add(SPRITE_EMPTY, 0, 0, 10, 10, texEmpty);

	const auto texBigCandle = textureManager->get(ID_TEX_BIG_CANDLE);
	spriteManager->add(SPRITE_BIG_CANDLE_1, 0, 0, BIG_CANDLE_WIDTH, BIG_CANDLE_HEIGHT, texBigCandle);
	spriteManager->add(SPRITE_BIG_CANDLE_2, 32, 0, 32 + BIG_CANDLE_WIDTH, BIG_CANDLE_HEIGHT, texBigCandle);

	const auto textHeart = textureManager->get(ID_TEX_HEART_ITEM);
	spriteManager->add(SPRITE_HEART_ITEM, 0, 0, 24, 20, textHeart);

	const auto texWhipItem = textureManager->get(ID_TEX_WHIP_ITEM);
	spriteManager->add(SPRITE_WHIP_ITEM, 0, 0, 32, 32, texWhipItem);

	const auto texKnifeItem = textureManager->get(ID_TEX_KNIFE_ITEM);
	spriteManager->add(SPRITE_KNIFE_ITEM, 0, 0, DAGGER_ITEM_W, DAGGER_ITEM_H, texKnifeItem);

	const auto texBurnEffect = textureManager->get(ID_TEX_BURN_EFFECT);
	spriteManager->add(SPRITE_BURN_EFFECT1, 0, 0, 43, 44, texBurnEffect);
	spriteManager->add(SPRITE_BURN_EFFECT2, 43, 0, 86, 44, texBurnEffect);
	spriteManager->add(SPRITE_BURN_EFFECT3, 86, 0, 129, 44, texBurnEffect);

	const auto texCollisionEffect = textureManager->get(ID_TEX_COLLISION_EFFECT);
	spriteManager->add(SPRITE_COLLISION_EFFECT, 0, 0, 16, 20, texCollisionEffect);
	}

void loadAnimations()
{
	auto animationManager = AnimationManager::getInstance();
	auto animation = new Animation(100);
	animation->add(SPRITE_BRICK_2);
	animationManager->add(ANIMATION_BRICK_IDLE, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_WHIP_LV1_L1);
	animation->add(SPRITE_WHIP_LV1_L2);
	animation->add(SPRITE_WHIP_LV1_L3);
	animation->add(SPRITE_EMPTY);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_WHIP_LV1_L, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_WHIP_LV1_R1);
	animation->add(SPRITE_WHIP_LV1_R2);
	animation->add(SPRITE_WHIP_LV1_R3);
	animation->add(SPRITE_EMPTY);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_WHIP_LV1_R, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_WHIP_LV2_L1);
	animation->add(SPRITE_WHIP_LV2_L2);
	animation->add(SPRITE_WHIP_LV2_L3);
	animation->add(SPRITE_EMPTY);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_WHIP_LV2_L, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_WHIP_LV2_R1);
	animation->add(SPRITE_WHIP_LV2_R2);
	animation->add(SPRITE_WHIP_LV2_R3);
	animation->add(SPRITE_EMPTY);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_WHIP_LV2_R, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_WHIP_LV3_L1);
	animation->add(SPRITE_WHIP_LV3_L2);
	animation->add(SPRITE_WHIP_LV3_L3);
	animation->add(SPRITE_EMPTY);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_WHIP_LV3_L, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_WHIP_LV3_R1);
	animation->add(SPRITE_WHIP_LV3_R2);
	animation->add(SPRITE_WHIP_LV3_R3);
	animation->add(SPRITE_EMPTY);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_WHIP_LV3_R, animation);

	animation = new Animation(100);
	animation->add(SPRITE_DAGGER_L);
	animationManager->add(ANIM_DAGGER_L, animation);
	animation = new Animation(100);
	animation->add(SPRITE_DAGGER_R);
	animationManager->add(ANIM_DAGGER_R, animation);

	animation = new Animation(BIG_CANDLE_ANIMATION_FRAME_TIME);
	animation->add(SPRITE_BIG_CANDLE_1);
	animation->add(SPRITE_BIG_CANDLE_2);
	animationManager->add(ANIM_BIG_CANDLE_IDLE, animation);

	animation = new Animation(100);
	animation->add(SPRITE_HEART_ITEM);
	animationManager->add(ANIM_HEART_ITEM_IDLE, animation);

	animation = new Animation(100);
	animation->add(SPRITE_WHIP_ITEM);
	animationManager->add(ANIM_WHIP_ITEM_IDLE, animation);

	animation = new Animation(100);
	animation->add(SPRITE_KNIFE_ITEM);
	animationManager->add(ANIM_DAGGER_ITEM_IDLE, animation);

	animation = new Animation(100);
	animation->add(SPRITE_COLLISION_EFFECT);
	animationManager->add(ANIM_COLLISION_EFFECT, animation);

	animation = new Animation(100);
	animation->add(SPRITE_BURN_EFFECT1);
	animation->add(SPRITE_BURN_EFFECT2);
	animation->add(SPRITE_BURN_EFFECT3);
	animationManager->add(ANIM_BURN_EFFECT, animation);

	/* Simon animations */
	loadSimonAnimations();
}

void loadSimonAnimations()
{
	auto animationManager = AnimationManager::getInstance();
	auto animation = new Animation(100);
	/// Moving anim
	animation->add(SPRITE_SIM_MOVE_R1);
	animation->add(SPRITE_SIM_MOVE_R2);
	animation->add(SPRITE_SIM_MOVE_R3);
	animationManager->add(ANIM_SIM_WALKING_R, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIM_MOVE_L1);
	animation->add(SPRITE_SIM_MOVE_L2);
	animation->add(SPRITE_SIM_MOVE_L3);
	animationManager->add(ANIM_SIM_WALKING_L, animation);

	/// Hitting anim
	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_SIM_HIT_L1);
	animation->add(SPRITE_SIM_HIT_L2);
	animation->add(SPRITE_SIM_HIT_L3);
	animation->add(SPRITE_SIM_MOVE_L1);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_HITTING_L, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_SIM_HIT_R1);
	animation->add(SPRITE_SIM_HIT_R2);
	animation->add(SPRITE_SIM_HIT_R3);
	animation->add(SPRITE_SIM_MOVE_R1);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_HITTING_R, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_L1);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_L2);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_L3);
	animation->add(SPRITE_SIM_SIT_L);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_HIT_WHEN_SITTING_L, animation);

	animation = new Animation(SIMON_HITTING_TIME);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_R1);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_R2);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_R3);
	animation->add(SPRITE_SIM_SIT_R);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_HIT_WHEN_SITTING_R, animation);

	/// throwing anim
	animation = new Animation(SIMON_THROWING_TIME);
	animation->add(SPRITE_SIM_HIT_L1);
	animation->add(SPRITE_SIM_HIT_L2);
	animation->add(SPRITE_SIM_HIT_L3);
	animation->add(SPRITE_SIM_MOVE_L1);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_THROW_L, animation);

	animation = new Animation(SIMON_THROWING_TIME);
	animation->add(SPRITE_SIM_HIT_R1);
	animation->add(SPRITE_SIM_HIT_R2);
	animation->add(SPRITE_SIM_HIT_R3);
	animation->add(SPRITE_SIM_MOVE_R1);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_THROW_R, animation);

	animation = new Animation(SIMON_THROWING_TIME);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_L1);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_L2);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_L3);
	animation->add(SPRITE_SIM_SIT_L);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_THROW_WHEN_SIT_L, animation);

	animation = new Animation(SIMON_THROWING_TIME);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_R1);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_R2);
	animation->add(SPRITE_SIM_HIT_WHEN_SIT_R3);
	animation->add(SPRITE_SIM_SIT_R);
	animation->setIsOneTimeAnim(true);
	animationManager->add(ANIM_SIM_THROW_WHEN_SIT_R, animation);

	/// Idle anim
	animation = new Animation(100);
	animation->add(SPRITE_SIM_MOVE_R1);
	animationManager->add(ANIM_SIM_IDLE_R, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIM_MOVE_L1);
	animationManager->add(ANIM_SIM_IDLE_L, animation);

	animation = new Animation(100);
	animation->add(SPRITE_SIM_SIT_R);
	animationManager->add(ANIM_SIM_SITTING_R, animation);
	animation = new Animation(100);
	animation->add(SPRITE_SIM_SIT_L);
	animationManager->add(ANIM_SIM_SITTING_L, animation);

}

void loadGameObjects()
{
	auto gameObjectManager = GameObjectManger::getInstance();
	gameObjectManager->loadGameObjects();
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