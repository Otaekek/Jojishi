#ifndef TERRAINGENERATIONBUILTIN_CLASS_HPP
#define TERRAINGENERATIONBUILTIN_CLASS_HPP

#include <staticMemoryManager.class.hpp>
#include <renderDataSys.class.hpp>

#define FRAGMENT_SIZE 10000

typedef struct	s_biom {

	float				sizex;
	float				sizey;
	float				posx;
	float				posy;
	uint32_t			dataRef;
	uint32_t			transformHandler;
	uint32_t			renderGoHandler[4096];
}						t_biom;

class terrainGenerationBuiltin {


public:

	static void 		init();

	static void 		update();

	static void			add_biom(float posx, float posy, float sizex, float sizey);

private:

	static t_biom		bioms[4096];
	static uint32_t		numBiom;

};

#endif