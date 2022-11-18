#pragma once
#include <Windows.h>
#include "widget.h"
#include "application.h"
class dialog_manager : public widget
{
public:
	dialog_manager( const pwidget& );
	~dialog_manager( );
	void init( );

	LRESULT window_proc( const MSG );
	LRESULT msghook_proc( int , WPARAM , LPARAM );
	
	int msg_loop( );
	
	HWND hManager = 0;
	HHOOK hMsgfilter = 0;
	HINSTANCE hInstance = ( ( application* ) parent )->hInstance;
private:
	const papplication& app = reinterpret_cast< application* >( parent );
	bool window_register( );
	bool window_create( );
	bool window_sethook( );
};

LRESULT CALLBACK internal_window_proc( HWND , UINT , WPARAM , LPARAM );
LRESULT CALLBACK internal_msghook_proc( int , WPARAM , LPARAM );
LRESULT CALLBACK general_window_proc( HWND , UINT , WPARAM , LPARAM );