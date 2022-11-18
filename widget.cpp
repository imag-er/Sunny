#include "widget.h"
#include "information_stream.h"

widget::widget( const pwidget& parent_):
	parent(parent_ )
{
	if ( parent == nullptr )
		return;
	parent->add_child( this );
}

widget::~widget( )
{
	if ( !childs.empty( ) )
		for ( const pwidget& c : childs )
			delete c;

	if ( parent == nullptr )
		return;
}

void widget::add_child( const pwidget& w)
{
	childs.insert( w );
}

void widget::remove_child( const pwidget& w)
{
	childs.erase( w );
	delete w;
}
