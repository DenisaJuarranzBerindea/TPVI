#pragma once
#include "./Vector2D.h"

struct Collision {
	bool collides;
	bool damages;

	operator bool() const { return collides; }
};