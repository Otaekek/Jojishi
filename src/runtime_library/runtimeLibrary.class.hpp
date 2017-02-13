#ifndef RUNTIME_LIBRARY_CLASS_HPP
#define RUNTIME_LIBRARY_CLASS_HPP

class staticMemoryManager {

public:

	static void init();
	static void shutdown();

	static void create_lib(char *sourcesPath);

private:
	static void compile();
	static void link();
};

#endif