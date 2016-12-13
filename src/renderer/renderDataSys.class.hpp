#ifndef RENDERDATASYS_CLASS_HPP
#define RENDERDATASYS_CLASS_HPP

#include <cstdint>
#include <transform.class.hpp>
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../file_loader/fileLoader.class.hpp"
#include "meshData.hpp"
#include <FreeImage.h>
#include <glm.hpp>
#include <cstdlib>
#include <jojishi.hpp>
#include <string>

enum E_SHADER {
	E_DEFAULT,
	E_SKYBOX
};

typedef struct s_light {

};

typedef struct		s_material {

	bool			has_diffuse_texture;
	bool			has_specular_texture;
	bool			has_bump_texture;
	bool			is_twosided;

	float			diffuse[3];
	float			ambiant[3];
	float			specular[3];

	uint32_t		bumpTexture;
	uint32_t		diffuseTexture;
	uint32_t		specularTexture;

}					t_material;

typedef struct		s_mesh {

	bool			has_child;

	GLuint			textureHandler;
	GLuint			vaoId;
	GLuint			vertexNum;
	GLuint			vboVerticeId;
	GLuint			indiceNum;
	GLuint			indiceBufferId;
	GLuint			*indices;
	GLuint			diffuseText;
	GLuint			specularTexts;

	GLuint			child;

	float 			*vbo;
	glm::mat4		initialTransform;

	t_material		material;

}					t_renderMeshData;

typedef	struct		s_node {

	uint32_t		program;
	bool			has_mesh;
	uint32_t		meshs;
	uint32_t 		child[12];
	uint32_t		childNum;

}					t_node;

class renderDataSys {

public:

	renderDataSys();

	~renderDataSys();

	static void 			init();
	static void 			shutdown();

	static uint32_t 		createVAO();
	static uint32_t 		createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId);
	static uint32_t 		createVBO_Indice(uint32_t *indices, uint32_t indice_size, uint32_t vaoId);
	static void 			obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene, char *path);
	static uint32_t 		load_programVertexFrag(std::string vertexPath, std::string fragPath);
	static void				computeModification(t_renderMeshData *mesh, glm::vec3 translation, float angle, glm::vec3 axis);
	static void				iterNode(t_node node, glm::vec3 translation, float angle, glm::vec3 axis);
	static void				modifyVertices(uint32_t assetHandler, glm::vec3 translation, float angle, glm::vec3 axis);
	static void				set_programm(E_SHADER shader, uint32_t asset);

private:
	static void 			copy_vertices(stackAllocator *allocator, aiMesh *mesh, t_renderMeshData *meshData, const aiScene *scene, char *path);
	static uint32_t 		node_to_mesh(stackAllocator *allocator, const aiNode *node,  glm::mat4 trans,const aiScene *scene, char *path);
	static void				handle_texture(aiTextureType type, char *path, aiMaterial *material, uint32_t *textEmplacement, bool *has_text);
	static uint32_t			_programm[16];
};

#endif