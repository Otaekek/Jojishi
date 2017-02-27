#ifndef GUIMANAGERBUILTIN_CLASS_HPP
#define GUIMANAGERBUILTIN_CLASS_HPP

# include "GUIelem.class.hpp"

typedef struct 	s_guiElem {

	void (on_mouse_hoover*)();
	void		(on_mouse_rclick*)(float rposx, float rposy);
	void		on_mouse_lclick(float rposx, float rposy);
	virtual void		on_keyboard_event(int key);
	virtual void		on_mouse_leave();
	
}				t_GUIelem;

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

		static uint32_t		_guiElem[4096];
		static uint32_t		_numElem;

};

#endif