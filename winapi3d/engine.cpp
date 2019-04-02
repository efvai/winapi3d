#include <windows.h>
#include "geometry.h"
#include "matrix.h"
#include "engine.h"
/*
ѕрив€зываем к движку объект, который отвечает за действи€ пользовател€
*/
void Engine::SetAction(Action *_action)
{
	action = _action;
}
/*
¬ыводит графику на контекст hdc
*/
void Engine::Draw(HDC hdc) {
	_Point rupor[20];
	double z = 0.0;
	rupor[1].x = 0.2;
	rupor[1].y = 0.1;
	rupor[1].z = z;
	rupor[2].x = 0.2;
	rupor[2].y = -0.1;
	rupor[2].z = z; // 0.4 = 1
	rupor[3].x = -0.2;
	rupor[3].y = -0.1;
	rupor[3].z = z;
	rupor[4].x = -0.2;
	rupor[4].y = 0.1;
	rupor[4].z = z;
	z = -0.4;
	rupor[5].x = 0.1;
	rupor[5].y = 0.05;
	rupor[5].z = z;
	rupor[6].x = 0.1;
	rupor[6].y = -0.05;
	rupor[6].z = z;
	rupor[7].x = -0.1;
	rupor[7].y = -0.05;
	rupor[7].z = z;
	rupor[8].x = -0.1;
	rupor[8].y = 0.05;
	rupor[8].z = z;
	z = -0.8;
	rupor[9].x = 0.1;
	rupor[9].y = 0.05;
	rupor[9].z = z;
	rupor[10].x = 0.1;
	rupor[10].y = -0.05;
	rupor[10].z = z;
	rupor[11].x = -0.1;
	rupor[11].y = -0.05;
	rupor[11].z = z;
	rupor[12].x = -0.1;
	rupor[12].y = 0.05;
	rupor[12].z = z;
	z = 0.0; // оси координат антенны 
	rupor[13].x = 0.0;
	rupor[13].y = 0.0;
	rupor[13].z = z;
	rupor[14].x = 0.4;
	rupor[14].y = 0.0;
	rupor[14].z = z;
	rupor[15].x = 0.0;
	rupor[15].y = 0.4;
	rupor[15].z = z;
	rupor[16].x = 0.0;
	rupor[16].y = 0.0;
	rupor[16].z = 0.4;
	z = 0.0; // глобальна€ система координат
	rupor[17].x = 0.0;
	rupor[17].y = 0.0;
	//rupor[17].z = 0.0;
	rupor[18].x = 1.0;
	rupor[18].y = 0.0;
	rupor[18].z = 0.0;
	rupor[19].x = 0.0;
	rupor[19].y = 1.0;
	rupor[19].z = 0.0;
	for (int i = 1; i <17; i++) {
		//¬ращение и перемещение осуществл€етс€ в логических координатах
		action->CurrentMatrix.ApplyMatrixtoPoint(rupor[i]);
		// ѕереход из логических в оконные координаты.
		rupor[i] = viewport.T(rupor[i]);
	}
	for (int i = 17; i <20; i++) {
		//ѕереход из логических в оконные координаты.
		rupor[i] = viewport.T(rupor[i]);
	}
	// пр€моугольник в плоскости z=0
	for (int i = 1; i <= 4; i++) {
		if (i == 1) {
			MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		}
		else
		{
			LineTo(hdc, rupor[i].x, rupor[i].y);
		}
	}
	LineTo(hdc, rupor[1].x, rupor[1].y);
	// пр€моугольник в плоскости z=-0.2
	for (int i = 5; i <= 8; i++) {
		if (i == 5) {
			MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		}
		else
		{
			LineTo(hdc, rupor[i].x, rupor[i].y);
		}
	}
	LineTo(hdc, rupor[5].x, rupor[5].y);
	// пр€моугольник в плоскости z=-0.6
	for (int i = 9; i <= 12; i++) {
		if (i == 9) {
			MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		}
		else
		{
			LineTo(hdc, rupor[i].x, rupor[i].y);
		}
	}
	LineTo(hdc, rupor[9].x, rupor[9].y);
	// ребра, параллельные оси z
	for (int i = 1; i <= 4; i++) {
		MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		LineTo(hdc, rupor[i + 4].x, rupor[i + 4].y);
	}
	for (int i = 5; i <= 8; i++) {
		MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		LineTo(hdc, rupor[i + 4].x, rupor[i + 4].y);
	}
	// оси координат антенны
	int i = 13;
	for (int j = 1; j <= 3; j++) {
		MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		LineTo(hdc, rupor[i + j].x, rupor[i + j].y);
	}
	// глобальные оси координат
	i = 17;
	for (int j = 1; j <= 2; j++) {
		//rupor[i+j] = viewport.T(rupor[i+j]);
		MoveToEx(hdc, rupor[i].x, rupor[i].y, NULL);
		LineTo(hdc, rupor[i + j].x, rupor[i + j].y);
	}
}