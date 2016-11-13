
#ifndef ASSET_SYSTEM_CLASS_HPP
#define ASSET_SYSTEM_CLASS_HPP

# include <cstdint>
# include <string>
#include <map>
#include "assetSystemWorker.class.hpp"

# define WORKER_NUMBER 4

class assetSystem {

public: 

	enum e_asset_state {
		E_UNDEF = 0,
		E_LOADING,
		E_LOADED,
		E_ERR
	};

	assetSystem();
	~assetSystem();

	uint64_t					load_asset(t_job job);
	void 						free_all();

	void 						create_job();

	bool						asset_ready(void *ptr);

	void 						set_asset_state(assetSystem::e_asset_state state, uint64_t ref);
	assetSystem::e_asset_state	get_asset_state(uint64_t ref);

	void 						*get_data_ptr(uint64_t ref);

private:

	assetSystemWorker									workers[WORKER_NUMBER];
	uint8_t												workers_index;
	std::map<uint64_t, assetSystem::e_asset_state>		data_status;
	std::map<uint64_t, void*>							ref_to_ptr;
	uint64_t	 										referencer;

};

#endif