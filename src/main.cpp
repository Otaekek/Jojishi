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

int main()
{
	renderBuiltIn::init();
	fileLoader::init();
	//jobHandler::init();
	transformBuiltin::init();
	renderDataSys::init();
	inputBuiltin::init();
	basicFPSControlManagerBuiltin::init();
	uint32_t transform;
	uint32_t asset;
	uint32_t go;
	transform = transformBuiltin::create();
	t_renderGO *elem;
	float light = 0.2;
	float lightA = 0.00005;
	go = renderBuiltIn::create();
	asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/cube/cube.obj", staticMemoryManager::E_OBJ_FILE);
	renderDataSys::set_programm(E_SKYBOX, asset);
	renderBuiltIn::modify_skybox(asset);
	//asset = fileLoader::load_fs_asset_sync("assets/graphic/mesh/lamborghini/Avent.obj", staticMemoryManager::E_OBJ_FILE);
	asset = fileLoader::load_fs_asset_sync("assets/graphic/mesh/IronMan/IronMan.obj", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("assets/graphic/mesh/castle/castle/castle.obj", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/Altair/altair.3ds", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/maiden/crystal_maiden_econ1.fbx", staticMemoryManager::E_OBJ_FILE);
	//asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/riven/Championship Riven.obj", staticMemoryManager::E_OBJ_FILE);


	elem = renderBuiltIn::get_renderGO(go);
	elem->assetHandler = asset;
	elem->transformHandler = transform;
	//elem->program = program;
	//renderDataSys::modifyVertices(asset, glm::vec3(20, -10, 0), 0, glm::vec3(0, 0, 0));
	//transformBuiltin::scale(elem->transformHandler, 2000.2, 2000.2, 2000.2);
	//transformBuiltin::rotate_model(elem->transformHandler, glm::vec3{1, 0, 0}, -1.57f);
	//transformBuiltin::rotate_model(elem->transformHandler, glm::vec3{1, 0, 0}, -0.15f);
	transformBuiltin::translate(elem->transformHandler, 0, -0, -2.01);
	basicFPSControlManagerBuiltin::create(0, 0, 0, 0, 0, 1, 1);

	uint t = 0;
	uint k = 0;
	float count = 0;
	int i = 0;
	t_renderGO *skybox;
	skybox = renderBuiltIn::get_skyboxGO();
	while (1)
	{
		//printf("%d\n", i++);
		count +=  1.0f / (((float)(((clock() - t))) / CLOCKS_PER_SEC));
		if (k++ > 100)
		{
		//	printf("%f\n", count / k);
			k = 0;
			count = 0;
		}
		//usleep(1.0f / 60000000);
		t = clock();
		if (light > 1.2 || light < 0.2)
			lightA *= -1;
		light += lightA;
		renderBuiltIn::modify_skybox_light(light);
		renderBuiltIn::render_me(go);
		//transformBuiltin::rotate_model(elem->transformHandler, glm::vec3{0, 1, 0}, 0.005f);
		transformBuiltin::rotate(skybox->transformHandler, glm::vec3(0, 1, 0), 0.0001);
		inputBuiltin::update();
		basicFPSControlManagerBuiltin::update();
		renderBuiltIn::update();
	}
	transformBuiltin::shutdown();
	//jobHandler::shutdown();
	return (0);
}

















