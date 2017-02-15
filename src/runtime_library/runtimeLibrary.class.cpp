#include "runtimeLibrary.class.hpp"

int runtimeLibrary::count = 0;

void runtimeLibrary::init()
{

}

void runtimeLibrary::shutdown()
{

}

void utoa(int n, char *s)
{
    int len = log10(n) + 1;
    int i = 0;

    if (!n)
    {
        s[0] = '0';
        s[1] = 0;
        return ;
    }
    s[len - i] = 0;
    while (n > 0)
    {
        s[len - i - 1] = n % 10 + '0';
        n /= 10;
        i++;
    }
}

char *runtimeLibrary::get_lib_from_source()
{
	char		*str;
	char		tmp[4096];
	char		output[4096];
	uint32_t 	len;

	if (count > 4096)
		count = 0;
	output[0] = 0;
	len = log10(count) + 1;
	str = (char*)malloc(19 + len + 1 + 5 + 400);
	str[0] = 0;
	strcat(str, "g++ -shared -o .rtlib/dylib");
	utoa(count, tmp);
	strcat(str, tmp);
	strcat(str, ".so ");
	strcat(str, " .rtlib/dylib");
	strcat(str, tmp);
	strcat(str, ".o");
	return (str);
}

char *runtimeLibrary::get_object_from_source(char *sourcePath)
{
	char		*str;
	char		tmp[4096];
	uint32_t 	len;

	if (count > 4096)
		count = 0;
	len = log10(count) + 1;
	str = (char*)malloc(19 + len + 1 + 5 + 400);
	str[0] = 0;
	strcat(str, "g++ -fpic -o .rtlib/dylib");
	utoa(count, tmp);
	strcat(str, tmp);
	strcat(str, ".o ");
	strcat(str, " -c ");
	strcat(str, sourcePath);
	return (str);
}

char *runtimeLibrary::get_lib_path()
{
	char *str;

	str = (char*)malloc(30);
	*str = 0;
	strcat(str, ".rtlib/dylib");
	utoa(count, str + 12);
	strcat(str, ".so");
	return (str);
}

void runtimeLibrary::create_lib(char *sourcesPath)
{
	compile(sourcesPath);
}

void runtimeLibrary::compile(char *sourcePath)
{
	char 	*str;
	int		id;
	void (*f)(void);

	id = vfork();
	if (id == 0)
	{
		count++;
		str = get_object_from_source(sourcePath);
		execl("/bin/sh", "sh", "-c", str, (char *) 0);
		free(str);
		_exit(2);
	}
	id = vfork();
	if (id == 0)
	{
		str = get_lib_from_source();
		execl("/bin/sh", "sh", "-c", str, (char *) 0);
		free(str);
		_exit(2);
	}
	str = get_lib_path();
	f = (void(*)())dlsym(link(str), "_Z4initv");
	f();
}

void *runtimeLibrary::link(char *sourcesLib)
{
	return (dlopen(sourcesLib, RTLD_NOW));
}

void runtimeLibrary::close_lib(void *handle)
{
	dlclose(handle);	
}