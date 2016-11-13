
#include "stackAllocator.class.hpp"

stackAllocator::stackAllocator()
{
	size = DEFAULT_ALLOC_SIZE;
	index = 0;
	data = new char[DEFAULT_ALLOC_SIZE];
}

stackAllocator::stackAllocator(uint32_t _size)
{
	size = _size;
	index = 0;
	data = new char(_size);
}

stackAllocator::~stackAllocator()
{
	delete(data);
}

void stackAllocator::all_mem_free()
{
	index = 0;
}

void *stackAllocator::mem_alloc(uint32_t size)
{
	index += size;
	return (index + data - size);
}

void stackAllocator::mem_free(uint32_t size)
{
	index -= size;
}

void *stackAllocator::get_data_pointer()
{
	return (data);
}

void *stackAllocator::get_offset()
{
	return (index + data);
}