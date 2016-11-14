
#include "assetSystem.class.hpp"

assetSystem::assetSystem(): workers_index(0), referencer(0)
{

}

assetSystem::~assetSystem()
{

}

uint64_t assetSystem::load_asset(t_job job)
{
	(++workers_index) %= WORKER_NUMBER;
	workers[workers_index].load_asset(job, referencer);
	return(referencer++);
}

void 			assetSystem::free_all()
{
	for (uint8_t i = 0; i < WORKER_NUMBER; i++)
		workers[i].free_all();
}

void 			assetSystem::create_job()
{
	t_loadHeader *header;

	t_job job;
	for (uint8_t i = 0; i < WORKER_NUMBER; i++)
		if (!workers[i].busy() && workers[i].job_waiting())
		{
			job = workers[i].get_job();
			header = (t_loadHeader*)job.data;
			ref_to_ptr[header->ref] = workers[i].get_working_on();
			data_status[header->ref] = assetSystem::E_LOADING;
			job.fptr(job.data);
		}
}
	
bool			assetSystem::asset_ready()
{
	bool all_ready = true;
	for (uint8_t i = 0; i < WORKER_NUMBER; i++)
		all_ready = workers[i].busy() ? false : all_ready;
	return (all_ready);
}

void 			assetSystem::set_asset_state(e_asset_state state, uint64_t ref)
{
	if (state == assetSystem::E_LOADED)
	for (uint8_t i = 0; i < WORKER_NUMBER; i++)
		if (ref_to_ptr[ref] == workers[i].get_working_on())
			workers[i].set_working_on(NULL);
	data_status[ref] = state;
}

assetSystem::e_asset_state	assetSystem::get_asset_state(uint64_t ref)
{
	return (data_status[ref]);
}

void 						*assetSystem::get_data_ptr(uint64_t ref)
{
	return (ref_to_ptr[ref]);
}
