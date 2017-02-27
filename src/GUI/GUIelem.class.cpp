#include "GUIelem.class.hpp"

GUIelem::GUIelem(float posx, float posy, float sizex, float sizey, float colliders[], uint32_t numcollider, uint32_t textHandler)
{
	_rendererID = rendererID;
}

GUIelem::~GUIelem()
{

}

void				GUIelem::on_mouse_hoover()
{
	printf("HOOVER !!!\n");
}

void				GUIelem::on_mouse_leave()
{
	printf("LEAVE !!!\n");
}

void				GUIelem::on_mouse_rclick(float rposx, float rposy)
{
	printf("RCLICKZZZ\n");
}

void				GUIelem::on_mouse_lclick(float rposx, float rposy)
{
	printf("LEFTCLIKZZZ\n");
}

void				GUIelem::on_keyboard_event(int key)
{
	printf("KEYZZZ:::: %d\n", key);
}