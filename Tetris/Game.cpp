#include "Game.h"
int game_state = 0;
// 0 = menu
// 1 = playing 
// 2 = gameover

int* playing_field;

void Fill(Figure* figure, HWND hWnd) {
    for (int i = 0; i < 4; i++) {
        if (figure->point[i].y == 0) {
            playing_field[figure->point[i].y * 10 + figure->point[i].x] = 1;
            GameOver(hWnd);
        }
        else {
            playing_field[figure->point[i].y * 10 + figure->point[i].x] = 1;
        }
    }
   // InvalidateRect(hWnd, NULL, NULL);
}

int DeleteLine() {
    for (int str = 19; str >= 0; str--) {
        int count = 0;
        for (int column = 0; column < 10; column++) {
            if (playing_field[str * 10 + column] == 1) {
                count++;
            }
            else {
                break;
            }
        }
        if (count == 10) {

            for (int str1 = str; str1 > 0; str1--) {
                for (int column1 = 0; column1 < 10; column1++) {
                    playing_field[str1 * 10 + column1] = playing_field[(str1 - 1) * 10 + column1];
                }
            }
            return 1;
        }
    }
    return 0;
}

void GameOver(HWND hWnd) {
    KillTimer(hWnd, 0);
    game_state = 2;
    InvalidateRect(hWnd, NULL, NULL);
}

void GameStart(HWND hWnd) {
    MoveWindow(hWnd, 0, 0, 500, 660, TRUE);
    playing_field = (int*)calloc(200, sizeof(int));
    FigureInit(hWnd);
}
