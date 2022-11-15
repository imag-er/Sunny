#include "Dialog.h"
#include <fmt/core.h>
#include <iostream>
#include "Application.h"
#include "internal_window_process.h"

bool dialog::is_window_class_registered = false;


dialog::dialog( std::wstring window_name_) :
	hWnd( 0 ) ,window_name(window_name_ )
{

}
LRESULT CALLBACK dialog::OnMsg( const MSG msg_)
{
	/*fmt::print(
		"message id:{},wparam:{}" ,
		msg_.message , 
		msg_.wParam 
	);*/
	switch ( msg_.message )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProcW( msg_.hwnd , msg_.message , msg_.wParam , msg_.lParam );
	}

}

void dialog::make( )
{
	auto app = application::get_instance( );
	bool ret = window_init( );

	if ( !ret )
		MessageBeep(0);
	app->add_node( hWnd , this );
}

bool dialog::window_init( )
{
	auto app = application::get_instance( );

	if ( !is_window_class_registered )
	{
		WNDCLASSW w { 0 };
		w.lpfnWndProc = internal_window_process;
		w.lpszClassName = L"classname";
		w.hInstance = app->hInstance;
		w.style = CS_HREDRAW | CS_VREDRAW;
		w.hbrBackground = ( HBRUSH ) GetStockObject( WHITE_BRUSH );
		w.hCursor = LoadCursorW( 0 , IDC_ARROW );
		w.hIcon = ( HICON ) LoadImageW( 0 , IDI_APPLICATION , IMAGE_ICON , 0 , 0 ,LR_DEFAULTSIZE );
		if ( !RegisterClassW( &w ) )
			return false;
	}

	is_window_class_registered = true;
	hWnd = CreateWindowExW(
		NULL , 
		L"classname" , 
		window_name.c_str() ,
		WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT ,
		CW_USEDEFAULT , 
		CW_USEDEFAULT , 
		CW_USEDEFAULT ,
		NULL ,
		NULL , 
		app->hInstance ,
		NULL );
	std::cout << "window thread id:" << std::this_thread::get_id( ) << std::endl;
	fmt::print( "------\n{}\n------\n" , GetLastError( ) );
	if ( hWnd == 0 )
		return false;
	ShowWindow( hWnd , SW_SHOW );
	UpdateWindow( hWnd );
	return true;
}
