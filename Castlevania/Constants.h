#pragma once

/*
	Simon constants
*/

// huong mat. object dang nhin
enum FaceSide {
	left=-1,right=1
};

//nhay
#define SIMON_VJUMP 0.5f;
#define SIMON_MOVING_WIDTH 40
#define SIMON_MOVING_HEIGHT 60
#define SIMON_HITTING_WIDTH 50
#define SIMON_HITTING_HEIGHT 60
#define SIMON_SITTING_WIDTH 40
#define SIMON_SITTING_HEIGHT 44
constexpr auto SIMON_HITTING_TIME = 150;

// trong luc luc nhay
#define SIMON_GRAVITY 0.002f;
//trong luc luc roi
#define SIMON_FALL 180
//di binh thuong
#define SIMON_VX 0.1f;
//len xuong cau thang
#define SIMON_VX_STAIR 43	
#define SIMON_VY_STAIR 43
//states
constexpr auto STATE_SIMON_IDLE= 1;
constexpr auto STATE_SIMON_WALKING_RIGHT= 2;
constexpr auto STATE_SIMON_WALKING_LEFT= 3;
constexpr auto STATE_SIMON_SITTING = 4;
constexpr auto STATE_SIMON_JUMPING= 5;
constexpr auto STATE_SIMON_HITTING= 6;


constexpr auto BRICK_2_SIZE = 32;

/*
	sprite constants
*/

constexpr auto SPRITE_SIMON_MOVING_RIGHT_1 = 10001;
constexpr auto SPRITE_SIMON_MOVING_RIGHT_2 = 10002;
constexpr auto SPRITE_SIMON_MOVING_RIGHT_3 = 10003;
constexpr auto SPRITE_SIMON_SIT_FACE_RIGHT = 10004;
constexpr auto SPRITE_SIMON_MOVING_LEFT_1 = 10005;
constexpr auto SPRITE_SIMON_MOVING_LEFT_2 = 10006;
constexpr auto SPRITE_SIMON_MOVING_LEFT_3 = 10007;
constexpr auto SPRITE_SIMON_SIT_FACE_LEFT= 10008;
constexpr auto SPRITE_SIMON_HITTING_LEFT1= 10009;
constexpr auto SPRITE_SIMON_HITTING_LEFT2= 10010;
constexpr auto SPRITE_SIMON_HITTING_LEFT3= 10011;
constexpr auto SPRITE_SIMON_HITTING_RIGHT1= 10012;
constexpr auto SPRITE_SIMON_HITTING_RIGHT2= 10013;
constexpr auto SPRITE_SIMON_HITTING_RIGHT3= 10014;

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


/* 
	texture constants
*/

constexpr auto ID_TEX_SIMON = 101;
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

/*
	image resources
*/
constexpr auto TEXTURE_SIMON_PATH = L"Resources\\sprites\\simon\\simon.png"; 
constexpr auto TEXTURE_LVL1_BACKGROUND_PATH= L"Resources\\sprites\\background\\lv1.png"; 
constexpr auto TEXTURE_ENTRANCE_BACKGROUND_PATH = L"Resources\\sprites\\background\\entranceBackground.png";
constexpr auto ENTRANCE_GROUND_BRICK_SCREEN_2 = L"Resources\\sprites\\ground\\2.png";