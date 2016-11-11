
#include "stackAllocator.class.hpp"

stackAllocator::stackAllocator()
{
	size = DEFAULT_ALLOC_SIZE;
	data = new char[DEFAULT_ALLOC_SIZE];
}

stackAllocator::stackAllocator(uint32_t _size)
{
	size = _size;
	data = new char(_size);
}

stackAllocator::~stackAllocator()
{
	delete(data);
}

void *stackAllocator::mem_alloc(uint32_t size)
{
	void *ret;

	ret = data;
	index += size;
	return (ret);
}

void stackAllocator::mem_free(uint32_t size)
{
	index -= size;
}
