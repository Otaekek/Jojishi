#include "memory_allocator/stackAllocator.class.hpp"
#include "static_memory_manager/staticMemoryManager.class.hpp"
#include "job_system/jobSystem.hpp"
#include "file_loader/fileLoader.class.hpp"
#include <cstdlib>
#include <iostream>
#include "job_system/jobHandler.class.hpp"
#include "../assimp/include/assimp/Importer.hpp"
#include <unistd.h>

int main()
{
	fileLoader::init();

	t_job job;
	uint32_t ref;

	for (int i = 0; i < 200; i++)
		ref = fileLoader::get_fs_asset_sync(std::string("assets/graphic/mesh/castle/castle.obj"));
	while (!staticMemoryManager::all_read())
		usleep(5000);
	for (int i = 0; i < 200; i++)
		printf("%d\n", staticMemoryManager::get_asset_state(i));
	jobHandler::shutdown();
	return (ref);
}
