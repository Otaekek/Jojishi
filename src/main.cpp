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
#include <texture_builtin.class.hpp>
#include <basicMeshFactory.class.hpp>
#include <basicLightFactory.class.hpp>
#include <terrainGenerationBuiltin.class.hpp>

int main()
{
	texture_builtin::init();
	transformBuiltin::init();
	renderBuiltIn::init();
	fileLoader::init();
	jobHandler::init();
	renderDataSys::init();
	inputBuiltin::init();
	basicFPSControlManagerBuiltin::init();
	uint32_t transform;
	uint32_t asset;
	uint32_t go;
	transform = transformBuiltin::create();
	t_renderGO *elem;
	go = renderBuiltIn::create();
	uint32_t cluster = staticMemoryManager::init_cluster();
	asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/cube/cube.obj", cluster);
	renderDataSys::set_programm(E_SKYBOX, asset);
	renderBuiltIn::modify_skybox(asset);
	fileLoader::load_fs_asset_async("assets/graphic/mesh/lamborghini/Avent.obj", cluster);
	fileLoader::load_fs_asset_async("assets/graphic/mesh/IronMan/IronMan.obj", cluster);

	asset = fileLoader::load_fs_asset_async("assets/graphic/mesh/castle/castle/castle.obj", cluster);
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
	staticMeshManager::create(glm::vec3(10000, 1000, 10000), glm::vec3(0, 1.0, 0), 0, glm::vec3(10, 10, 10), "assets/graphic/mesh/castle/castle/castle.obj");
	staticMeshManager::create(glm::vec3(10000, 1000, 12000), glm::vec3(0, 1.0, 0), 0, glm::vec3(10, 10, 10), "assets/graphic/mesh/castle/castle/castle.obj");
	staticMeshManager::create(glm::vec3(9000, 0, 9000), glm::vec3(1.0, 0.0, 0), 0, glm::vec3(800.5, 800.3, 800.5) ,"assets/graphic/mesh/lamborghini/Avent.obj");
	
	staticMeshManager::create(glm::vec3(8000, 1000, 10000), glm::vec3(0, 1.0, 0), 0, glm::vec3(10, 10, 10), "assets/graphic/mesh/castle/castle/castle.obj");
	staticMeshManager::create(glm::vec3(8000, 400, 1000), glm::vec3(0, 1.0, 0), 1, glm::vec3(200, 200, 200) , "assets/graphic/mesh/IronMan/IronMan.obj");
	staticMeshManager::create(glm::vec3(800, 0, 200), glm::vec3(1.0, 0.0, 0), 0, glm::vec3(1000.5, 1000.3, 1000.5) ,"assets/graphic/mesh/lamborghini/Avent.obj");
	renderBuiltIn::modify_skybox_light(1.2);
	basicLightFactory::create(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));
	basicLightFactory::create(glm::vec3(0, 80000, 51200), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));
	//basicLightFactory::create(glm::vec3(-200, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));
	//basicLightFactory::create(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));
		//terrainGenerationBuiltin::add_biom(0, 0, 0,256,
		//			200, 2000, texture_builtin::create_instance(fileLoader::load_fs_asset_sync("assets/graphic/texture/rock.jpeg", 1)), 10,
		///			texture_builtin::create_instance(fileLoader::load_fs_asset_sync("assets/graphic/texture/mountain.png", 1)));
		terrainGenerationBuiltin::add_biom(0, 0, 0,256,
				80, 400, texture_builtin::create_instance(fileLoader::load_fs_asset_sync("assets/graphic/texture/grass.jpg", 1)), 10,
				texture_builtin::create_instance(fileLoader::load_fs_asset_sync("assets/graphic/texture/hills.jpg", 1)));
		//terrainGenerationBuiltin::add_biom(51200, 0, 0,256,
		//			200, 260, texture_builtin::create_instance(fileLoader::load_fs_asset_sync("assets/graphic/texture/grass.jpg", 1)), 10,
		//			texture_builtin::create_instance(fileLoader::load_fs_asset_sync("assets/graphic/texture/hills.jpg", 1)));
	
	while (1)
	{
		//printf("%d\n", i++);
		inputBuiltin::update();
		basicFPSControlManagerBuiltin::update();
		staticMeshManager::update();
		terrainGenerationBuiltin::update();
		basicLightFactory::update();
		renderBuiltIn::update();
	}
	transformBuiltin::shutdown();
	jobHandler::shutdown();
	return (0);
}

















