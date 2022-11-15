#include "Application.h"
#include "Dialog.h"
#include <fmt/core.h>
#include <iostream>
application* application::obj = nullptr;

application* application::get_instance( )
{
	if ( obj == nullptr )
		obj = new application( );

	return obj;
}

void application::add_node( HWND hWnd_ ,dialog* dialog_)
{
	obj->handle_to_Dialog[ hWnd_ ] = dialog_;
}

dialog* application::get_node( HWND hWnd_)
{
	return obj->handle_to_Dialog[ hWnd_ ];
}

uint32_t application::exec( )
{
	
	std::cout << "msgloop thread id:" << std::this_thread::get_id( ) << std::endl;
	MSG msg{0};
	while ( msg.message != WM_QUIT )
	{
		if ( PeekMessageW( &msg , NULL , 0 , 0 , PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessageW( &msg );
		}
		Sleep( 50 );
	}
	return msg.wParam;
}

application::application( )
{
	 
}