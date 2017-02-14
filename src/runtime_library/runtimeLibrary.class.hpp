#ifndef RUNTIME_LIBRARY_CLASS_HPP
#define RUNTIME_LIBRARY_CLASS_HPP

#include <cstdlib>
#include <math.h> 
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

class runtimeLibrary {

public:

	static void init();
	static void shutdown();

	static void create_lib(char *sourcesPath);
	static void close_lib(void *handle);

private:
	static void compile(char *sourcepath);
	static void *link(char *sourcepath);
	static char *get_string_from_source(char *sourcepath);
	static int count;
};

#endif