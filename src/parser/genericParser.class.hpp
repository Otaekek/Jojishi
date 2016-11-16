#ifndef GENERICPARSER_CLASS_HPP
#define GENERICPARSER_CLASS_HPP


#include "../mesh_renderer/meshData.hpp"
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/Importer.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../../assimp/include/assimp/postprocess.h"
#include "../../assimp/include/assimp/scene.h"

#include "../job_system/jobSystem.hpp"
#include "../asset_database_system/assetSystemWorker.class.hpp"
#include <map>
#include <string>


class genericParser {

public:
	
	genericParser();
	~genericParser();

	void load_file(void *data);



private:
	
	void 	parse_path_and_handle_scene(std::string path);
	void 	obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene);

	std::map<std::string, void (genericParser::*)(stackAllocator *, const aiScene *)> extension_to_function;
};

#endif
