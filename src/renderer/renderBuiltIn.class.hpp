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

	static	void		init();
	static	void		shutdown();

	static	uint32_t	create();
	static	void		destroy(uint32_t ref);
	static	t_renderGO	*get_renderGO(uint32_t ref);

	static	uint32_t	create_camera();
	static	void		destroy_camera(uint32_t ref);
	static	t_camera	*get_camera(uint32_t ref);

	static	void		add_camera(uint32_t camHandler);
	static	void 		remove_camera(uint32_t camHandler);

	static	void		render_me(uint32_t assetHandler);
	static	void		update();



	static GLFWwindow*				get_window();

	static GLFWvidmode				*get_mode();

private :

	static uint32_t					cluster_id;
	static uint32_t					camCluster_id;
	static uint32_t					list[MAX_SUBSCRIBE];
	static uint32_t					sizeList;
	static GLFWwindow*				window;
	static std::vector<uint32_t> 	cameraList;
	static uint32_t					_cameras[512];
	static uint32_t					numCamera;
	static void						render(t_camera *camera);
	static void						render_node(t_node node, t_renderGO *elem, uint32_t program);
	static void						render_unit(t_renderMeshData *mesh, t_renderGO *elem, uint32_t program);
	static void						render_object(uint32_t index, t_camera *camera);
	static GLFWvidmode*				mode;
};

#endif