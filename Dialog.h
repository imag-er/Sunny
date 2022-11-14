#pragma once
#include <Windows.h>
class Dialog
{
public:
	Dialog( );
	LRESULT CALLBACK OnMsg( const MSG );
	void make( );
	
	HWND hWnd;

private:
	bool window_init( );
};

