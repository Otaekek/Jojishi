#include "jobHandler.class.hpp"

jobHandler::jobHandler(): slaves({std::thread(jobHandler::job_worker, queue[0]),
 std::thread(jobHandler::job_worker, queue[1]),
 std::thread(jobHandler::job_worker, queue[2]),
 std::thread(jobHandler::job_worker, queue[3]),
 std::thread(jobHandler::job_worker, queue[4]),
 std::thread(jobHandler::job_worker, queue[5]),
 std::thread(jobHandler::job_worker, queue[6]),
 std::thread(jobHandler::job_worker, queue[7])})
{

}

jobHandler::~jobHandler()
{
	for (uint8_t i = 0; i < NUMTHREAD; i++)
		slaves[i].join();
}

void jobHandler::push_job(t_job job)
{

}

void jobHandler::job_worker(t_job queue[MAXJOB])
{

}