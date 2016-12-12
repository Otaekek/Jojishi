#ifndef INPUTBUILTIN_CLASS_HPP
#define INPUTBUILTIN_CLASS_HPP

#include <glfw3.h>
#include <renderBuiltIn.class.hpp>

class inputBuiltin {

public:

	static void init();
	static void shutdown();

	static void update();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void hide_cursor();

	static bool		key_pressed[4096];
	static float	_mouseYPos;
	static float	_mouseXPos;
	static float	_relMouseYPos;
	static float	_relMouseXPos;
};

#endif