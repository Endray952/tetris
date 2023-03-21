#pragma once
#include "framework.h"
#include"time.h"
#define SPEED 900
#define DIFFICULTY 0.01
typedef struct {
    int x;
    int y;
}GPoint;
typedef struct {
    GPoint* point;
}Figure;
void FigureInit( HWND hWnd);
void FigureMove( int* playing_field, HWND hWnd);
void Rotate( int* playing_field);
int CheckBorders( int* playing_field, GPoint delta);