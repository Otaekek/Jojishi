# include "assetSystemWorker.class.hpp"

assetSystemWorker::assetSystemWorker(): allocator(ALLOC_SIZE),
	data(allocator.get_data_pointer()),
	working_on(NULL), q_index(0)
{

}

assetSystemWorker::~assetSystemWorker()
{

}

void assetSystemWorker::load_asset(t_job job, uint64_t ref)
{
	t_loadHeader *header;

	header = (t_loadHeader*)job.data;
	header->ref = ref;
	queue[q_index] = job;
	q_index++;
}

void assetSystemWorker::free_all()
{
	allocator.all_mem_free();
}

t_job assetSystemWorker::get_job()
{
	t_loadHeader *header;

	header = (t_loadHeader*)queue[q_index - 1].data;
	header->allocator = &allocator;
	working_on = allocator.get_offset();
	q_index--;
	return (queue[q_index]);
}

bool assetSystemWorker::job_waiting()
{
	return ((q_index > 0));
}

bool assetSystemWorker::busy()
{
	return ((working_on != NULL));
}

void *assetSystemWorker::get_working_on()
{
	return (working_on);
}
	
void assetSystemWorker::set_working_on(void *v)
{
	working_on = v;
}