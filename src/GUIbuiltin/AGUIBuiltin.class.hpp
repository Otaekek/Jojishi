#ifndef AGUIBUILTIN_CLASS_HPP
#define AGUIBUILTIN_CLASS_HPP

class AGUIBuiltin {

public:

protected:

	float		posx;
	float		posy;

	float		sizex;
	float		sizey;

	uint32_t	childnum;

	AGUIBuiltin	child[16];
};

#endif