#include "memory_allocator/stackAllocator.class.hpp"
#include "asset_database_system/assetSystem.class.hpp"
#include "job_system/jobSystem.hpp"
#include "file_loader/fileLoader.class.hpp"
#include <cstdlib>
#include <iostream>

#include "../assimp/include/assimp/Importer.hpp"

assetSystem g_asset_db;

int main()
{
	fileLoader::init();

	t_job job;

	uint64_t ref = fileLoader::get_fs_asset(std::string("assets/graphic/mesh/cube/cube.obj"),
		assetSystemWorker::E_OBJ_FILE);
	 ref = fileLoader::get_fs_asset(std::string("assets/graphic/mesh/mercedes/mercedes.obj"),
		assetSystemWorker::E_OBJ_FILE);

	while (g_asset_db.create_job(&job))
	{
		job.fptr(job.data);
		printf("%d\n", g_asset_db.get_asset_state(ref));
	}
	return (ref);
}
