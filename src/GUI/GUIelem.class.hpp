#ifndef GUIelem_CLASS_HPP
# define GUIelem_CLASS_HPP

class GUIelem {

public:

	GUIelem(float posx, float posy, float sizex, float sizey, float colliders[], uint32_t numcollider, uint32_t textHandler);
	~GUIelem();

	virtual void		update();
	virtual void		render_spec();
	virtual void		on_mouse_hoover();
	virtual void		on_mouse_rclick(float rposx, float rposy);
	virtual void		on_mouse_lclick(float rposx, float rposy);
	virtual void		on_keyboard_event(int key);

	void				set_size(float x, float y);
	void				set_collider(float colliders[], uint32_t numc);
	void				set_pos(float x, float y);
	void				render(float aposx, float aposy, float asizex, float asizey);
	void				on_mouse_leave();

	uint32_t			_layer;
	float				_colliders[256 * 4];
	float				_collidernum;
	bool				_deleteMe;

protected:

	uint32_t	_textHandler;
	uint32_t	_childnum;
	uint32_t	_childs[256];
	float		_posx;
	float		_posy;
	float		_sizex;
	float		_sizey;

	GUIelem();
};

#endif