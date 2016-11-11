
#ifndef STACKALLOCATOR_CLASS_HPP
#define STACKALLOCATOR_CLASS_HPP

#include <cstdint>

#define DEFAULT_ALLOC_SIZE 4096

class stackAllocator {

public:

	stackAllocator();
	stackAllocator(uint32_t size);
	~stackAllocator();

	void *mem_alloc(uint32_t size);
	void mem_free(uint32_t size);

private:

	char 			*data;
	uint32_t		index;
	uint32_t	size;
};

#endif