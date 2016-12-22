#include "basicMeshFactory.class.hpp"

staticMesh::staticMesh()
{
}

staticMesh::staticMesh(glm::vec3 pos, glm::vec3 rot, float angle, glm::vec3 scale, std::string meshName)
{
	t_transform *transform;
	t_renderGO *renderGO;

	transformHandler = transformBuiltin::create();
	assetHandler = fileLoader::get_fs(meshName);
	renderGOhandler = renderBuiltIn::create();

	transform = transformBuiltin::get_transform(transformHandler);
	renderGO = renderBuiltIn::get_renderGO(renderGOhandler);
	renderGO->transformHandler = transformHandler;
	renderGO->assetHandler = assetHandler;
	renderGO->cullOnMe = true;
	renderGO->cullMode = GL_BACK;
	transformBuiltin::translate(transformHandler, pos.x, pos.y, pos.z);
	transformBuiltin::rotate(transformHandler, rot, angle);
	transformBuiltin::scale(transformHandler, scale.x, scale.y, scale.z);
}

staticMesh::~staticMesh()
{

}

void staticMesh::update()
{
	renderBuiltIn::render_me(renderGOhandler);
}

uint32_t		staticMeshManager::numElem = 0;
staticMesh		staticMeshManager::elems[MESH_FACTORY_MAX_ELEM];

void		staticMeshManager::init()
{

}

void		staticMeshManager::shutdown()
{

}

void		staticMeshManager::create(glm::vec3 pos, glm::vec3 rot, float angle, glm::vec3 scale, std::string meshName)
{
	elems[numElem++] = staticMesh(pos, rot, angle, scale, meshName);
}

void		staticMeshManager::update()
{
	for (uint32_t i = 0; i < numElem; i++)
		elems[i].update();
}

