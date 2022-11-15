#include "internal_window_process.h"
#include "message_dispatcher.h"
#include "application.h"
#include "dialog.h"
#include "information_stream.h"
LRESULT internal_window_process( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
    auto app = application::get_instance( );

    isout << app->get_node( hWnd )->window_name << iss::n;
    if ( uMsg == WM_CREATE )
    {
        return DefWindowProcW( hWnd , uMsg , wParam , lParam );
    }
    message_dispatcher* pmd = new message_dispatcher( hWnd );
    MSG msg;
    msg.message = uMsg;
    msg.hwnd = hWnd;
    msg.wParam = wParam;
    msg.lParam = lParam;

    return pmd->dispatch( msg );
}
