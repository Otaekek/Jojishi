#ifndef STATICMEMORYMANAGER_CLASS_HPP
#define STATICMEMORYMANAGER_CLASS_HPP

#define NUMCLUSTER 1
#define MAXREF 4096

#include <cstdint>
#include "../memory_allocator/stackAllocator.class.hpp"
#include <cstring>
#include <mutex>

typedef struct 			s_loadHeader {
	stackAllocator 		*allocator;
	uint64_t 			ref;
}						t_loadHeader;

class staticMemoryManager {

public:

	enum e_asset_state {
		E_UNDEF = 0,
		E_LOADING,
		E_LOADED,
		E_ERR
	};

	enum E_ASSET_TYPE {
		E_OBJ_FILE = 0,
		E_ENUM_SIZE,
	};

	static uint64_t									load_asset(void *loadData);

	static staticMemoryManager::e_asset_state		get_asset_state(uint64_t ref);

	static void 									set_asset_state(staticMemoryManager::e_asset_state state, uint64_t ref);
	static void										asset_loaded(E_ASSET_TYPE type, t_loadHeader header);
	static void 									*get_data_ptr(uint64_t ref);
	static void 									free_all();

	static bool										all_read();

private:

	static void										merge(stackAllocator *allocator, staticMemoryManager::E_ASSET_TYPE type);
	static stackAllocator							clusters[NUMCLUSTER];
	static staticMemoryManager::e_asset_state		data_status[MAXREF];
	static void										*ref_to_ptr[MAXREF];
	static uint64_t	 								referencer;
	static uint32_t									count;
	static std::mutex								mutexes[NUMCLUSTER];
};

#endif