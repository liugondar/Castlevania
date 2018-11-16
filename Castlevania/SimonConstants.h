#pragma once

//nhay
constexpr auto SIMON_VJUMP = 0.5f;
// Simon's width when moving
constexpr auto SIM_MOVE_W = 32;
// Simon's width when moving
constexpr auto SIM_MOVE_H = 62;
// Simon's width when hitting (normal state)
constexpr auto SIM_HIT_W = 48;
// Simon's height when hitting (normal state)
constexpr auto SIM_HIT_H = 62;
// Simon's width when sitting
constexpr auto SIM_SIT_W = 32;
// Simon's height when sitting
constexpr auto SIM_SIT_H = 48;
// Simon's width when hitting( in sitting state)
constexpr auto SIM_HIT_WHEN_SIT_W = 48;
// Simon's height when hitting( in sitting state)
constexpr auto SIM_HIT_WHEN_SIT_H = 48;

constexpr auto SIMON_HITTING_TIME = 150;

// trong luc luc nhay
#define SIMON_GRAVITY 0.002f;
//trong luc luc roi
constexpr auto SIMON_FALL = 180;
//di binh thuong
constexpr auto SIMON_VX = 0.15f;;
//len xuong cau thang
#define SIMON_VX_STAIR 43	
#define SIMON_VY_STAIR 43

//states
constexpr auto STATE_SIMON_IDLE = 1;
constexpr auto STATE_SIMON_WALKING= 2;
constexpr auto STATE_SIMON_SITTING = 3;
constexpr auto STATE_SIMON_JUMPING = 4;
constexpr auto STATE_SIMON_HITTING = 5;
constexpr auto STATE_SIMON_HIT_WHEN_SITTING = 6;
