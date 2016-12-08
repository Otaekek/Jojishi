#include "memory_allocator/stackAllocator.class.hpp"
#include "static_memory_manager/staticMemoryManager.class.hpp"
#include "job_system/jobSystem.hpp"
#include "file_loader/fileLoader.class.hpp"
#include <cstdlib>
#include <iostream>
#include "job_system/jobHandler.class.hpp"
#include "../assimp/include/assimp/Importer.hpp"
#include <unistd.h>
#include "memory_allocator/poolAllocator.class.hpp"
#include "dynamic_memory_manager/dynamicMemoryManager.class.hpp"
#include <transform.class.hpp>
#include <iostream>
#include <glfw3.h>
#include <list>
#include <vector>
#include <ctime>
#include <renderBuiltIn.class.hpp>

int main()
{
	renderBuiltIn::init();
	fileLoader::init();
	//jobHandler::init();
	transformBuiltin::init();
	renderDataSys::init();

	uint32_t transform;
	uint32_t asset;
	uint32_t go;
	transform = transformBuiltin::create();
	t_renderGO *elem;
	go = renderBuiltIn::create();
	//asset = fileLoader::get_fs_asset_sync("assets/graphic/mesh/lamborghini/Avent.obj", staticMemoryManager::E_OBJ_FILE);
	asset = fileLoader::get_fs_asset_sync("assets/graphic/mesh/IronMan/IronMan.obj", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::get_fs_asset_sync("assets/graphic/mesh/castle/castle/castle.obj", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::get_fs_asset_sync("./assets/graphic/mesh/Altair/altair.3ds", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::get_fs_asset_sync("./assets/graphic/mesh/maiden/crystal_maiden_econ1.fbx", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::get_fs_asset_sync("./assets/graphic/mesh/riven/Championship Riven.obj", staticMemoryManager::E_OBJ_FILE);

	elem = renderBuiltIn::get_renderGO(go);
	elem->assetHandler = asset;
	elem->transformHandler = transform;
	//elem->program = program;
	renderBuiltIn::subscribe(go);
	//renderDataSys::modifyVertices(asset, glm::vec3(20, -10, 0), 0, glm::vec3(0, 0, 0));
	//transformBuiltin::scale(elem->transformHandler, 20.2, 20.2, 20.2);
	//transformBuiltin::rotate_model(elem->transformHandler, glm::vec3{1, 0, 0}, -1.57f);
	transformBuiltin::rotate_model(elem->transformHandler, glm::vec3{1, 0, 0}, -0.15f);
	transformBuiltin::translate(elem->transformHandler, 0, -150, -200.01);
	uint t = 0;
	uint k = 0;
	float count = 0;

	while (1)
	{
		count +=  1.0f / (((float)(((clock() - t))) / CLOCKS_PER_SEC));
		if (k++ > 1000)
		{
			printf("%f\n", count / k);
			k = 0;
			count = 0;
		}
		t = clock();
//		i = !i;
		//printf("%d", i);
		//printf("%d\n", i++);
		//printf("%p\n", ouais
		//transformBuiltin::translate(elem->transformHandler, -0.01, 0, -0.01);
		transformBuiltin::rotate_model(elem->transformHandler, glm::vec3{0, 1, 0}, 0.001f);
	//	transformBuiltin::rotate(elem->transformHandler, glm::vec3{0, 0, 1}, 0.001f);
	//	transformBuiltin::rotate(elem->transformHandler, glm::vec3{1, 0, 0}, 0.001f);
	//	transformBuiltin::rotate(elem->transformHandler, glm::vec3{1, 0, 0}, 0.001f);
		renderBuiltIn::update();
	}
	transformBuiltin::shutdown();
	//jobHandler::shutdown();
	return (0);
}

















