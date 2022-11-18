#pragma once
#include "widget.h"
#include <Windows.h>
class dialog_manager;
class dialog;
using papplication = application*;
// singleton
class application : public widget
{
public:
	static application* instance( );

	dialog_manager* dm = nullptr;
	
	HINSTANCE hInstance;
private:
	application( );
	static application* obj;
};


