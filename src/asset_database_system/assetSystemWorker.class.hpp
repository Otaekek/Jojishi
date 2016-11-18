#ifndef ASSETSYSTEMWORKER_CLASS_HPP
#define ASSETSYSTEMWORKER_CLASS_HPP

#include "../memory_allocator/stackAllocator.class.hpp"
#include "../job_system/jobSystem.hpp"
#include <string>

#define ALLOC_SIZE 65536
#define MAX_LOADING 4096

typedef struct 			s_loadHeader {
	stackAllocator 		*allocator;
	uint64_t 			ref;
}						t_loadHeader;

class assetSystemWorker {

public:

	enum E_ASSET_TYPE {
		E_OBJ_FILE = 0,
		E_ENUM_SIZE,
	};

	assetSystemWorker();
	~assetSystemWorker();

	void load_asset(t_job job, uint64_t ref);

	void free_all();

	bool busy();
	bool job_waiting();

	t_job get_job();

	void *get_working_on();

	void set_working_on(void *v);
private:

	stackAllocator 				allocator;
	void 						*data;
	void 						*working_on;
	t_job						queue[MAX_LOADING];

	uint16_t					q_index;
};

#endif