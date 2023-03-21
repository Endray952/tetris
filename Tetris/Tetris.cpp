// TetrisTest.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Tetris.h"
#include "Game.h"
#include "Draw.h"
#include "Menu.h"
#include"Figure.h"
#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

extern Figure figure;
extern int* playing_field;
extern int game_state;
Menu* menu;
int curBut = 0;
HMENU hMenubar;
int game_state1 = 0;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TETRIS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU,
        0, 0, 600, 850, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    switch (message)
    {
    case WM_CREATE:
        figure.point = (GPoint*)malloc(4 * sizeof(int));        
        //game_state = 0;
        menu = SystemInitialise("Config.txt");
        MoveWindow(hWnd, menu->window.size.leftTop.x, menu->window.size.leftTop.y, menu->window.size.rightBottom.x, menu->window.size.rightBottom.y, TRUE);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        if (game_state1 == 0) {
            game_state = game_state1;
            SystemUpdate(menu, hdc, hWnd, curBut);
        }
        else if (game_state == 1 || game_state == 2) {
            DrawGame(hdc, hWnd, &figure, playing_field, game_state);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_RIGHT:
            if (game_state == 1 && CheckBorders( playing_field, { 1,0 }) == 1) {
                for (int i = 0; i < 4; i++) {
                    figure.point[i].x += 1;
                }
                InvalidateRect(hWnd, &rcClient, TRUE);
            }

            break;

        case VK_LEFT:
            if (game_state == 1 && CheckBorders( playing_field, { -1,0 }) == 1) {
                for (int i = 0; i < 4; i++) {
                    figure.point[i].x -= 1;
                }
                InvalidateRect(hWnd, &rcClient, TRUE);
            }
            break;
        case VK_DOWN:
            if (game_state == 1) {
                FigureMove( playing_field, hWnd);
            }
            else if (game_state == 0) {
                curBut++;
                if (curBut > menu->butNum) {
                    curBut = menu->butNum;
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        case VK_UP:
            if (game_state == 1) {
                Rotate( playing_field);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (game_state == 0) {
                curBut--;
                if (curBut < 0) {
                    curBut = 0;
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        case VK_RETURN:
            if (game_state == 0) {
                if (strcmp(menu->buttons[curBut].name, "Start") == 0) {
                    game_state = 1;
                    game_state1 = 1;
                    GameStart(hWnd);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                else if (strcmp(menu->buttons[curBut].name, "Exit") == 0) {
                    DestroyWindow(hWnd);
                }
            }
            else if (game_state == 2) {
                //game_state = 0;
                game_state1 = 0;
                MoveWindow(hWnd, menu->window.size.leftTop.x, menu->window.size.leftTop.y, menu->window.size.rightBottom.x, menu->window.size.rightBottom.y, TRUE);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
    }
    break;
    case WM_TIMER:
        if (game_state == 1) {
            FigureMove(playing_field, hWnd);
            InvalidateRect(hWnd, &rcClient, TRUE);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
