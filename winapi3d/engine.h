#pragma once
#include "action.h"
#include "viewport.h"

class Engine {
	//Matrix current_rot;
	Action *action;
public:
	Viewport viewport;
	void Draw(HDC hdc);
	void SetAction(Action *_action);
};