#pragma once
// huong mat. object dang nhin
enum FaceSide {
	left=-1,right=1
};

constexpr auto BRICK_2_SIZE = 32;
constexpr auto LV1_GROUND_Y = 384;

/*
	sprite constants
*/

constexpr auto SPRITE_MARIO_FACE_LEFT_1 = 20001;
constexpr auto SPRITE_MARIO_FACE_LEFT_2 = 20002;
constexpr auto SPRITE_MARIO_FACE_LEFT_3 = 20003;
constexpr auto SPRITE_MARIO_FACE_RIGHT_1 =20011;
constexpr auto SPRITE_MARIO_FACE_RIGHT_2 = 20012;
constexpr auto SPRITE_MARIO_FACE_RIGHT_3 = 20013;

constexpr auto SPRITE_BRICK = 40001;
constexpr auto SPRITE_BRICK_2 = 40002;
constexpr auto SPRITE_GOOMBA_GO_LEFT = 30001;
constexpr auto SPRITE_GOOMBA_GO_RIGHT = 30011;
constexpr auto SPRITE_GOOMBA_DIE = 30021;

constexpr auto SPRITE_WHIP_LEFT_LV1_1 = 50001;
constexpr auto SPRITE_WHIP_LEFT_LV1_2 = 50002;
constexpr auto SPRITE_WHIP_LEFT_LV1_3 = 50003;
constexpr auto SPRITE_WHIP_RIGHT_LV1_1 = 50004;
constexpr auto SPRITE_WHIP_RIGHT_LV1_2 = 50005;
constexpr auto SPRITE_WHIP_RIGHT_LV1_3 = 50006;

constexpr auto SPRITE_EMPTY = 60001;
constexpr auto SPRITE_BIG_CANDLE_1 = 60002;
constexpr auto SPRITE_BIG_CANDLE_2 = 60003;

/* 
	texture constants
*/

constexpr auto ID_TEX_SIMON = 101;
constexpr auto ID_TEX_EMPTY= 501;
constexpr auto ID_TEX_BIG_CANDLE= 502;		//
constexpr auto ID_TEX_WHIP = 401;
constexpr auto ID_TEX_MARIO = 0;
constexpr auto ID_TEX_ENEMY = 10;
constexpr auto ID_TEX_MISC = 20;
constexpr auto ID_TEX_BBOX = -101;		//
constexpr auto ID_TEX_BRICK_2= 201;		//
constexpr auto ID_TEX_BACKGROUND_LV1=301;		//
constexpr auto ID_TEX_ENTRANCE_BACKGROUND= 302;		//


/* Animation constans */
constexpr auto ANIMATION_MARIO_IDLE = 100;
constexpr auto ANIMATION_MARIO_IDLE_LEFT = 101;
constexpr auto ANIMATION_MARIO_IDLE_RIGHT = 102;
constexpr auto ANIMATION_MARIO_FACE_LEFT = 103;
constexpr auto ANIMATION_MARIO_FACE_RIGHT = 104;

constexpr auto ANIMATION_BRICK_IDLE = 201;
constexpr auto ANIMATION_GOOMBA_WALKING = 301;
constexpr auto ANIMATION_GOOMBA_DEAD = 302;

constexpr auto ANIMATION_SIMON_WALKING_RIGHT = 101;
constexpr auto ANIMATION_SIMON_WALKING_LEFT= 111;
constexpr auto ANIMATION_SIMON_IDLE_FACE_RIGHT = 102;
constexpr auto ANIMATION_SIMON_IDLE_FACE_LEFT= 112;
constexpr auto ANIMATION_SIMON_SIT_FACE_RIGHT = 103;
constexpr auto ANIMATION_SIMON_SIT_FACE_LEFT= 113;
constexpr auto ANIMATION_SIMON_HITTING_LEFT= 121;
constexpr auto ANIMATION_SIMON_HITTING_RIGHT= 122;

constexpr auto ANIMATION_WHIP_LV1_LEFT = 501;
constexpr auto ANIMATION_WHIP_LV1_RIGHT= 502;
constexpr auto ANIMATION_BIG_CANDLE_IDLE = 503;

/*
	image resources
*/
constexpr auto TEXTURE_SIMON_PATH = L"Resources\\sprites\\simon\\simon.png"; 
constexpr auto TEXTURE_EMPTY_PATH = L"Resources\\sprites\\EmptySprite.png"; 
constexpr auto TEXTURE_WHIP_PATH = L"Resources\\sprites\\weapon\\whip.png";
constexpr auto TEXTURE_BIG_CANDLE_PATH = L"Resources\\sprites\\ground\\0.png";
constexpr auto TEXTURE_LVL1_BACKGROUND_PATH= L"Resources\\sprites\\background\\lv1.png"; 
constexpr auto TEXTURE_ENTRANCE_BACKGROUND_PATH = L"Resources\\sprites\\background\\entranceBackground.png";
constexpr auto ENTRANCE_GROUND_BRICK_SCREEN_2 = L"Resources\\sprites\\ground\\2.png";