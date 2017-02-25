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
	{
		printf("Error in %s line %d: too many elems\n", __FILE__, __LINE__);
		return ;
	}
	_guiElem[_numElem++] = guiElemHandler;
}

static float dot(float x1, float y1, float x2, float y2)
{
	
}

static float length(float x, float y)
{
	
}

static bool check_right(float px, float py, float dx, float dy)
{
	float dist;

	dist = dot((px-x0, py-y0), (x1-x0, y1-y0)) / length(x1-x0, y1-y0);
	return ((dist > 0));
}

bool	GUIManagerBuiltin::collide_mouse(float x, float y, uint32_t indexElem)
{
	GUIelem *elem = (GUIelem*)dynamicMemoryManager::get_ptr(_guiElem[i]);
	for (uint32_t i = 0; i < (GUIelem*)dynamicMemoryManager::get_ptr(elem->_collidernum; i++)
		if (check_right(elem->_colliders[i * 4],
			check_right(elem->_colliders[i * 4 + 1],
			check_right(elem->_colliders[i * 4 + 2],
			check_right(elem->_colliders[i * 4 + 3]) == false)
			return (false);
	return (true);
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
