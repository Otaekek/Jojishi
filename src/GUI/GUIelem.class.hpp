#ifndef GUIelem_CLASS_HPP
# define GUIelem_CLASS_HPP

class GUIelem {

public:

	GUIelem(uint32_t rendererID);
	~GUIelem();

	virtual void		on_mouse_hoover();
	virtual void		on_mouse_rclick(float rposx, float rposy);
	virtual void		on_mouse_lclick(float rposx, float rposy);
	virtual void		on_keyboard_event(int key);
	virtual void		on_mouse_leave();

	bool				_deleteMe;
	uint32_t			_rendererID;

protected:

	GUIelem();
};

#endif
