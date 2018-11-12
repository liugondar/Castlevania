#pragma once

//nhay
#define SIMON_VJUMP 0.5f;
#define SIMON_MOVING_WIDTH 40
#define SIMON_MOVING_HEIGHT 64
#define SIMON_HITTING_WIDTH 50
#define SIMON_HITTING_HEIGHT 64
#define SIMON_SITTING_WIDTH 40
#define SIMON_SITTING_HEIGHT 47

constexpr auto SIMON_HITTING_TIME = 150;

// trong luc luc nhay
#define SIMON_GRAVITY 0.002f;
//trong luc luc roi
#define SIMON_FALL 180
//di binh thuong
#define SIMON_VX 1.f;
//len xuong cau thang
#define SIMON_VX_STAIR 43	
#define SIMON_VY_STAIR 43

//states
constexpr auto STATE_SIMON_IDLE = 1;
constexpr auto STATE_SIMON_WALKING_RIGHT = 2;
constexpr auto STATE_SIMON_WALKING_LEFT = 3;
constexpr auto STATE_SIMON_SITTING = 4;
constexpr auto STATE_SIMON_JUMPING = 5;
constexpr auto STATE_SIMON_HITTING = 6;
constexpr auto STATE_SIMON_HIT_WHEN_SITTING = 7;


constexpr auto SPRITE_SIMON_MOVING_RIGHT_1 = 10001;
constexpr auto SPRITE_SIMON_MOVING_RIGHT_2 = 10002;
constexpr auto SPRITE_SIMON_MOVING_RIGHT_3 = 10003;
constexpr auto SPRITE_SIMON_SIT_FACE_RIGHT = 10004;
constexpr auto SPRITE_SIMON_MOVING_LEFT_1 = 10005;
constexpr auto SPRITE_SIMON_MOVING_LEFT_2 = 10006;
constexpr auto SPRITE_SIMON_MOVING_LEFT_3 = 10007;
constexpr auto SPRITE_SIMON_SIT_FACE_LEFT = 10008;
constexpr auto SPRITE_SIMON_HITTING_LEFT1 = 10009;
constexpr auto SPRITE_SIMON_HITTING_LEFT2 = 10010;
constexpr auto SPRITE_SIMON_HITTING_LEFT3 = 10011;
constexpr auto SPRITE_SIMON_HITTING_RIGHT1 = 10012;
constexpr auto SPRITE_SIMON_HITTING_RIGHT2 = 10013;
constexpr auto SPRITE_SIMON_HITTING_RIGHT3 = 10014;