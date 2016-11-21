#ifndef POOLALLOCATOR_CLASS_HPP
#define POOLALLOCATOR_CLASS_HPP

#define DEFAULT_BLOC_SIZE 256
#define DEFAULT_BLOC_NUMBER 1024

#include <cstdint>

class poolAllocator {

public: 

	typedef struct 			s_bloc {
		char 				*mem;
		struct s_bloc		*next_elem;
		uint32_t			size;
	}						t_bloc;

	poolAllocator();
	poolAllocator(uint32_t bloc_size, uint32_t bloc_num);
	~poolAllocator();

	poolAllocator::t_bloc 		*mem_alloc(void);
	void 		mem_free(t_bloc *bloc);

private:

	char 		*data;
	t_bloc 		*free_list;
	t_bloc		*free_list_last;
};

#endif