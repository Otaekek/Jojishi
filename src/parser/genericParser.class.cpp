#include "genericParser.class.hpp"

void 	genericParser::load_file(void *data)
{
	data = (void*)data;
}

char 	*genericParser::read_file(char *path)
{
	path = NULL;
	return path;
}

t_meshData 	*genericParser::convert_to_mesh(stackAllocator *allocator, aiScene *scene)
{
	t_meshData *ku;

	ku = (t_meshData*)allocator;
	ku = (t_meshData*)scene;
	return ku;
}
