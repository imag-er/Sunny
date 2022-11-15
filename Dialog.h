#pragma once
#include <Windows.h>
#include <string>
class dialog
{
public:
	dialog( std::wstring );
	LRESULT CALLBACK OnMsg( const MSG );
	void make( );
	
	HWND hWnd;
	std::wstring window_name;
private:
	bool window_init( );
	static bool is_window_class_registered;
};

