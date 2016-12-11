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
}				t_renderGO;

class renderBuiltIn {

public :

	static 	void 		init();
	static 	void 		shutdown();

	static 	uint32_t 	create();
	static	void 		destroy(uint32_t ref);

	static	void		render_me(uint32_t assetHandler);
	static 	void		update();

	static 	t_renderGO 	*get_renderGO(uint32_t ref);

	static	void		add_camera(uint32_t camHandler);

	static GLFWwindow*				get_window();

	static GLFWvidmode				*get_mode();
	
private :

	static uint32_t					cluster_id;
	static uint32_t					list[MAX_SUBSCRIBE];
	static uint32_t					sizeList;
	static GLFWwindow*				window;
	static uint32_t					_cameras[512];
	static uint32_t					numCamera;
	static void						render(glm::mat4 camera);
	static void						render_node(t_node node, t_renderGO *elem, glm::mat4 camera, uint32_t program);
	static void						render_unit(glm::mat4 camera, t_renderMeshData *mesh, t_renderGO *elem, uint32_t program);
	static void						render_object(uint32_t index, glm::mat4 camera);
	static GLFWvidmode*				mode;
};

#endif