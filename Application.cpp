#include "application.h"
#include "dialog_manager.h"
#include "information_stream.h"
application* application::obj = nullptr;

application::application( ) :
	widget(nullptr ) , hInstance(::GetModuleHandleW(0))
{
	isout.init( );
	isout << "输出流测试" << iss::n;
}
application* application::instance( )
{
	if ( obj == nullptr )
	{
		obj = new application( );
		obj->dm = new dialog_manager( obj );
		obj->dm->init( );
	}
	return obj;
}
