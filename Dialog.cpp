#include "Dialog.h"
#include <fmt/core.h>
#include "Application.h"
#include "internal_window_process.h"
Dialog::Dialog( ) :
	hWnd( 0 )
{

}
LRESULT CALLBACK Dialog::OnMsg( const MSG msg_)
{
	fmt::print(
		"message id:{},wparam:{}\n" ,
		msg_.message , 
		msg_.wParam 
	);
	switch ( msg_.message )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProcW( msg_.hwnd , msg_.message , msg_.wParam , msg_.lParam );
	}

}

void Dialog::make( )
{
	auto app = Application::get_instance( );
	bool ret = window_init( );
	if ( !ret )
		MessageBeep(0);
	app->add_node( hWnd , this );
}

bool Dialog::window_init( )
{
	auto app = Application::get_instance( );

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

	hWnd = CreateWindowExW(
		NULL , 
		L"classname" , 
		L"name" , 
		WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT ,
		CW_USEDEFAULT , 
		CW_USEDEFAULT , 
		CW_USEDEFAULT ,
		NULL ,
		NULL , 
		app->hInstance ,
		NULL );
	if ( hWnd == 0 )
		return false;
	ShowWindow( hWnd , SW_SHOW );
	UpdateWindow( hWnd );
	return true;
}
