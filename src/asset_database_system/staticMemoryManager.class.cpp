#include "staticMemoryManager.class.hpp"

stackAllocator											staticMemoryManager::clusters[NUMCLUSTER];
assetSystem::e_asset_state								staticMemoryManager::data_status[MAXREF];
void													staticMemoryManager::*ref_to_ptr[MAXREF];
uint64_t	 											staticMemoryManager::referencer = 0;
uint32_t												count = 0;

uint64_t							staticMemoryManager::load_asset(void *loadData)
{
	t_loadHeader header;

	referencer++;
	header.ref = referencer;
	header.allocator = new allocator();
	memcpy(loadData, &header, sizeof(t_loadHeader));
	set_asset_state(E_LOADING, ref);
	count++;
	return (referencer);
}

assetSystem::e_asset_state			staticMemoryManager::get_asset_state(uint64_t ref)
{
	return (data_status[ref]);
}

void 								staticMemoryManager::set_asset_state(assetSystem::e_asset_state state, uint64_t ref)
{
	data_status[ref] = state;
}

void								staticMemoryManager::asset_loaded(E_ASSET_TYPE type, t_loadHeader header)
{
	count--;
	set_asset_state[header.ref] = E_LOADED;
	merge(header.allocator, type);
}

void 								*staticMemoryManager::get_data_ptr(uint64_t ref)
{
	return (ref_to_ptr[ref]);
}

void 								staticMemoryManager::free_all()
{
	for (uint16_t i = 0; i < NUMCLUSTER, i++)
		clusters[i].free_all();
}

bool								staticMemoryManager::all_read()
{
	return (count == 0);
}


void								staticMemoryManager::merge(stackAllocator *allocator, staticMemoryManager::E_ASSET_TYPE type)
{
	memcpy(clusters[type].get_offset(), allocator->get_data_ptr(), allocator->get_size());
	delete allocator;
}