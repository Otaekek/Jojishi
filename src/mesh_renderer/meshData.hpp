#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <cstdint>

typedef struct 	s_meshData {

	float 		*vertex;
	float 		*uv;
	float 		*normales;

	uint32_t	*indices;

	uint64_t	*material_handlers;

	uint32_t	vertex_size;
	uint32_t	uv_size;
	uint32_t	normales_size;
	uint32_t	indices_size;
	uint32_t	material_handlers_size;

}				t_meshData;

#endif