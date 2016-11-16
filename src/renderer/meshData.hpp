#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <cstdint>

typedef struct 	s_renderMeshData {
	uint32_t	vaoId;
	uint32_t	vboVerticeId;
	uint32_t	vboIndiceId;
	uint32_t	indiceNum;
}				t_renderMeshData;

#endif