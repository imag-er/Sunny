#pragma once
#include <memory>
#include <set>
class widget;
using pwidget = widget*;
class widget
{
public:

	pwidget parent;
	widget(const pwidget&);

	// 被动释放 由父类调用
	// 主动释放应该提交请求给父类 由父类来处理
	~widget( );

	void add_child( const pwidget&);
	void remove_child( const pwidget&);

	std::set<widget*> childs;

private:

};

