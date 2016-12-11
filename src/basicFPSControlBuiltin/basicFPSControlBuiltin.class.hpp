#ifndef BASICFPSCONTROLBUILTIN_CLASS_HPP
#define BASICFPSCONTROLBUILTIN_CLASS_HPP

/*
	This factory was created mainly for debug and testing
	As it has no physics components movement are based directly on the transform
	and this is NOT recommended in a real game.
*/

/*
	Note:
		The way the Gameobject are conceived ( if they are ) are left to the game programmer
		but it is recommanded to architect them this way.
*/

#include <transform.class.hpp>
#include <string>
#include <renderBuiltIn.class.hpp>
#include <fileLoader.class.hpp>
#include <inputBuiltin.class.hpp>

#define MAX_ELEM 64

class basicFPSControl {

public:

	basicFPSControl();
	basicFPSControl(float posx, float posy, float posz);
	~basicFPSControl();

	void update();

private:

	uint32_t	_transformHandler;

	void 		render();
	void 		behave();
	float		rotx;
	float		roty;
};

class basicFPSControlManagerBuiltin {

public:

	static void 		init();
	static void 		shutdow();

	static void 		update();
	static void 		create(float posx, float posy, float posz);

private:

	static basicFPSControl		elems[MAX_ELEM];
	static uint32_t				numElem;
};

#endif
