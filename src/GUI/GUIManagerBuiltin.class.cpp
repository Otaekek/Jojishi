uint32_t	GUIManagerBuiltin::_GUIelem _guiElem[4096] = {0};
uint32_t	GUIManagerBuiltin::_numElem = 0;

void GUIManagerBuiltin::init()
{
	add_mouse_move_callback(GUI_mouse_move_callback);
	add_keyboard_callback(GUI_keyboard_callback);
	add_mouse_button_callback(GUI_mouse_click_callback);
}

void GUIManagerBuiltin::shutdown()
{

}

void GUIManagerBuiltin::update()
{
	for (uint32_t i = 0; i < _numElem; i++)
	{
		(GUIelem*)dynamicMemoryManager::get_ptr(_guiElem[i])->update();
		(GUIelem*)dynamicMemoryManager::get_ptr(_guiElem[i])->render();
	}
}
		
void GUIManagerBuiltin::create(uint32_t guiElemHandler)
{
	if (_numElem >= 4095)
		return ;
	_guiElem[_numElem++] = guiElemHandler;
}

void GUIManagerBuiltin::collide_mouse()
{

}

void	GUIManagerBuiltin::GUI_mouse_click_callback(GLFWwindow *w, int button, int action, int mods)
{

}

void	GUIManagerBuiltin::GUI_mouse_move_callback(GLFWwindow *w, double x, double y)
{

}

void	GUIManagerBuiltin::GUI_keyboard_callback(GLFWwindow *w, int button, int scancode, int action, int mods)
{

}

bool	GUIManagerBuiltin::mouse_collide()
{
	
}
