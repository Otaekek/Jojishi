
#ifndef STACKALLOCATOR_CLASS_HPP
#define STACKALLOCATOR_CLASS_HPP

#include <cstdint>

#define DEFAULT_ALLOC_SIZE 134217728

class stackAllocator {

public:

	stackAllocator();
	stackAllocator(uint32_t size);
	~stackAllocator();

	void *get_data_pointer();
	void *get_offset();

	void *mem_alloc(uint32_t size);
	void mem_free(uint32_t size);

	void all_mem_free();

	uint32_t	get_size();

private:

	char 			*data;
	uint32_t		index;
	uint32_t	size;
};

#endif