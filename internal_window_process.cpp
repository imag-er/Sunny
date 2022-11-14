#include "internal_window_process.h"
#include "MessageDispatcher.h"
LRESULT internal_window_process( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
    if ( uMsg == WM_CREATE )
    {
        return DefWindowProcW( hWnd , uMsg , wParam , lParam );
    }
    MessageDispatcher* pmd = new MessageDispatcher( hWnd );
    MSG msg;
    msg.message = uMsg;
    msg.hwnd = hWnd;
    msg.wParam = wParam;
    msg.lParam = lParam;

    return pmd->dispatch( msg );
}
