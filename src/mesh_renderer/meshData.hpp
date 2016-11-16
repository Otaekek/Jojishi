#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <cstdint>

typedef struct 	s_meshData {

	float 		*vertex;
	float 		*uv;
	float 		*normal;

	uint32_t	*indice;

	uint32_t	vertex_size;
	uint32_t	indices_size;

}				t_meshData;

#endif