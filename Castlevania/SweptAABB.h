#pragma once
#include <math.h>
#include <limits>
#include <iostream>
#include <algorithm>

#include "Box.h"

void sweptAABB(
	Box movingObject, Box standingObject,
	float dx, float dy,
	float &t, float &nx, float &ny);