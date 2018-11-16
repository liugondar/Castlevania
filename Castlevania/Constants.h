#pragma once
// huong mat. object dang nhin
enum FaceSide {
	left = -1, right = 1
};

enum State
{
	dead = -1,
	normal = 1
};

constexpr auto BRICK_2_SIZE = 32;
constexpr auto LV1_GROUND_Y = 384;

/*
	sprite constants
*/

// Sprite simon move right 1 's id
constexpr auto SPRITE_SIM_MOVE_R1 = 10001;
// Sprite simon move right 2 's id
constexpr auto SPRITE_SIM_MOVE_R2 = 10002;
// Sprite simon move right 3 's id
constexpr auto SPRITE_SIM_MOVE_R3 = 10003;

// Sprite simon sit face to right's id
constexpr auto SPRITE_SIM_SIT_R = 10004;
// Sprite simon sit face to left 's id
constexpr auto SPRITE_SIM_SIT_L = 10008;

// Sprite simon move left 1 's id
constexpr auto SPRITE_SIM_MOVE_L1 = 10005;
// Sprite simon move left 2 's id
constexpr auto SPRITE_SIM_MOVE_L2 = 10006;
// Sprite simon move left 3 's id
constexpr auto SPRITE_SIM_MOVE_L3 = 10007;

// Sprite simon hit to left 1's id
constexpr auto SPRITE_SIM_HIT_L1 = 10009;
// Sprite simon hit to left 2's id
constexpr auto SPRITE_SIM_HIT_L2 = 10010;
// Sprite simon hit to left 3's id
constexpr auto SPRITE_SIM_HIT_L3 = 10011;
// Sprite simon hit to right 1 's id
constexpr auto SPRITE_SIM_HIT_R1 = 10012;
// Sprite simon hit to right 2 's id
constexpr auto SPRITE_SIM_HIT_R2 = 10013;
// Sprite simon hit to right 3 's id
constexpr auto SPRITE_SIM_HIT_R3 = 10014;

// Sprite simon hit when sit to left 1 's id
constexpr auto SPRITE_SIM_HIT_WHEN_SIT_L1 = 10015;
// Sprite simon hit when sit to left 2 's id
constexpr auto SPRITE_SIM_HIT_WHEN_SIT_L2 = 10016;
// Sprite simon hit when sit to left 3 's id
constexpr auto SPRITE_SIM_HIT_WHEN_SIT_L3 = 10017;
// Sprite simon hit when sit to left 1 's id
constexpr auto SPRITE_SIM_HIT_WHEN_SIT_R1 = 10018;
// Sprite simon hit when sit to left 2 's id
constexpr auto SPRITE_SIM_HIT_WHEN_SIT_R2 = 10019;
// Sprite simon hit when sit to left 3 's id
constexpr auto SPRITE_SIM_HIT_WHEN_SIT_R3 = 10020;


constexpr auto SPRITE_BRICK = 40001;
constexpr auto SPRITE_BRICK_2 = 40002;

constexpr auto SPRITE_WHIP_LV1_L1 = 50001;
constexpr auto SPRITE_WHIP_LV1_L2 = 50002;
constexpr auto SPRITE_WHIP_LV1_L3 = 50003;
constexpr auto SPRITE_WHIP_LV1_R1 = 50004;
constexpr auto SPRITE_WHIP_LV1_R2 = 50005;
constexpr auto SPRITE_WHIP_LV1_R3 = 50006;

constexpr auto SPRITE_WHIP_LV2_L1 = 50011;
constexpr auto SPRITE_WHIP_LV2_L2 = 50012;
constexpr auto SPRITE_WHIP_LV2_L3 = 50013;
constexpr auto SPRITE_WHIP_LV2_R1 = 50014;
constexpr auto SPRITE_WHIP_LV2_R2 = 50015;
constexpr auto SPRITE_WHIP_LV2_R3 = 50016;

constexpr auto SPRITE_WHIP_LV3_L1 = 50021;
constexpr auto SPRITE_WHIP_LV3_L2 = 50022;
constexpr auto SPRITE_WHIP_LV3_L3 = 50023;
constexpr auto SPRITE_WHIP_LV3_R1 = 50024;
constexpr auto SPRITE_WHIP_LV3_R2 = 50025;
constexpr auto SPRITE_WHIP_LV3_R3 = 50026;

constexpr auto SPRITE_EMPTY = 60001;
constexpr auto SPRITE_BIG_CANDLE_1 = 60002;
constexpr auto SPRITE_BIG_CANDLE_2 = 60003;
constexpr auto SPRITE_HEART_ITEM = 60004;
constexpr auto SPRITE_WHIP_ITEM = 60005;
constexpr auto SPRITE_KNIFE_ITEM = 60006;


/*
	texture constants
*/

constexpr auto ID_TEX_SIMON = 101;
constexpr auto ID_TEX_EMPTY = 501;
constexpr auto ID_TEX_BIG_CANDLE = 502;		//
constexpr auto ID_TEX_WHIP = 401;
constexpr auto ID_TEX_MARIO = 0;
constexpr auto ID_TEX_ENEMY = 10;
constexpr auto ID_TEX_MISC = 20;
constexpr auto ID_TEX_BBOX = -101;		//
constexpr auto ID_TEX_BRICK_2 = 201;		//
constexpr auto ID_TEX_HEART_ITEM = 202;		//
constexpr auto ID_TEX_WHIP_ITEM = 203;
constexpr auto ID_TEX_KNIFE_ITEM = 204;

constexpr auto ID_TEX_BACKGROUND_LV1 = 301;		//
constexpr auto ID_TEX_ENTRANCE_BACKGROUND = 302;		//


/* Animation constants */

constexpr auto ANIMATION_BRICK_IDLE = 201;

constexpr auto ANIM_SIM_WALKING_RIGHT = 101;
constexpr auto ANIM_SIM_WALKING_LEFT = 111;
constexpr auto ANIM_SIM_IDLE_FACE_RIGHT = 102;
constexpr auto ANIM_SIM_IDLE_FACE_LEFT = 112;
constexpr auto ANIM_SIM_SIT_FACE_RIGHT = 103;
constexpr auto ANIM_SIM_SIT_FACE_LEFT = 113;
constexpr auto ANIM_SIM_HIT_LEFT = 121;
constexpr auto ANIM_SIM_HIT_RIGHT = 122;
constexpr auto ANIM_SIM_HIT_WHEN_SIT_LEFT = 123;
constexpr auto ANIM_SIM_HIT_WHEN_SIT_RIGHT = 124;

constexpr auto ANIM_WHIP_LV1_L = 501;
constexpr auto ANIM_WHIP_LV1_R = 502;
constexpr auto ANIM_WHIP_LV2_L = 503;
constexpr auto ANIM_WHIP_LV2_R = 504;
constexpr auto ANIM_WHIP_LV3_L = 505;
constexpr auto ANIM_WHIP_LV3_R = 506;
constexpr auto ANIM_BIG_CANDLE_IDLE = 701;
constexpr auto ANIM_HEART_ITEM_IDLE = 702;
constexpr auto ANIM_WHIP_ITEM_IDLE = 703;
constexpr auto ANIM_KNIFE_ITEM_IDLE = 706;

/*
	image resources
*/
constexpr auto TEXTURE_SIMON_PATH = L"Resources\\sprites\\simon\\simon.png";
constexpr auto TEXTURE_EMPTY_PATH = L"Resources\\sprites\\EmptySprite.png";
constexpr auto TEXTURE_WHIP_PATH = L"Resources\\sprites\\weapon\\morningstar.png";
constexpr auto TEXTURE_LVL1_BACKGROUND_PATH = L"Resources\\sprites\\background\\lv1.png";
constexpr auto TEXTURE_ENTRANCE_BACKGROUND_PATH = L"Resources\\sprites\\background\\entranceBackground.png";
constexpr auto ENTRANCE_GROUND_BRICK_SCREEN_2 = L"Resources\\sprites\\ground\\2.png";

constexpr auto TEXTURE_BIG_CANDLE_PATH = L"Resources\\sprites\\ground\\0.png";

constexpr auto TEXTURE_HEART_ITEM_PATH = L"Resources\\sprites\\item\\1.png";
constexpr auto TEXTURE_WHIP_ITEM_PATH = L"Resources\\sprites\\item\\3.png";
constexpr auto TEXTURE_KNIFE_ITEM_PATH = L"Resources\\sprites\\item\\4.png";