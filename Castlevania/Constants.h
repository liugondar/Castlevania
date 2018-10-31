#pragma once

/*
	Simon constants
*/
//nhay
#define SIMON_VJUMP 450

// trong luc luc nhay
#define SIMON_GRAVITY 20
//trong luc luc roi
#define SIMON_FALL 180
//di binh thuong
#define SIMON_VX 150
//len xuong cau thang
#define SIMON_VX_STAIR 43	
#define SIMON_VY_STAIR 43

/*
	sprite constants
*/

constexpr auto SPRITE_MARIO_FACE_LEFT_1 = 10001;
constexpr auto SPRITE_MARIO_FACE_LEFT_2 = 10002;
constexpr auto SPRITE_MARIO_FACE_LEFT_3 = 10003;

constexpr auto SPRITE_MARIO_FACE_RIGHT_1 = 10011;
constexpr auto SPRITE_MARIO_FACE_RIGHT_2 = 10012;
constexpr auto SPRITE_MARIO_FACE_RIGHT_3 = 10013;

constexpr auto SPRITE_BRICK = 20001;
constexpr auto SPRITE_GOOMBA_GO_LEFT = 30001;
constexpr auto SPRITE_GOOMBA_GO_RIGHT = 30011;
constexpr auto SPRITE_GOOMBA_DIE = 30021;


/* 
	texture constants
*/

constexpr auto ID_TEX_SIMON = 1;
constexpr auto ID_TEX_MARIO = 0;
constexpr auto ID_TEX_ENEMY = 10;
constexpr auto ID_TEX_MISC = 20;
constexpr auto ID_TEX_BBOX = -100;		//

/*
	image resources
*/
constexpr auto SIMON_SPRITE = L"(Resource\sprites\simon\simonFull.png)";