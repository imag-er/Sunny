#include "Application.h"
#include "Dialog.h"
Application* Application::obj = nullptr;

Application* Application::get_instance( )
{
	if ( obj == nullptr )
		obj = new Application( );

	return obj;
}

void Application::add_node( HWND hWnd_ ,Dialog* dialog_)
{
	obj->handle_to_Dialog[ hWnd_ ] = dialog_;
}

Dialog* Application::get_node( HWND hWnd_)
{
	return obj->handle_to_Dialog[ hWnd_ ];
}

void Application::exec( )
{
}

Application::Application( )
{
	
}