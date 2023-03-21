#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "Draw.h"

int score = 0;
void DrawGame(HDC hdc, HWND hWnd, Figure* figure, int* playing_field, int game_state) {
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBM = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
    SelectObject(memDC, memBM);
    Rectangle(memDC, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
    if (game_state == 1 && DeleteLine() == 1) {
        score += SCORE;
    }

    DrawLevel(playing_field, memDC, hWnd);
    if (game_state == 1) {
        DrawFigure(figure, memDC, hWnd);
    }
    DrawScore(memDC, hWnd, game_state);
    BitBlt(hdc, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, memDC, 0, 0, SRCCOPY);
    DeleteDC(memDC);
    DeleteObject(memBM);

}

void DrawLevel(int* playing_field, HDC memDC, HWND hWnd) {
    HBRUSH Cell = CreateSolidBrush(RGB(90, 90, 90));
    HBRUSH Figure = CreateSolidBrush(RGB(255, 150, 90));
    HPEN pen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
    HBRUSH old_brush;
    HPEN old_pen;
    for (int str = 0; str < 20; str++) {
        for (int column = 0; column < 10; column++) {
            if (playing_field[str * 10 + column] == 1) {
                old_brush = (HBRUSH)SelectObject(memDC, Figure);
            }
            else {
                old_brush = (HBRUSH)SelectObject(memDC, Cell);
            }
            Rectangle(memDC, column * CELL, str * CELL, CELL + column * CELL, CELL + str * CELL);
            old_pen = (HPEN)SelectObject(memDC, pen);
            Rectangle(memDC, column * CELL, str * CELL, CELL + column * CELL, CELL + str * CELL);
        }
    }
    SelectObject(memDC, old_brush);
    DeleteObject(Cell);
    DeleteObject(Figure);
    SelectObject(memDC, old_pen);
    DeleteObject(pen);
}

void DrawFigure(Figure* figure, HDC memDC, HWND hWnd) {
    HBRUSH old_brush;
    HBRUSH Figure = CreateSolidBrush(RGB(255, 150, 90));
    for (int i = 0; i < 4; i++) {
        old_brush = (HBRUSH)SelectObject(memDC, Figure);
        Rectangle(memDC, figure->point[i].x * CELL, figure->point[i].y * CELL, CELL + figure->point[i].x * CELL, CELL + figure->point[i].y * CELL);
    }
    SelectObject(memDC, old_brush);
    DeleteObject(Figure);
}

void DrawScore(HDC memDC, HWND hWnd, int game_state) {
    RECT rcScore;

    char* buffer = (char*)malloc(10 * sizeof(char));
    itoa(score, buffer, 10);
    HFONT hFont = CreateFont(24, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("font"));
    if (game_state == 1) {
        rcScore.left = SCOREL;
        rcScore.top = SCORET;
        rcScore.right = SCORER;
        rcScore.bottom = SCOREB;
        SelectObject(memDC, hFont);
        SetTextColor(memDC, RGB(0, 0, 0));
        DrawTextA(memDC, buffer, -1, &rcScore, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    }
    else if (game_state == 2) {
        HPEN blackPen = CreatePen(BS_SOLID, 3, RGB(0, 0, 0));
        HBRUSH White = CreateSolidBrush(RGB(255, 255, 255));
        rcScore.left = RESL;
        rcScore.top = REST;
        rcScore.right = RESR;
        rcScore.bottom = RESB;
        HBRUSH old_brush = (HBRUSH)SelectObject(memDC, White);
        Rectangle(memDC, rcScore.left, rcScore.top, rcScore.right, rcScore.bottom);
        HPEN old_pen = (HPEN)SelectObject(memDC, blackPen);
        Rectangle(memDC, rcScore.left, rcScore.top, rcScore.right, rcScore.bottom);
        char buf[20] = "Score\n";
        SelectObject(memDC, hFont);
        SetTextColor(memDC, RGB(0, 0, 0));
        DrawTextA(memDC, strcat(buf, buffer), -1, &rcScore, DT_CENTER | DT_VCENTER);
        SelectObject(memDC, old_brush);
        DeleteObject(White);
        SelectObject(memDC, old_pen);
        DeleteObject(blackPen);
    }
    free(buffer);
    DeleteObject(hFont);
}

