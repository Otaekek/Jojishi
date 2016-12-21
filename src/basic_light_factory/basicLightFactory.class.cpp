#include "basicLightFactory.class.hpp"

basicLight::basicLight()
{
	transformHandler = 0;
	lightHandler = 0;
}

basicLight::basicLight(glm::vec3 position, glm::vec3 direction, glm::vec3 scale, E_LIGHT type, glm::vec3 color)
{
	t_light		*light;

	transformHandler = transformBuiltin::create();
	tranformBuiltin::scale(transformHandler, scale.x, scale.y, scale.z);
	transformBuiltin::translate(transformHandler, position.x, position.y, position.z);
	transformHandler::rotate(transformHandler, rotate.x, rotate.y, rotate.z);

	lightHandler = renderBuiltIn::create_light();
	light = renderBuiltIn::get_light(lightHandler);
	light->type = type;
	light->color = color;
	light->attenuation = 1;
	light->linearAttenuation = 1;
	light->quadraticAttenuation = 1;
}

basicLight::~basicLight()
{

}

void basicLight::update()
{

}


uint32_t		basicLightFactory::numElem = 0;
basicLight		basicLightFactory::elems[LIGHT_FACTORY_MAX_ELEM];

void		basicLightFactory::init()
{

}

void		basicLightFactory::shutdown()
{

}

void		basicLightFactory::create(glm::vec3 position, glm::vec3 direction, glm::vec3 scale, E_LIGHT type, glm::vec3 color)
{

}

void		basicLightFactory::update()
{

}




