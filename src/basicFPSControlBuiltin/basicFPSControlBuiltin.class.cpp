#include "basicFPSControlBuiltin.class.hpp"

basicFPSControl::basicFPSControl()
{

}

basicFPSControl::basicFPSControl(float posx, float posy, float posz)
{
	_transformHandler = transformBuiltin::create();
	rotx = 0;
	roty = 0;
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
}

void 		basicFPSControl::behave()
{
	glm::vec3 up = glm::vec3(0, 1, 0);
	float mouseX, mouseY;
	inputBuiltin::hide_cursor();
	mouseX = inputBuiltin::_mouseXPos;
	mouseY = inputBuiltin::_mouseYPos;
	rotx -= mouseX;
	if (fabs(roty -mouseY / 5) < 0.3)
		roty += -mouseY / 5;
	transformBuiltin::euler_angle(_transformHandler, rotx, roty);

	glm::vec3 direction = transformBuiltin::get_direction(_transformHandler);
	glm::vec3 crossDirection = -cross(up, direction);

	if (inputBuiltin::key_pressed[GLFW_KEY_W])
		transformBuiltin::translate(_transformHandler, direction.x, direction.y, direction.z);
	if (inputBuiltin::key_pressed[GLFW_KEY_S])
		transformBuiltin::translate(_transformHandler, -direction.x, -direction.y, -direction.z);
	if (inputBuiltin::key_pressed[GLFW_KEY_D])
		transformBuiltin::translate(_transformHandler, crossDirection.x, crossDirection.y, crossDirection.z);
	if (inputBuiltin::key_pressed[GLFW_KEY_A])
		transformBuiltin::translate(_transformHandler, -crossDirection.x, -crossDirection.y, -crossDirection.z);
	if (inputBuiltin::key_pressed[GLFW_KEY_ESCAPE])
		exit(0);
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

