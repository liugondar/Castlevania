#pragma once
#include "Animation.h"
using namespace std;



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

