#ifndef GENERICPARSER_CLASS_HPP
#define GENERICPARSER_CLASS_HPP


#include "../mesh_renderer/meshData.hpp"
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/Importer.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../../assimp/include/assimp/postprocess.h"

class genericParser {

public:
	
	void load_file(void *data);

private:

	char *read_file(char *path);
	t_meshData *convert_to_mesh(stackAllocator *allocator, aiScene *scene);

};

#endif
