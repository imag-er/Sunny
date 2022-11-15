#pragma once
#include <Windows.h>
#include <map>

class dialog;
class message_dispatcher
{
public:
	message_dispatcher( HWND );
	LRESULT CALLBACK dispatch( const MSG );
private:
	dialog* dialog;
	using message_dispose_func = void( dialog::*)( );
};

