#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"

Menu* SystemInitialise(const char* configName) {
	FILE* openConf = fopen(configName, "r");
	char* str = (char*)malloc(50 * sizeof(char));
	Window window;
	Button* buttons = (Button*)malloc(sizeof(Button));
	Button* p;
	int butNum = 0;
	int butIndex;
	//Обработка тела конфига
	while (fscanf(openConf, "%s", str) >= 1) {
		if (str[0] == '#') continue;
		if (strcmp(str, "WindowBegin") == 0) {
			do {
				if ((fscanf(openConf, "%s", str) >= 1) && (strcmp(str, "Size") == 0)) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i,%i)", &(window.size.leftTop.x), &(window.size.leftTop.y), &(window.size.rightBottom.x), &(window.size.rightBottom.y));
				}
				else if (strcmp(str, "Color") == 0) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i)", &(window.color.r), &(window.color.g), &(window.color.b));
				}
			} while (strcmp(str, "WindowEnd") != 0);

		}
		else if (strcmp(str, "ButtonBegin") == 0) {
			butNum++;
			butIndex = butNum - 1;
			p = (Button*)realloc(buttons, butNum * sizeof(Button));
			if (p == NULL) {
				puts("realloc error");
				return NULL;
			}
			else {
				buttons = p;
			}
			do {
				if ((fscanf(openConf, "%s", str) >= 1) && (strcmp(str, "Size") == 0)) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i,%i)", &(buttons[butIndex].size.leftTop.x), &(buttons[butIndex].size.leftTop.y), &(buttons[butIndex].size.rightBottom.x), &(buttons[butIndex].size.rightBottom.y));
				}
				else if (strcmp(str, "Color") == 0) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i)", &(buttons[butIndex].color.r), &(buttons[butIndex].color.g), &(buttons[butIndex].color.b));
				}
				else if (strcmp(str, "Name") == 0) {
					fscanf(openConf, "%s", str);
					buttons[butIndex].name = (char*)malloc(strlen(str) - 4);
					for (int i = 2; i < strlen(str) - 2; i++) {
						buttons[butIndex].name[i - 2] = str[i];
					}
					buttons[butIndex].name[strlen(str) - 4] = '\0';
				}
			} while (strcmp(str, "ButtonEnd") != 0);

		}
	}


	Menu* menu = (Menu*)malloc(sizeof(Menu));
	menu->window = window;
	menu->buttons = buttons;
	menu->butNum = butIndex;
	free(str);
	fclose(openConf);
	return menu;
}
void SystemUpdate(Menu* menu, HDC hdc, HWND hWnd, int curBut) {
	RECT rcWindow;
	RECT rcLine;
	HBRUSH backGrColor = CreateSolidBrush(RGB(menu->window.color.r, menu->window.color.g, menu->window.color.b));
	//MoveWindow(hWnd, menu->window.size.leftTop.x, menu->window.size.leftTop.y, menu->window.size.rightBottom.x, menu->window.size.rightBottom.y, TRUE);
	GetClientRect(hWnd, &rcWindow);
	SelectObject(hdc, backGrColor);
	Rectangle(hdc, menu->window.size.leftTop.x, menu->window.size.leftTop.y, menu->window.size.rightBottom.x, menu->window.size.rightBottom.y);
	for (int i = 0; i <= menu->butNum; i++) {
		HBRUSH brush = CreateSolidBrush(RGB(menu->buttons[i].color.r, menu->buttons[i].color.g, menu->buttons[i].color.b));
		SelectObject(hdc, brush);
		Rectangle(hdc, menu->buttons[i].size.leftTop.x, menu->buttons[i].size.leftTop.y, menu->buttons[i].size.rightBottom.x, menu->buttons[i].size.rightBottom.y);
		rcLine.left = menu->buttons[i].size.leftTop.x;
		rcLine.top = menu->buttons[i].size.leftTop.y;
		rcLine.right = menu->buttons[i].size.rightBottom.x;
		rcLine.bottom = menu->buttons[i].size.rightBottom.y;
		SetBkMode(hdc, TRANSPARENT);
		if (i == curBut) {
			SetTextColor(hdc, RGB(255, 0, 0));
			DrawTextA(hdc, menu->buttons[i].name, -1, &rcLine, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
		else {
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawTextA(hdc, menu->buttons[i].name, -1, &rcLine, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}


	}
}
void SystemRelease(Menu* menu) {
	free(menu->buttons);
	free(menu);
	menu = NULL;

}