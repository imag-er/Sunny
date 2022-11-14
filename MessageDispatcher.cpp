#include "MessageDispatcher.h"
#include "Application.h"
#include "Dialog.h"
MessageDispatcher::MessageDispatcher( HWND hWnd_) :
	dialog( Application::get_node(hWnd_) )
{

}

LRESULT CALLBACK MessageDispatcher::dispatch( const MSG msg_)
{
	auto app = Application::get_instance( );
	return dialog->OnMsg( msg_ );
}
