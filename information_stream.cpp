#pragma warning(disable:4996)

#include "information_stream.h"
#include <Windows.h>
information_stream isout;

void information_stream::init( )
{
	AllocConsole( );

	old_stream = freopen( "CONOUT$" , "w+" , stdout );
}



information_stream::~information_stream( )
{
	fclose( old_stream );
}
