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
#include <mapEditorBuiltin.class.hpp>
#include <directorySmartLoader.class.hpp>
#include <runtimeLibrary.class.hpp>

void init()
{
	texture_builtin::init();
	transformBuiltin::init();
	renderBuiltIn::init();
	fileLoader::init();
	jobHandler::init();
	renderDataSys::init();
	inputBuiltin::init();
	basicFPSControlManagerBuiltin::init();
	mapEditorBuiltin::init();
}

void shutdown()
{
	transformBuiltin::shutdown();
	jobHandler::shutdown();
}

void update()
{
	inputBuiltin::update();
	basicFPSControlManagerBuiltin::update();
	staticMeshManager::update();
	terrainGenerationBuiltin::update();
	basicLightFactory::update();
	mapEditorBuiltin::update();
	renderBuiltIn::update();
}

int main()
{
	uint32_t 	transform;
	uint32_t 	asset;
	uint32_t 	go;
	t_renderGO 	*elem;
	t_renderGO 	*skybox;

	init();

	transform = transformBuiltin::create();
	go = renderBuiltIn::create();
	uint32_t cluster = staticMemoryManager::init_cluster();
	asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/cube/cube.obj", E_3D);
	renderDataSys::set_programm(E_SKYBOX, asset);
	renderBuiltIn::modify_skybox(asset);

	basicFPSControlManagerBuiltin::create(256 * 1300 * -0, 0000, -256 * 1300 * 0, 0, 0, 1, 1);


	renderBuiltIn::modify_skybox_light(1.2);
	basicLightFactory::create(glm::vec3(0, 10000, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(1, 1, 1));

	directorySmartLoader::execute();


	runtimeLibrary::create_lib("assets/levelBuilder/level01");
	
	while (1)
	{
		update();
	}
	shutdown();
	return (0);
}
