#include "basicFPSControlBuiltin.class.hpp"

basicFPSControl::basicFPSControl()
{

}

basicFPSControl::basicFPSControl(float posx, float posy, float posz)
{
	_transformHandler = transformBuiltin::create();
	transformBuiltin::translate(_transformHandler, posx, posy, posz);
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

void 		basicFPSControlManagerBuiltin::create(float posx, float posy, float posz)
{
	basicFPSControl control(posx, posy, posz);

	elems[numElem++] = control;
}

