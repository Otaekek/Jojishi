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

#define MAX_ELEM 16

class basicFPSControl {

public:

	 basicFPSControl(std::string meshPath, float posx, float posy, float posz);
	~basicFPSControl();

	void update();

private:

	uint32_t	transformHandler;
	uint32_t	assetHandler;

	void 		render();
	void 		behave();
};

class basicFPSControlManagerBuiltin {

public:

	static void 		init();
	static void 		shutdow();

	static void 		update();
	static void 		create();

private:

	static basicFPSControl		elems[MAX_ELEM];
	static uint32_t				numElem;
};

#endif
