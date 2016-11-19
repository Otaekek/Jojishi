#include "memory_allocator/stackAllocator.class.hpp"
#include "static_memory_manager/staticMemoryManager.class.hpp"
#include "job_system/jobSystem.hpp"
#include "file_loader/fileLoader.class.hpp"
#include <cstdlib>
#include <iostream>
#include "job_system/jobHandler.class.hpp"
#include "../assimp/include/assimp/Importer.hpp"

int main()
{
	fileLoader::init();

	t_job job;

	jobHandler cu;
	uint64_t ref = fileLoader::get_fs_asset(std::string("assets/graphic/mesh/cube/cube.obj"));
	printf("%d\n", staticMemoryManager::get_asset_state(ref));
	return (ref);
}
