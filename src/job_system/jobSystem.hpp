#ifndef JOBSYSTEM_HPP
#define JOBSYSTEM_HPP

typedef struct 	s_job {
	void 		(*fptr)(void *);
	char		data[256];
}				t_job;

#endif