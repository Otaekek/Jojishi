#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

#include <xmmintrin.h>
#include "../dynamic_memory_manager/dynamicMemoryManager.class.hpp"

typedef struct 	s_matrix {
	float		data[16];
}				t_matrix;

class matrixFactory {

public:
	static uint32_t		create();
	static uint32_t		create_iso();
	static void			scale(uint32_t matrix, float x, float y, float z);
	static void			translate(uint32_t matrix, float x, float y, float z);
	static void 		rotate(uint32_t matrix, float x, float y, float z);

	static void 		init();
	static void 		shutdown();

private:
	static uint32_t 	cluster_id;
	static void 		multiply(float *a, float *b);
};

#endif
