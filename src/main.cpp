#include "memory_allocator/stackAllocator.class.hpp"
#include "asset_database_system/assetSystem.class.hpp"
#include "job_system/jobSystem.hpp"
#include <cstdlib>
#include <iostream>

assetSystem a;

void loader(void *data)
{
	t_loadHeader *mdr;

	mdr = (t_loadHeader*)data;
	void *ptr = (*mdr->allocator).get_offset();
	printf("Job created ! Ref: %zu Data ptr: %p\n", mdr->ref, ptr);
	ptr = (*mdr->allocator).get_offset();
	char *q = (char*)mdr->allocator->mem_alloc(16);
	q[0] = 3;
	printf("Job Finished ! Ref: %zu Data ptr: %p\n\n", mdr->ref, ptr);
	a.set_asset_state(assetSystem::E_LOADED, mdr->ref);
}

int main()
{
	t_job job;

	t_loadHeader mdr[8000];

	job.fptr = loader;

	uint64_t (groupe_dasset[8000]);
	for (uint i = 0 ; i < 8000; i++)
	{
		job.data = &(mdr[i]);
		groupe_dasset[i] = a.load_asset(job);
	}
	for (uint i = 0 ; i < 8000; i++)
	{
		a.create_job();
	}
	printf("mdr\n");
	return (0);
}
