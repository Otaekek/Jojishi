
#include "inputBuiltin.class.hpp"

bool inputBuiltin::key_pressed[4096] = {false};

float inputBuiltin::_mouseXPos = 0;
float inputBuiltin::_mouseYPos = 0;


float inputBuiltin::_relMouseYPos = 0;
float inputBuiltin::_relMouseXPos = 0;

void inputBuiltin::init()
{
	glfwSetKeyCallback(renderBuiltIn::get_window(), inputBuiltin::key_callback);
	glfwSetMouseButtonCallback(renderBuiltIn::get_window(), inputBuiltin::mouse_button_callback);
	glfwSetCursorPos(renderBuiltIn::get_window(), renderBuiltIn::get_mode()->width / 2, renderBuiltIn::get_mode()->height / 2);
}

void inputBuiltin::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		key_pressed[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		key_pressed[button] = false;
	}
}


void inputBuiltin::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		key_pressed[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		key_pressed[key] = false;
	}
}

void inputBuiltin::shutdown()
{

}

void inputBuiltin::update()
{
	glfwPollEvents();
}

void inputBuiltin::hide_cursor()
{
	glfwSetInputMode(renderBuiltIn::get_window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void  inputBuiltin::add_mouse_move_callback(void (*f)(GLFWwindow *w, double x, double y))
{
	glfwSetCursorPosCallback(renderBuiltIn::get_window(), f);
}