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

#include <renderBuiltIn.class.hpp>

int main()
{
	fileLoader::init();
	//jobHandler::init();
	transformBuiltin::init();
	renderBuiltIn::init();

	uint32_t program = renderDataSys::load_programVertexFrag("assets/shaders/basicVertexShader.shader", "assets/shaders/basicFragShader.shader");
	uint32_t transform;
	uint32_t asset;
	uint32_t go;
	transform = transformBuiltin::create();
	t_renderGO *elem;
	go = renderBuiltIn::create();
	asset = fileLoader::get_fs_asset_sync("assets/graphic/mesh/cube/cube.obj", staticMemoryManager::E_OBJ_FILE);
	elem = renderBuiltIn::get_renderGO(go);
	elem->assetHandler = asset;
	elem->transformHandler = transform;
	elem->program = program;
	renderBuiltIn::subscribe(go);
	transformBuiltin::scale(elem->transformHandler, 0.02, 0.02, 0.02);
	int i = 1000;

	while (i--)
	{
		renderBuiltIn::update();
		transformBuiltin::rotate(elem->transformHandler, glm::vec3{0, 1, 0}, 0.1f);
		//sleep(1);
//		transformBuiltin::translate(elem->transformHandler, 0.1, 0.1, 0.1);
		usleep(1.0f / 60.0f * 1000000);
	}
	transformBuiltin::shutdown();
	//jobHandler::shutdown();
	return (0);
}
