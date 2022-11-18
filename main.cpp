#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:6285)

#include "application.h"
#include "information_stream.h"
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "widget.h"
#include "dialog_manager.h"
INT WINAPI WinMain(
	_In_ HINSTANCE hInstance ,
	_In_opt_ HINSTANCE hPrevInstance ,
	_In_ LPSTR lpCmdLine ,
	_In_ int nShowCmd
)
{
	auto app = application::instance( );

	widget* w1 = new widget( nullptr );
	widget* w2 = new widget( w1 );

	w1->remove_child( w2 );

	return app->dm->msg_loop();
}