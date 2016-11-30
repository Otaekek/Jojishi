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
	//fileLoader::readfile("Makefile");
	renderDataSys::load_programVertexFrag("assets/shaders/basicVertexShader.shader", "assets/shaders/basicFragShader.shader");
	while (1)
	{
		//return 1;
		renderBuiltIn::update();
		usleep(50000);
	}
	transformBuiltin::shutdown();
	jobHandler::shutdown();
	return (0);
}
