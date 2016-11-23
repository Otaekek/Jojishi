#ifndef RENDERBUILTIN_CLASS_HPP
#define RENDERBUILTIN_CLASS_HPP

class renderBuiltIn {

public :

	typedef struct 	s_render {
		uint32_t 	assetHandler;
		uint32_t	modelMatrix;		
	}				t_renderGO;

	static void init();
	static void shutdown();
	static void subscribe(uint32_t dataHandler);
	static void unsubscribe(uint32_t dataHandler);

private :

};

#endif