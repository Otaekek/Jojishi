#ifndef JOBHANDLER_CLASS_HPP
# define JOBHANDLER_CLASS_HPP

#include "jobSystem.hpp"

#include <unistd.h>
#include <thread>

#define NUMTHREAD 8
#define MAXJOB 256

class jobHandler {

public:

	jobHandler();
	~jobHandler();

	void push_job(t_job job);

	static void job_worker(t_job queue[MAXJOB]);

private:

	t_job 				queue[NUMTHREAD][MAXJOB];
	std::thread			slaves[NUMTHREAD];

};

#endif