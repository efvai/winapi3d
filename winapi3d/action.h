#pragma once
#include "matrix.h"
#include "vec.h"

class Action {
public:
	vec old_mouse;
	Matrix CurrentMatrix;
	void InitAction(double x, double y);
	void Rotate(double x, double y);
	void Translate(double x, double y);
	void Transform_0();
	void Transform_1();
	void Transform_2();
	void Transform_3();
	void Transform_4();
	void Transform_5();
};