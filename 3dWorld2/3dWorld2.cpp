// 3dWorld2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3dWorld2.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>

//import std.core;
import std.memory;

import BaseApplication;

void initializeConcole() {
	AllocConsole();
	FILE* fp = nullptr;
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hConsole = _open_osfhandle(reinterpret_cast<long>(stdHandle), _O_TEXT);
	fp = _fdopen(hConsole, "w");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	//SetConsoleTextAttribute(stdHandle, (WORD)((15 << 4) | 0));
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	initializeConcole();

	BaseApplication baseApp;
	if (baseApp.initializeApp()) {
		baseApp.mainLoop();
	}
	if (baseApp.getIsMainLoopDone()) {
		baseApp.exitApplication();
	}

	return EXIT_SUCCESS;
}


