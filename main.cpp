#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include "application.h"
#include "information_stream.h"
#include "dialog.h"
#include <iostream>
#include <tchar.h>
#include <WinBase.h>

INT WINAPI WinMain(
	_In_ HINSTANCE hInstance ,
	_In_opt_ HINSTANCE hPrevInstance ,
	_In_ LPSTR lpCmdLine ,
	_In_ int nShowCmd
)
{
	application* app = application::get_instance( );
	app->hInstance = hInstance;

	isout.init( );
	isout << "输出流测试" << 1 << 1.0 << iss::n;

	dialog d1(L"window1" );
	d1.make( );

	dialog d2(L"window2" );
	d2.make( );

	return app->exec( );
}