#ifndef JOBSYSTEM_HPP
#define JOBSYSTEM_HPP

typedef struct 	s_job {
	void (*fptr)(void *);
	void *data;
}				t_job;

#endif