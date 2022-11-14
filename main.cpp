#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include "Application.h"
#include "Dialog.h"
#include <iostream>
#include <tchar.h>
INT WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	INT nCmdShow
	)
{
	AllocConsole( );
	freopen( "CONOUT$" , "w+" , stdout );
	Application* app = Application::get_instance( );
	app->hInstance = hInstance;

	Dialog d1;
	d1.make( );
	app->exec( );
	return 0;
}