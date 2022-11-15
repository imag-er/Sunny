#include "message_dispatcher.h"
#include "Application.h"
#include "Dialog.h"
message_dispatcher::message_dispatcher( HWND hWnd_) :
	dialog( application::get_node(hWnd_) )
{

}

LRESULT CALLBACK message_dispatcher::dispatch( const MSG msg_)
{
	auto app = application::get_instance( );
	return dialog->OnMsg( msg_ );
}
