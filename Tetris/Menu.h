#pragma once
#include "framework.h"
#include "stdio.h"
typedef struct {
	int x;
	int y;
}Point;
typedef struct {
	Point leftTop;
	Point rightBottom;
}Size;
typedef struct {
	int r;
	int g;
	int b;
}Color;
typedef struct {
	Size size;
	Color color;
}Window;
typedef struct {
	Size size;
	Color color;
	char* name;
}Button;
typedef struct {
	Window window;
	Button* buttons;
	int butNum;
}Menu;
Menu* SystemInitialise(const char* configName);
void SystemUpdate(Menu* menu, HDC hdc, HWND hWnd, int curBut);
void SystemRelease(Menu* menu);
