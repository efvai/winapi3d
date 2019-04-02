#include <math.h>
#include <memory.h>
#include "matrix.h"
#include "geometry.h"
/*
 онструктор, инициализирует матрицу единичной (матрица тождественного преобразовани€)
*/
Matrix::Matrix() {
	SetUnit();
	 data[1][1] = 0.866; //cos30;
	data[2][1] = 0.5; //sin30;
	data[1][2] = -0.5; //sin(-30);
	data[2][2] = 0.866; //cos30;
	data[1][1] = 0.966; //cos15;
	data[2][1] = 0.259; //sin15;
	data[1][2] = -0.259; //sin(-15);
	data[2][2] = 0.866; //cos15;
}
/*
“екуща€ матрица становитс€ единичной
*/
void Matrix::SetUnit() {
	//memset(data, sizeof(data), 0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = 0.0;
		}
	}
	for (int i = 0; i < 4; i++) {
		data[i][i] = 1.0;
	}
}
/*
”станавливает текущую матрицу в качестве матрицы вращени€ на угол alpha,
заданный косинусом и синусом
*/
void Matrix::SetRotationMatrixbySinCos(double sinalpha, double cosalpha) {
	SetUnit();
	data[0][0] = cosalpha; // a // a c p 0 //
	data[0][1] = sinalpha; // c // b d q 0 //
						   //data[0][2] = 0.0; // p // h f r 0 //
						   //data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = -sinalpha; // b 
	data[1][1] = cosalpha; // d
						   //data[1][2] = 0.1; // q
						   //data[1][3] = 0.1; // 0
						   //data[2][0] = 0.0; // h
						   //data[2][1] = 0.25; // f
						   //data[2][2] = 0.0; // r
						   //data[2][3] = 1.0; // 0
						   //data[3][0] = 0.25; // m
						   //data[3][1] = 0.25; // n
						   //data[3][2] = 1.0; // l
						   //data[3][3] = 1.0; // 1
}
/*
”станавливает текущую матрицу в качестве матрицы вращени€ на угол alpha
*/
void Matrix::SetRotationMatrix(double alpha) {
	SetRotationMatrixbySinCos(sin(alpha), cos(alpha));
}
/*
”станавливает текущую матрицу в качестве матрицы параллельного переноса на вектор (tx, ty)
*/
void Matrix::SetTranslationMatrix(double tx, double ty) {
	SetUnit();
	//
	data[0][0] = 1 - tx;
	data[1][1] = 1 - ty;
	data[3][0] = tx;
	data[3][1] = ty;
}
void Matrix::SetTranslationMatrix_0() {
	SetUnit();
	data[0][0] = 0.0; // a // a c p 0 //
	data[0][1] = 1.0; // c // b d q 0 //
	data[0][2] = 0.0; // p // h f r 0//
	data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = 0.1; // b 
	data[1][1] = 0.0; // d
	data[1][2] = 0.1; // q
	data[1][3] = 0.1; // 0
	data[2][0] = 0.5; // h
	data[2][1] = 0.25; // f
	data[2][2] = 0.0; // r
	data[2][3] = -1.0; // 0
	data[3][0] = 0.25; // m
	data[3][1] = 0.25; // n
	data[3][2] = 1.0; // l
	data[3][3] = 1.0; // 1
}
void Matrix::SetTranslationMatrix_1() {
	SetUnit();
	data[0][0] = 0.0; // a // a c p 0 //
	data[0][1] = 1.0; // c // b d q 0 //
	data[0][2] = 0.0; // p // h f r 0//
	data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = 0.1; // b 
	data[1][1] = 0.0; // d
	data[1][2] = -1.0; // q
	data[1][3] = 0.1; // 0
	data[2][0] = 0.5; // h
	data[2][1] = 1.0; // f
	data[2][2] = 0.0; // r
	data[2][3] = 0.0; // 0
	data[3][0] = 0.25; // m
	data[3][1] = 0.25; // n
	data[3][2] = 1.0; // l 
	data[3][3] = 1.0; // 1
}
void Matrix::SetTranslationMatrix_2() {
	SetUnit();
	data[0][0] = 0.766; // a // a c p 0 //
	data[0][1] = 0.642; // c // b d q 0 //
	data[0][2] = 1.0; // p // h f r 0 //
	data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = -0.642; // b 
	data[1][1] = 0.766; // d
	data[1][2] = -1.0; // q
	data[1][3] = 0.1; // 0
	data[2][0] = -1.; // h
	data[2][1] = 1.0; // f
	data[2][2] = 0.0; // r
	data[2][3] = 0.0; // 0
	data[3][0] = 0.25; // m
	data[3][1] = 0.25; // n
	data[3][2] = 1.0; // l
	data[3][3] = 1.0; // 1
}
void Matrix::SetTranslationMatrix_3() {
	SetUnit();
	data[0][0] = 0.0; // a // a c p 0 //
	data[0][1] = 1.0; // c // b d q 0 //
	data[0][2] = 0.0; // p // h f r 0//
	data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = 0.1; // b 
	data[1][1] = 0.866; // d 
	data[1][2] = -0.5; // q 
	data[1][3] = 0.1; // 0
	data[2][0] = 0.5; // h
	data[2][1] = 0.5; // f 
	data[2][2] = 0.866; // r 
	data[2][3] = 0.0; // 0
	data[3][0] = 0.25; // m
	data[3][1] = 0.25; // n
	data[3][2] = 1.0; // l
	data[3][3] = 1.0; // 1
}
void Matrix::SetTranslationMatrix_4() {
	SetUnit();
	data[0][0] = 0.94; // a // a c p 0 //
	data[0][1] = 1.0; // c // b d q 0 //
	data[0][2] = -0.342; // p // h f r 0//
	data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = 0.1; // b 
	data[1][1] = 0.0; // d
	data[1][2] = -1.0; // q
	data[1][3] = 0.1; // 0
	data[2][0] = 0.342; // h 
	data[2][1] = 1.0; // f
	data[2][2] = 0.94; // r
	data[2][3] = 0.0; // 0
	data[3][0] = 0.25; // m
	data[3][1] = 0.25; // n
	data[3][2] = 1.0; // l
	data[3][3] = 1.0; // 1
}
void Matrix::SetTranslationMatrix_5() {
	SetUnit();
	data[0][0] = 0.0; // a // a c p 0 //
	data[0][1] = 1.0; // c // b d q 0 //
	data[0][2] = 0.0; // p // h f r 0//
	data[0][3] = 1.0; // 0 // m n l 1 //
	data[1][0] = 0.1; // b 
	data[1][1] = 0.0; // d
	data[1][2] = -1.0; // q
	data[1][3] = 0.1; // 0
	data[2][0] = 0.5; // h
	data[2][1] = 1.0; // f
	data[2][2] = 0.0; // r
	data[2][3] = 0.0; // 0
	data[3][0] = 0.45; // m
	data[3][1] = 0.2; // n 
	data[3][2] = 1.0; // l
	data[3][3] = 1.0; // 1
}
/*
”множает текущую матрицу на матрицу, переданную в качестве параметра
*/
void Matrix::MultiplyMatrices(Matrix &right) {
	double temp[4][4];
	double val;
	memcpy(temp, data, sizeof(data));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			val = 0;
			for (int v = 0; v < 4; v++) {
				val += temp[i][v] * right.data[v][j];
			}
			data[i][j] = val;
		}
	}
}
/*
ѕеремножает точку, переданную в качестве параметра на текущую матрицу.
ѕри этом последний столбец матрицы не учитываетс€
*/
void Matrix::ApplyMatrixtoPoint(_Point &point) {
	double _x, _y, _z, w;
	_x = point.x;
	_y = point.y;
	_z = point.z;
	point.x = _x * data[0][0] + _y * data[1][0] + _z * data[2][0] + data[3][0];
	point.y = _x * data[0][1] + _y * data[1][1] + _z * data[2][1] + data[3][1];
	point.z = _x * data[0][2] + _y * data[1][2] + _z * data[2][2] + data[3][2];
	w = data[2][3] * _z + 1;
	point.x = point.x / w;
	point.y = point.y / w;
}