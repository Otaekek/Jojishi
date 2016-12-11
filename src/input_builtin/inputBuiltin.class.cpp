
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
	_relMouseXPos = -_mouseXPos;
	_relMouseYPos = -_mouseYPos;
	glfwGetCursorPos(renderBuiltIn::get_window(), (double*)&_mouseXPos, (double*)&_mouseYPos);
	_relMouseYPos += _mouseYPos;
	_relMouseXPos += _mouseXPos;
}

void inputBuiltin::hide_cursor()
{
	glfwSetInputMode(renderBuiltIn::get_window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
