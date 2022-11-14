#pragma once
#include <windows.h>
#include <map>
#include <thread>
class Dialog;
// Singleton
class Application
{
public:
	// 提供一个公有的静态接口 获取实例
	static Application* get_instance( );

	static void add_node( HWND,Dialog* );
	static Dialog* get_node( HWND );
	static void exec( );

	HINSTANCE hInstance = 0;

private:
	// 私有化构造函数
	Application( );

	// 维护一个句柄到对象的map
	// 后期要修改成树的形式
	::std::map<HWND , Dialog*> handle_to_Dialog;

	static Application* obj;
};

