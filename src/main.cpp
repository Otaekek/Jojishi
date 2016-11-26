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

void display_mat(uint32_t ref)
{
	glm::mat4 kek =   transformBuiltin::to_mat(ref);

	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", kek[i][j]);
		}
		printf("\n");
	}

	glm::vec3 dir = transformBuiltin::get_direction(ref);
	printf("x: %f y: %f z: %f\n", dir.x, dir.y, dir.z);
	printf("\n");
}

void display_dir() {

}

void display_euler() {

}

int main()
{
	fileLoader::init();
	jobHandler::init();
	transformBuiltin::init();

	for (uint32_t i = 0; i < 6; i++)
	{

		uint32_t ref = transformBuiltin::create();
		transformBuiltin::rotate(ref, {1, 0, 0}, 1.4);
		transformBuiltin::rotate(ref, {0, 1, 0}, 1.4);
		transformBuiltin::translate(ref, 3, 3, 3);
		transformBuiltin::scale(ref, 3, 3, 3);
		display_mat(ref);
		transformBuiltin::destroy(ref);
	}
	transformBuiltin::shutdown();
	jobHandler::shutdown();
	return (0);
}
