#pragma once
#include "GameObject.h"
class Simon :
	public GameObject
{
public:
	Simon();
	~Simon();

	// Inherited via GameObject
	virtual void render() override;
	virtual Box getBoundingBox() override;
};

