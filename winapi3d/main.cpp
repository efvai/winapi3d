#include <windows.h>
#include "engine.h"
const double PI = 3.141592653;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "CG6";
char szWindowCaption[] = "CG #6 Mouse Tracking and Rotation";
////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;
	// ��������� ��������� ������ ����
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCSTR)szClassName;
	// ������������ ����� ����
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}
	// ������� �������� ���� ����������
	hWnd = CreateWindow(
		(LPCSTR)szClassName, // ��� ������ 
		"������ WinAPI ����������", // ����� ��������� 
		WS_OVERLAPPEDWINDOW, // ����� ���� 
		50, 50, // ������� ������ �������� ���� 
		600, 600, // ������ � ������ ���� 
		(HWND)NULL, // ��������� �� ������������ ���� NULL 
		(HMENU)NULL, // ������������ ���� ������ ���� 
		(HINSTANCE)hInstance, // ��������� �� ������� ����������
		NULL); // ���������� � �������� lParam � ������� WM_CREATE
	if (!hWnd)
	{
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}
	// ���������� ���� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// ��������� ���� ��������� ��������� �� �������� ����������
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return (lpMsg.wParam);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static RECT Rect;
	HDC hdc, hCmpDC;
	HBITMAP hBmp;
	static Action *action;
	static Engine *engine;
	//static bool x = true;
	switch (messg)
	{
	case WM_CREATE:
		engine = new Engine();
		action = new Action(); //�����. ������. Matrix � ����. ������� (������. ���������)
		engine->SetAction(action); // ����.�������� ����� engine->action = action;
		break;
	case WM_PAINT:
		//x = x;
		GetClientRect(hWnd, &Rect);
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, 0xEECCCC);
		// �������� ������ ��������� ��� ������� ������������
		hCmpDC = CreateCompatibleDC(hdc);
		hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
			Rect.bottom - Rect.top);
		SelectObject(hCmpDC, hBmp);
		// �������� ������� ������
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = 0xEECCCC;
		HBRUSH brush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &Rect, brush);
		DeleteObject(brush);
		// ���������
		engine->Draw(hCmpDC);
		// ����� �� �����
		SetStretchBltMode(hdc, COLORONCOLOR);
		BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
			hCmpDC, 0, 0, SRCCOPY);
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // ����� ������ ������� WM_PAINT ��� WM_SIZE
		GetClientRect(hWnd, &Rect);
		engine->viewport.SetWindowSize(Rect.right - Rect.left, Rect.bottom - Rect.top);
		// x = false;
		break; //����������� �������� �����. viewport.Height, viewport.Width;
	case WM_ERASEBKGND:
		return 1;
		break;
	case WM_LBUTTONDOWN:
		_Point mouse_point;
		mouse_point.x = LOWORD(lParam); //�������� ���������� ������� ���� � ������� ����
		mouse_point.y = HIWORD(lParam);
		//����������� ���������� ������� � ����������
		mouse_point = engine->viewport.T_inv(mouse_point);
		// ���������� ���������� ������� � ������� old_mouse
		action->InitAction(mouse_point.x, mouse_point.y);
		//InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		if (UINT(wParam) & MK_LBUTTON) {
			_Point mouse_point;
			mouse_point.x = LOWORD(lParam); // ���������� � ������� ����
			mouse_point.y = HIWORD(lParam);
			mouse_point = engine->viewport.T_inv(mouse_point);// ���������� ���������� 
			if (UINT(wParam) & MK_CONTROL) {
				//���������� ������� ���������, �������� �� ������� � ���������� ��������� ����
				action->Translate(mouse_point.x, mouse_point.y);
			}
			else {
				action->Rotate(mouse_point.x, mouse_point.y);
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_KEYDOWN:
		int KeyPressed;
		KeyPressed = int(wParam);
		if (KeyPressed == int('0'))
		{
			action->Transform_0();
		}
		if (KeyPressed == int('1'))
		{
			action->Transform_1();
		}
		if (KeyPressed == int('2'))
		{
			action->Transform_2();
		}
		if (KeyPressed == int('3'))
		{
			action->Transform_3();
		}
		if (KeyPressed == int('4'))
		{
			action->Transform_4();
		}
		if (KeyPressed == int('5'))
		{
			action->Transform_5();
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd, messg, wParam, lParam));
	}
	return (0);
}