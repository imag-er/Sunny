#pragma once
#include <Windows.h>
#include <map>

class Dialog;
class MessageDispatcher
{
public:
	MessageDispatcher( HWND );
	LRESULT CALLBACK dispatch( const MSG );
private:
	Dialog* dialog;
	using message_dispose_func = void( Dialog::*)( );
};

