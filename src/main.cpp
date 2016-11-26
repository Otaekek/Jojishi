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

	uint32_t t = dynamicMemoryManager::cluster_init(3, 30);
	for (uint32_t i = 0; i < 40; i++)
	{
		uint32_t ref = dynamicMemoryManager::create_slot(t);
		char *mem = (char*)dynamicMemoryManager::get_ptr(ref);
		memcpy(mem, "lol", 3);
		if (!(i % 4))
		dynamicMemoryManager::clear_data(ref, t);
	}
	jobHandler::shutdown();
	return (0);
}
