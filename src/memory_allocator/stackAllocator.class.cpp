
#include "stackAllocator.class.hpp"
#include <cstdio>

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
	data = new char[_size];
}

stackAllocator::~stackAllocator()
{
	delete [] data;
}

void stackAllocator::all_mem_free()
{
	index = 0;
}

void *stackAllocator::mem_alloc(uint32_t _size)
{
	index += _size;
	return (&data[index - _size]);
}

void stackAllocator::mem_free(uint32_t _size)
{
	index -= _size;
}

void *stackAllocator::get_data_pointer()
{
	return (data);
}

void *stackAllocator::get_offset()
{
	return (index + data);
}