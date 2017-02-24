#include "GUIelem.class.hpp"

GUIelem::GUIelem(float posx, float posy, float sizex, float sizey, float colliders[], uint32_t numcollider, uint32_t textHandler)
{
	_posx = posx;
	_posy = posy;
	_sizex = sizex;
	_sizey = sizey;
	set_collider(colliders, numcollider);
	_textHandler = textHandler;
}

GUIelem::~GUIelem()
{

}

void				*GUIelem::operator new(size_t size)
{

}

void				GUIelem::set_size(float x, float y)
{

}

void				GUIelem::set_collider(float colliders[], uint32_t numc)
{
	for (uint32_t i = 0; i < numc; i++)
	{
		_colliders[i * 2] = colliders[i * 2];
		_colliders[i * 2 + 1] = colliders[i * 2 + 1];
	}
	_collidernum = numc;
}

void				GUIelem::set_pos(float x, float y)
{
	_posx = x;
	_posy = y;
}

void				GUIelem::render(float aposx, float aposy, float asizex, float asizey)
{
	render_spec();
	for (uint32_t i = 0; i < _childnum; i++)
		(GUIelem*)dynamicMemoryManager::get_ptr(_childs[i]).render();
	//billboard::push(text, apox + _posx * asizex * _sizex, aposy + _posy * asizey * _sizey, asizex * _sizey, asizey * _sizey);
}

void				GUIelem::update()
{

}

uint32_t			GUIelem::render_spec()
{

}

void				GUIelem::on_mouse_hoover()
{

}

void				GUIelem::on_mouse_rclick(float rposx, float rposy)
{

}

void				GUIelem::on_mouse_lclick(float rposx, float rposy)
{

}

void				GUIelem::on_keyboard_event(int key)
{

}