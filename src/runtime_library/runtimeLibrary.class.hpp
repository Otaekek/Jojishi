#ifndef RUNTIME_LIBRARY_CLASS_HPP
#define RUNTIME_LIBRARY_CLASS_HPP

#include <cstdlib>
#include <math.h> 
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h> 
#include <stdio.h>
#include <unistd.h>


class runtimeLibrary {

public:

	static void init();
	static void shutdown();

	static void create_lib(char *sourcesPath);
	static void close_lib(void *handle);

private:
	static char *get_lib_path();
	static void compile(char *sourcepath);
	static void *link(char *sourcepath);
	static char *get_object_from_source(char *sourcepath);
	static char *get_lib_from_source();
	static int count;
};

#endif