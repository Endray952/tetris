#pragma once
#include "framework.h"
#include "Game.h"
#include "string"
#include"Figure.h"
#define SCORE 100
#define CELL 30

#define SCOREL 380
#define SCORET 150
#define SCORER 430
#define SCOREB 200

#define RESL 200
#define REST 150
#define RESR 400
#define RESB 350
void DrawGame(HDC hdc, HWND hWnd, Figure* figure, int* playing_field, int game_state);
void DrawLevel(int* playing_field, HDC memDC, HWND hWnd);
void DrawFigure(Figure* figure, HDC memDC, HWND hWnd);
void DrawScore(HDC memDC, HWND hWnd, int game_state);