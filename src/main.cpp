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

int main()
{
	fileLoader::init();
	jobHandler::init();

	jobHandler::shutdown();
	return (0);
}
