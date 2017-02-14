#include "runtimeLibrary.class.hpp"

int runtimeLibrary::count = 0;

void runtimeLibrary::init()
{

}

void runtimeLibrary::shutdown()
{

}

/*
void runtimeLibrary::create_lib_from_dir(char *sourcesDir)
{

}


void runtimeLibrary::compile_dir(char *sourcesDir)
{
	count++;
}
*/

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

char *runtimeLibrary::get_string_from_source(char *sourcepath)
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
	memcpy(str, "g++ -dynamiclib -o dylib", 24);
	utoa(count, tmp);
	memcpy(str + 24, tmp, len);
	memcpy(str + 24 + len, ".so \0", 5);
	strcat(output, "dylib");
	strcat(output, tmp);
	strcat(output, ".so");
	strcat(str, "dylib");
	strcat(str, tmp);
	strcat(str, ".cpp");
	return (str);
}

void runtimeLibrary::create_lib(char *sourcesPath)
{
	compile(sourcesPath);
}

void runtimeLibrary::compile(char *sourcePath)
{
	char *str;

	count++;
	str = get_string_from_source(sourcePath);
	system(str);
	//link(ouais);
}

void *runtimeLibrary::link(char *sourcesLib)
{
	return (dlopen(sourcesLib, RTLD_NOW));
}

void runtimeLibrary::close_lib(void *handle)
{
	dlclose(handle);	
}