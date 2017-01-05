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
#include <basicFPSControlBuiltin.class.hpp>
#include <inputBuiltin.class.hpp>
#include <basicMeshFactory.class.hpp>
#include <basicLightFactory.class.hpp>
#include <terrainGenerationBuiltin.class.hpp>

int main()
{
	transformBuiltin::init();
	renderBuiltIn::init();
	fileLoader::init();
	//jobHandler::init();
	renderDataSys::init();
	inputBuiltin::init();
	basicFPSControlManagerBuiltin::init();
	uint32_t transform;
	uint32_t asset;
	uint32_t go;
	transform = transformBuiltin::create();
	t_renderGO *elem;
	go = renderBuiltIn::create();
	asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/cube/cube.obj", staticMemoryManager::E_OBJ_FILE);
	renderDataSys::set_programm(E_SKYBOX, asset);
	renderBuiltIn::modify_skybox(asset);
	//fileLoader::load_fs_asset_sync("assets/graphic/mesh/lamborghini/Avent.obj", staticMemoryManager::E_OBJ_FILE);
	//fileLoader::load_fs_asset_sync("assets/graphic/mesh/IronMan/IronMan.obj", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("assets/graphic/mesh/castle/castle/castle.obj", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/Altair/altair.3ds", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/maiden/crystal_maiden_econ1.fbx", staticMemoryManager::E_OBJ_FILE);
	//fileLoader::load_fs_asset_sync("assets/graphic/mesh/land/OBJ/Models_OBJ/Terrain_500000.obj", staticMemoryManager::E_OBJ_FILE);
	//fileLoader::load_fs_asset_sync("./assets/graphic/mesh/witcher/Geralt/Geralt.obj", staticMemoryManager::E_OBJ_FILE);

	basicFPSControlManagerBuiltin::create(0, 0, 0, 0, 0, 1, 1);

/*	basicFPSControlManagerBuiltin::create(-200, 0, 0, 0.5, 0.5, 0.5, 0.5);
	basicFPSControlManagerBuiltin::create(0, 0, 200, 0, 0.5, 0.25, 0.5);
	basicFPSControlManagerBuiltin::create(200, 0, 0, 0.25, 0.5, 0.25, 0.5);
	basicFPSControlManagerBuiltin::create(0, 200, 0, 0.87, 0.13, 0.12, 0.12);
	*/
	uint t = 0;
	uint k = 0;
	float count = 0;
	int i = 0;
	t_renderGO *skybox;
	skybox = renderBuiltIn::get_skyboxGO();
	//staticMeshManager::create(glm::vec3(0, 0, 0), glm::vec3(0, 1.0, 0), 0, glm::vec3(300, 300, 300), "./assets/graphic/mesh/witcher/Geralt/Geralt.obj");
	//staticMeshManager::create(glm::vec3(0, 0, 0), glm::vec3(0, 1.0, 0), 1, glm::vec3(1, 1, 1) , "assets/graphic/mesh/IronMan/IronMan.obj");
	//staticMeshManager::create(glm::vec3(800, 0, 200), glm::vec3(1.0, 0.0, 0), 0, glm::vec3(0.5, 0.3, 0.5) ,"assets/graphic/mesh/land/OBJ/Models_OBJ/Terrain_500000.obj");
	renderBuiltIn::modify_skybox_light(1.2);
	basicLightFactory::create(glm::vec3(0, 1000, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));
	//basicLightFactory::create(glm::vec3(-200, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));
	//basicLightFactory::create(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));

	terrainGenerationBuiltin::add_biom(0, 0, 1000);
	while (1)
	{
		//printf("%d\n", i++);
		terrainGenerationBuiltin::update();
		staticMeshManager::update();
		inputBuiltin::update();
		basicFPSControlManagerBuiltin::update();
		basicLightFactory::update();
		renderBuiltIn::update();
	}
	transformBuiltin::shutdown();
	//jobHandler::shutdown();
	return (0);
}

















