#ifndef RENDERBUILTIN_CLASS_HPP
#define RENDERBUILTIN_CLASS_HPP

#define GLFW_INCLUDE_GLEXT

#include <glm.hpp>
#include <staticMemoryManager.class.hpp>
#include <dynamicMemoryManager.class.hpp>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <glfw3.h>
#include <transform.class.hpp>
#include <meshData.hpp>
#include <jobHandler.class.hpp>
#include <gtc/type_ptr.hpp>
#include <jojishi.hpp>
#include "renderDataSys.class.hpp"

#define MAX_SUBSCRIBE 65536

typedef struct 	s_render {
	uint32_t 	assetHandler;
	uint32_t	transformHandler;
	uint32_t	program;
}				t_renderGO;

class renderBuiltIn {

public :

	static 	void 		init();
	static 	void 		shutdown();

	static 	uint32_t 	create();
	static	void 		destroy(uint32_t ref);

	static 	void 		subscribe(uint32_t dataHandler);
	static 	void 		unsubscribe(uint32_t dataHandler);

	static 	void		update();

	static 	t_renderGO 	*get_renderGO(uint32_t ref);

	static	void 		set_camera(uint32_t *camHandlers, uint32_t camNum);

private :

	static uint32_t					cluster_id;
	static std::vector<uint32_t>	list;
	static GLFWwindow*				window;
	static uint32_t					camera[16];
	static uint32_t					cameraNum;
	static void						render(glm::mat4 camera);
	static void						render_node(t_node node, t_renderGO *elem, glm::mat4 camera);
	static void						render_unit(glm::mat4 camera, t_renderMeshData *mesh, t_renderGO *elem);
	static void						render_object(uint32_t index, glm::mat4 camera);
	static uint32_t					program;
	static GLFWvidmode*				mode;
};

#endif