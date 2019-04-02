#pragma once
#include "geometry.h"

#ifndef _MATRIX

class Matrix {
	double data[4][4];
public:
	Matrix();
	void SetUnit();
	void SetRotationMatrix(double alpha);
	void SetRotationMatrixbySinCos(double sinalpha, double cosalpha);
	void SetTranslationMatrix(double tx, double ty);
	void SetTranslationMatrix_0();
	void SetTranslationMatrix_1();
	void SetTranslationMatrix_2();
	void SetTranslationMatrix_3();
	void SetTranslationMatrix_4();
	void SetTranslationMatrix_5();
	void MultiplyMatrices(Matrix &right);
	void ApplyMatrixtoPoint(_Point &point);
};

#define _MATRIX
#endif