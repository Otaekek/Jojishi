#ifndef RENDERDATASYS_CLASS_HPP
#define RENDERDATASYS_CLASS_HPP

#include <cstdint>
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "meshData.hpp"

class renderDataSys {

public:

	renderDataSys();

	~renderDataSys();

	static uint32_t createVAO();
	static uint32_t createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId);
	static uint32_t createVBO_Indice(uint32_t *indices, uint32_t indice_size, uint32_t vaoId);
	static void obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene);

private:

};

#endif