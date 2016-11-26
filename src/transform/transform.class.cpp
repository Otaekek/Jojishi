#include <transform.class.hpp>

uint32_t transformBuiltin::cluster_id = 0;

void transformBuiltin::init()
{
	cluster_id = dynamicMemoryManager::cluster_init(sizeof(t_transform), 65536);
}

void transformBuiltin::shutdown()
{

}

uint32_t transformBuiltin::create()
{
	return (dynamicMemoryManager::create_slot(cluster_id));
}

void transformBuiltin::destroy(uint32_t handler)
{
	dynamicMemoryManager::clear_data(handler, cluster_id);
}

glm::vec3 transformBuiltin::get_direction(uint32_t handler)
{
	t_transform transform;
	glm::vec3 axis = {0, 0, 1};

	transform = get_transform(handler);
	axis = axis * transform.rotation;
	return (axis);
}

void transformBuiltin::rotate(uint32_t handler, glm::vec3 axis, float angle)
{
	t_transform transform;

	transform = get_transform(handler);
	transform.rotation = glm::rotate(transform.rotation, angle, axis);
}

void transformBuiltin::rotate_model(uint32_t handler, glm::vec3 axis, float angle)
{
	t_transform transform;

	transform = get_transform(handler);
	axis = axis * transform.rotation;
	transform.rotation = glm::rotate(transform.rotation, angle, axis);
}

void transformBuiltin::translate(uint32_t handler, float &x, float &y, float & z)
{
	t_transform transform;

	transform = get_transform(handler);
	transform.position.x += x;
	transform.position.y += y;
	transform.position.z += z;
}

void transformBuiltin::scale(uint32_t handler, float &x, float &y, float & z)
{
	t_transform transform;

	transform = get_transform(handler);
	transform.scale.x *= x;
	transform.scale.y *= y;
	transform.scale.z *= z;
}

t_transform transformBuiltin::get_transform(uint32_t h)
{
	t_transform *ret;

	ret = (t_transform*)dynamicMemoryManager::get_ptr(h);
	return (*ret);
}

glm::mat4 transformBuiltin::to_mat(uint32_t handler)
{
	t_transform transform;

	transform = get_transform(handler);
	return (glm::mat4_cast(transform.rotation));
}