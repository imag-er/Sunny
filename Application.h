﻿#pragma once
#include <windows.h>
#include <map>
#include <thread>
class dialog;
// Singleton
class application
{
public:
	// 提供一个公有的静态接口 获取实例
	static application* get_instance( );

	static void add_node( HWND,dialog* );
	static dialog* get_node( HWND );
	static uint32_t exec( );

	HINSTANCE hInstance = 0;

private:
	// 私有化构造函数
	application( );

	// 维护一个句柄到对象的map
	// 后期要修改成树的形式
	::std::map<HWND , dialog*> handle_to_Dialog;

	static application* obj;
};

