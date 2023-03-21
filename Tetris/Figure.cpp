#include "Figure.h"
#include "Game.h"
Figure figure;
void FigureInit( HWND hWnd) {
    srand(time(NULL));
    int type = rand() % 7;
    static int coordinates_x[] = { 1, 0, 2, 3,
                                  1, 1, 0, 1,
                                  1, 0, 1, 0,
                                  1, 0, 1, 1,
                                  1, 1, 1, 0,
                                  1, 1, 0, 0,
                                  1, 0, 0, 1 };
    static int coordinates_y[] = { 0, 0, 0, 0,
                            1, 0, 1, 2,
                            1, 0, 0, 1,
                            1, 0, 0, 2,
                            1, 0, 2, 2,
                            1, 0, 1, 2,
                            1, 0, 1, 2 };
    static double speed = SPEED;
    speed -= DIFFICULTY * speed;
    KillTimer(hWnd, 0);
    SetTimer(hWnd, 0, speed, NULL);
    for (int i = 0; i < 4; i++) {
        figure.point[i].x = coordinates_x[i + 4 * type];
        figure.point[i].y = coordinates_y[i + 4 * type];
    }
}
void FigureMove( int* playing_field, HWND hWnd) {
    if (CheckBorders( playing_field, { 0,1 }) == 1) {
        for (int i = 0; i < 4; i++) {
            figure.point[i].y += 1;
        }

    }
    else {
        Fill(&figure, hWnd);
        FigureInit( hWnd);
    }
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    InvalidateRect(hWnd, &rcClient, NULL);
}
void Rotate( int* playing_field) {
    GPoint center;
    GPoint figure_copy[4];
    center.x = figure.point[0].x;
    center.y = figure.point[0].y;
    int x, y;
    for (int i = 0; i < 4; i++) {
        figure_copy[i].x = figure.point[i].x;
        figure_copy[i].y = figure.point[i].y;
        x = figure.point[i].y - center.y;
        y = figure.point[i].x - center.x;
        figure.point[i].x = center.x - x;
        figure.point[i].y = center.y + y;
    }
    if (CheckBorders( playing_field, { 0,0 }) == 0) {
        for (int i = 0; i < 4; i++) {
            figure.point[i].x = figure_copy[i].x;
            figure.point[i].y = figure_copy[i].y;
        }
    }
}
int CheckBorders( int* playing_field, GPoint delta) {
    for (int i = 0; i < 4; i++) {
        if ((figure.point[i].x + delta.x < 0) || (figure.point[i].x + delta.x > 9) || (playing_field[(figure.point[i].y + delta.y) * 10 + figure.point[i].x] == 1) || (figure.point[i].y + delta.y == 20)) {
            return 0;
        }
        else if (playing_field[figure.point[i].y * 10 + figure.point[i].x] == 1 || playing_field[figure.point[i].y * 10 + figure.point[i].x + delta.x] == 1) {
            return 0;
        }
    }
    return 1;
}