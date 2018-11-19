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


constexpr auto SPRITE_BRICK_2 = 20001;

constexpr auto SPRITE_WHIP_LV1_L1 = 30001;
constexpr auto SPRITE_WHIP_LV1_L2 = 30002;
constexpr auto SPRITE_WHIP_LV1_L3 = 30003;
constexpr auto SPRITE_WHIP_LV1_R1 = 30004;
constexpr auto SPRITE_WHIP_LV1_R2 = 30005;
constexpr auto SPRITE_WHIP_LV1_R3 = 30006;

constexpr auto SPRITE_WHIP_LV2_L1 = 30011;
constexpr auto SPRITE_WHIP_LV2_L2 = 30012;
constexpr auto SPRITE_WHIP_LV2_L3 = 30013;
constexpr auto SPRITE_WHIP_LV2_R1 = 30014;
constexpr auto SPRITE_WHIP_LV2_R2 = 30015;
constexpr auto SPRITE_WHIP_LV2_R3 = 30016;

constexpr auto SPRITE_WHIP_LV3_L1 = 30021;
constexpr auto SPRITE_WHIP_LV3_L2 = 30022;
constexpr auto SPRITE_WHIP_LV3_L3 = 30023;
constexpr auto SPRITE_WHIP_LV3_R1 = 30024;
constexpr auto SPRITE_WHIP_LV3_R2 = 30025;
constexpr auto SPRITE_WHIP_LV3_R3 = 30026;

constexpr auto SPRITE_DAGGER_L= 40001;
constexpr auto SPRITE_DAGGER_R= 40002;

constexpr auto SPRITE_EMPTY = 70001;
constexpr auto SPRITE_BIG_CANDLE_1 = 50002;
constexpr auto SPRITE_BIG_CANDLE_2 = 50003;
constexpr auto SPRITE_HEART_ITEM = 60001;
constexpr auto SPRITE_WHIP_ITEM = 60002;
constexpr auto SPRITE_KNIFE_ITEM = 60003;

constexpr auto SPRITE_HIT_AFFECT = 80001;
 
/*
	texture constants
*/

constexpr auto ID_TEX_SIMON = 101;
constexpr auto ID_TEX_EMPTY = 701;
constexpr auto ID_TEX_BIG_CANDLE = 502;		//
constexpr auto ID_TEX_WHIP = 301;
constexpr auto ID_TEX_DAGGER= 401;
constexpr auto ID_TEX_BBOX = -101;		//
constexpr auto ID_TEX_BRICK_2 = 201;		//
constexpr auto ID_TEX_HEART_ITEM = 601;		//
constexpr auto ID_TEX_WHIP_ITEM = 602;
constexpr auto ID_TEX_KNIFE_ITEM = 603;
constexpr auto ID_TEX_HIT_AFFECT = 801;

constexpr auto ID_TEX_BACKGROUND_LV1 = 1;		//
constexpr auto ID_TEX_ENTRANCE_BACKGROUND = 2;		//


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
constexpr auto ANIM_SIM_THROW_L = 125;
constexpr auto ANIM_SIM_THROW_R = 126;
constexpr auto ANIM_SIM_THROW_WHEN_SIT_L = 127;
constexpr auto ANIM_SIM_THROW_WHEN_SIT_R = 128;

constexpr auto ANIM_WHIP_LV1_L = 301;
constexpr auto ANIM_WHIP_LV1_R = 302;
constexpr auto ANIM_WHIP_LV2_L = 303;
constexpr auto ANIM_WHIP_LV2_R = 304;
constexpr auto ANIM_WHIP_LV3_L = 305;
constexpr auto ANIM_WHIP_LV3_R = 306;
constexpr auto ANIM_DAGGER_L= 407;
constexpr auto ANIM_DAGGER_R= 408;

constexpr auto ANIM_HIT_AFFECT = 801;

constexpr auto ANIM_BIG_CANDLE_IDLE = 501;
constexpr auto ANIM_HEART_ITEM_IDLE = 601;
constexpr auto ANIM_WHIP_ITEM_IDLE = 602;
constexpr auto ANIM_KNIFE_ITEM_IDLE = 603;


/*
	image resources
*/
constexpr auto TEXTURE_SIMON_PATH = L"Resources\\sprites\\simon\\simon.png";
constexpr auto TEXTURE_EMPTY_PATH = L"Resources\\sprites\\EmptySprite.png";
constexpr auto TEXTURE_WHIP_PATH = L"Resources\\sprites\\weapon\\morningstar.png";
constexpr auto TEXTURE_DAGGER_PATH= L"Resources\\sprites\\weapon\\1.png";
constexpr auto TEXTURE_LVL1_BACKGROUND_PATH = L"Resources\\sprites\\background\\lv1.png";
constexpr auto TEXTURE_ENTRANCE_BACKGROUND_PATH = L"Resources\\sprites\\background\\entranceBackground.png";
constexpr auto ENTRANCE_GROUND_BRICK_SCREEN_2 = L"Resources\\sprites\\ground\\2.png";

constexpr auto TEXTURE_BIG_CANDLE_PATH = L"Resources\\sprites\\ground\\0.png";

constexpr auto TEXTURE_HIT_AFFECTS= L"Resources\\sprites\\other\\1.png";

constexpr auto TEXTURE_HEART_ITEM_PATH = L"Resources\\sprites\\item\\1.png";
constexpr auto TEXTURE_WHIP_ITEM_PATH = L"Resources\\sprites\\item\\3.png";
constexpr auto TEXTURE_KNIFE_ITEM_PATH = L"Resources\\sprites\\item\\4.png";