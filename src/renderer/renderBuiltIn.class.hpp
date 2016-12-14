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

typedef struct	s_render {
	uint32_t	assetHandler;
	uint32_t	transformHandler;
}				t_renderGO;

typedef struct	s_camera {
	uint32_t	effect;
	uint32_t	transformHandler;
	float		posx;
	float		posy;
	float		sizex;
	float		sizey;
}				t_camera;

class renderBuiltIn {

public :

	static	void					init();
	static	void					shutdown();

	static	uint32_t				create();
	static	void					destroy(uint32_t ref);
	static	t_renderGO				*get_renderGO(uint32_t ref);

	static	uint32_t				create_camera();
	static	void					destroy_camera(uint32_t ref);
	static	t_camera				*get_camera(uint32_t ref);

	static	void					add_camera(uint32_t camHandler);

	static	void					render_me(uint32_t assetHandler);
	static	void					update();

	static GLFWwindow*				get_window();

	static GLFWvidmode				*get_mode();

	static void						modify_skybox(uint32_t handler);
	static t_renderGO				*get_skyboxGO();
	static void						modify_skybox_light(float f);

	static uint32_t					create_light();
	static void						destroy_light(uint32_t ref);
	static void						add_light(uint32_t ref);

private :

	static GLFWvidmode*				mode;
	static GLFWwindow*				window;

	static uint32_t					cluster_id;
	static uint32_t					list[MAX_SUBSCRIBE];
	static uint32_t					sizeList;

	static uint32_t					camCluster_id;
	static uint32_t					_cameras[512];
	static uint32_t					numCamera;

	static float					skybox_light;
	static uint32_t					skyboxGO;

	static uint32_t					lightClusterId;
	static uint32_t					_numLight;
	static uint32_t					_lightsHandlers[4096];

	static void						render(t_camera *camera);
	static void						render_node(t_node node, t_renderGO *elem, uint32_t program);
	static void						render_unit(t_renderMeshData *mesh, t_renderGO *elem, uint32_t program);
	static void						render_object(uint32_t index, t_camera *camera);
	static void						render_skybox(t_camera *camera);
};

#endif