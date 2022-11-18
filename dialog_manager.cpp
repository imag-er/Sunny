#include "dialog_manager.h"
#include "application.h"
#include "information_stream.h"

dialog_manager::dialog_manager( const pwidget& parent_) :
	widget(parent_ )
{

}

dialog_manager::~dialog_manager( )
{
	// release resources
	UnregisterClassW( L"dialog_manager" , app->hInstance );
	UnregisterClassW( L"general_window" , app->hInstance );
	UnhookWindowsHookEx( hMsgfilter );
}

void dialog_manager::init( )
{
	if ( !window_sethook( ) )
	{
		isout << "无法安装钩子" << GetLastError() << iss::n;
		return;
	}
	isout << "已安装消息钩子:" << hMsgfilter << iss::n;

	if ( !window_register() )
	{
		isout << "无法注册窗口类" << iss::n;
		return;
	}

	if ( !window_create() )
	{
		isout << "无法创建窗口" << GetLastError() << iss::n;
		return;
	}

	UpdateWindow( hManager );
	ShowWindow( hManager , SW_HIDE );
	isout << "已创建窗口:" << hManager << iss::n;


}

LRESULT dialog_manager::window_proc( MSG m )
{
	isout 
		<< "//////\ndialog_manager：\nhwnd:" << (DWORD)hManager
		<< "\nmessage:" << m.message
		<< "\nwparam:" << m.wParam
		<< "\nlparam" << m.lParam
		<< "\n//////\n";
	return ::DefWindowProcW( m.hwnd , m.message , m.wParam , m.lParam );
}
LRESULT dialog_manager::msghook_proc( int nCode, WPARAM wParam, LPARAM lParam)
{
	isout << "//////\nHook：\ncode:" << nCode
		<< "\nwparam:" << wParam
		<< "\nlparam" << lParam
		<< "\n//////";
	return CallNextHookEx( app->dm->hMsgfilter , nCode , wParam , lParam );
}


int dialog_manager::msg_loop( )
{
	MSG msg { 0 };
	while ( 0 != GetMessageW( &msg , NULL , 0 , 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessageW( &msg );
	}
	return 0;
}

bool dialog_manager::window_register( )
{
	WNDCLASSW wdm;
	wdm.lpfnWndProc = ( WNDPROC ) internal_window_proc;
	wdm.lpszClassName = L"dialog_manager";
	wdm.hCursor = NULL;
	wdm.hInstance = hInstance;
	wdm.cbClsExtra = 0;
	wdm.cbWndExtra = 0;
	wdm.hIcon = NULL;
	wdm.lpszMenuName = NULL;
	wdm.hbrBackground = NULL;
	wdm.style = 0;

	WNDCLASSW wgeneral;
	wgeneral.lpfnWndProc = ( WNDPROC ) general_window_proc;
	wgeneral.lpszClassName = L"general_window";
	wgeneral.hCursor = LoadCursorW( NULL , IDC_ARROW );
	wgeneral.hInstance = hInstance;
	wgeneral.cbClsExtra = 0;
	wgeneral.cbWndExtra = 0;
	wgeneral.hIcon = ( HICON ) LoadImageW( 
		NULL , 
		IDI_APPLICATION , 
		IMAGE_ICON , 
		0 , 
		0 , 
		LR_DEFAULTSIZE );

	wgeneral.lpszMenuName = NULL;
	wgeneral.hbrBackground = NULL;
	wgeneral.style = CS_HREDRAW|CS_VREDRAW;

	return RegisterClassW( &wdm ) && RegisterClassW(&wgeneral );
}

bool dialog_manager::window_create( )
{
	return (hManager = CreateWindowExW(
		WS_EX_TOOLWINDOW |
		WS_EX_NOACTIVATE |
		WS_EX_LAYERED |
		WS_EX_TOPMOST |
		WS_EX_TRANSPARENT ,
		L"dialog_manager" ,
		L"dialog_manager" ,
		WS_POPUP ,
		0 , 0 , 0 , 0 ,
		NULL ,
		NULL ,
		hInstance ,
		NULL ));
}

bool dialog_manager::window_sethook( )
{
	hMsgfilter = SetWindowsHookExW(
		WH_CALLWNDPROC ,
		internal_msghook_proc,
		hInstance,
		GetCurrentThreadId() );
	int r = GetLastError( );

	return hMsgfilter;
}

LRESULT CALLBACK internal_window_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static const auto app = application::instance( );

	// TODO：对不同消息做不同处理 打包后再交给dispatcher
	if ( hWnd == 0 )
		return 0;
	MSG m;
	
	m.message = uMsg;
	m.hwnd = hWnd;
	m.wParam = wParam;
	m.lParam = lParam;
	return app->dm->window_proc(m);
}
LRESULT CALLBACK internal_msghook_proc(int nCode ,WPARAM wParam ,LPARAM lParam)
{
	static const auto app = application::instance( );
	return app->dm->msghook_proc( nCode , wParam , lParam );
}

