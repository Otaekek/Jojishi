#ifndef RENDERDATASYS_CLASS_HPP
#define RENDERDATASYS_CLASS_HPP

#include <cstdint>
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../file_loader/fileLoader.class.hpp"
#include "meshData.hpp"
#include <jojishi.hpp>
#include <string>

typedef struct 	s_renderMeshData {

	bool 		has_normals;
	bool 		has_texture;

	GLuint		textureHandler;
	GLuint		vaoId;
	GLuint		vboVerticeId;
	GLuint		indiceNum;
	GLuint		*indices;
}				t_renderMeshData;

class renderDataSys {

public:

	renderDataSys();

	~renderDataSys();

	static uint32_t createVAO();
	static uint32_t createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId);
	static uint32_t createVBO_Indice(uint32_t *indices, uint32_t indice_size, uint32_t vaoId);
	static void 	obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene);
	static uint32_t 		load_programVertexFrag(std::string vertexPath, std::string fragPath);

private:

};

#endif