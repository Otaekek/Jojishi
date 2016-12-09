#include "basicFPSControlBuiltin.class.hpp"

basicFPSControl::basicFPSControl()
{

}

basicFPSControl::basicFPSControl(std::string meshPath, float posx, float posy, float posz)
{
	_transformHandler = transformBuiltin::create();
	transformBuiltin::translate(_transformHandler, posx, posy, posz);
	_assetHandler = fileLoader::load_fs_asset_sync(meshPath, staticMemoryManager::E_OBJ_FILE);
}

basicFPSControl::~basicFPSControl()
{

}

void 		basicFPSControl::update()
{
	render();
	behave();
}

void 		basicFPSControl::render()
{
	renderBuiltIn::add_camera(_transformHandler);
	//renderBuiltIn::add_render(_assetHandler);
	renderBuiltIn::remove_camera(_transformHandler);
}

void 		basicFPSControl::behave()
{

}

basicFPSControl		basicFPSControlManagerBuiltin::elems[MAX_ELEM];
uint32_t			basicFPSControlManagerBuiltin::numElem = 0;

void 		basicFPSControlManagerBuiltin::init()
{

}

void 		basicFPSControlManagerBuiltin::shutdow()
{

}

void 		basicFPSControlManagerBuiltin::update()
{
	for (uint32_t i = 0; i < numElem; i++)
		elems[i].update();
}

void 		basicFPSControlManagerBuiltin::create(std::string path, float posx, float posy, float posz)
{
	basicFPSControl control(path, posx, posy, posz);

	elems[numElem++] = control;
}

