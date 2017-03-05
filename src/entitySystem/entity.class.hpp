#ifndef ENTITY_CLASS_HPP
#define ENTITY_CLASS_HPP

#define MAX_COMPONENT 12

class entity {

public:

	void		set_index(uint32_t index) {_manager_index = index;}
	uint32_t	get_index() {return _manager_index;}
	void		update();

private:

	uint32_t	_manager_index;

	uint32_t	_scriptsHandlers[MAX_COMPONENT];
	uint32_t	_scriptsCount;

	uint32_t	_rendersHandlers[MAX_COMPONENT];
	uint32_t	_renderCount;

	uint32_t	_terrainsHandlers[MAX_COMPONENT];
	uint32_t	_terrainCount;

	uint32_t	_lightsHandlers[MAX_COMPONENT];
	uint32_t	_lightCount;

	uint32_t	_camerasHandlers[MAX_COMPONENT];
	uint32_t	_cameraCount;

}

#endif 