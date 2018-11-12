#pragma once
#include <math.h>
#include <limits>
#include <iostream>
#include <algorithm>

#include "Box.h"

bool isColliding(float bl, float bt, float br, float bb, float sl, float st, float sr, float sb);
void sweptAABB(
	float ml,			// move left 
	float mt,			// move top
	float mr,			// move right 
	float mb,			// move bottom
	float sl,			// static left
	float st,
	float sr,
	float sb,
	float dx, float dy,
	float &t, float &nx, float &ny);