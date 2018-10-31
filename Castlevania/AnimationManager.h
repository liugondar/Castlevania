#pragma once
#include "Animation.h"
using namespace std;

constexpr auto ANIMATION_MARIO_IDLE = 100;
constexpr auto ANIMATION_MARIO_IDLE_LEFT = 101;
constexpr auto ANIMATION_MARIO_IDLE_RIGHT = 102;
constexpr auto ANIMATION_MARIO_FACE_LEFT = 103;
constexpr auto ANIMATION_MARIO_FACE_RIGHT = 104;

constexpr auto ANIMATION_BRICK_IDLE = 201;
constexpr auto ANIMATION_GOOMBA_WALKING = 301;
constexpr auto ANIMATION_GOOMBA_DEAD= 302;

class AnimationManager {
private:
	static AnimationManager* instance;
	unordered_map<int, Animation*>  animations;
public:
	void add(int id, Animation* animation) {
		animations[id] = animation;
	}
	Animation* get(int id) {
		return animations[id];
	}

	static AnimationManager* getInstance();
};

