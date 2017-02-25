#ifndef GUIMANAGERBUILTIN_CLASS_HPP
#define GUIMANAGERBUILTIN_CLASS_HPP

# include "GUIelem.class.hpp"

class GUIManagerBuiltin {

	public:

		static void init();
		static void shutdown();
		static void update();
		
		static void create(uint32_t guiElemHandler);
		
	private:

		static void mouse_over();
		static void mouse_leave();
		static void mouse_mouseclick();
		static void mouse_keyboard();
		
		static bool mouse_collide();

		static uint32_t		_guiElem[4096];
		static uint32_t		_numElem;

};

#endif