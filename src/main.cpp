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
	(*mdr->allocator).mem_alloc(4);
	ptr = (*mdr->allocator).get_offset();
	printf("Job Finished ! Ref: %zu Data ptr: %p\n\n", mdr->ref, ptr);
	a.set_asset_state(assetSystem::E_LOADED, mdr->ref);
}

int main()
{
	t_job job;

	t_loadHeader mdr[8];

	job.fptr = loader;

	uint64_t (groupe_dasset[8]);
	for (uint i = 0 ; i < 8; i++)
	{
		job.data = &(mdr[i]);
		groupe_dasset[i] = a.load_asset(job);
	}
	for (uint i = 0 ; i < 8; i++)
	{
		a.create_job();
	}
	return (0);
}
