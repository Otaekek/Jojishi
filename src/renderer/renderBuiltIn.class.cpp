#include <renderBuiltIn.class.hpp>
#include <unistd.h>

GLFWvidmode* 			renderBuiltIn::mode;
GLFWwindow* 			renderBuiltIn::window;

uint32_t 				renderBuiltIn::cluster_id;
uint32_t				renderBuiltIn::list[MAX_SUBSCRIBE];
uint32_t				renderBuiltIn::sizeList;

uint32_t				renderBuiltIn::camCluster_id;
uint32_t				renderBuiltIn::_cameras[512];
uint32_t				renderBuiltIn::numCamera = 0;

uint32_t				renderBuiltIn::skyboxGO;
float					renderBuiltIn::skybox_light = 1;

uint32_t				renderBuiltIn::lightClusterId;
uint32_t				renderBuiltIn::_numLight = 0;
uint32_t				renderBuiltIn::_lightsHandlers[4096];

int				sort(uint32_t a, uint32_t b)
{
	return (0);
}

void 			renderBuiltIn::init()
{
	t_renderGO *skybox;
	cluster_id = dynamicMemoryManager::cluster_init(sizeof(t_renderGO), 65536);
	camCluster_id = dynamicMemoryManager::cluster_init(sizeof(t_camera), 4096);
	lightClusterId = dynamicMemoryManager::cluster_init(sizeof(t_light), 65536);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	mode = (GLFWvidmode*)glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	window = glfwCreateWindow(mode->width, mode->height, "jojishiGameEngine", glfwGetPrimaryMonitor(), NULL);
	//window = glfwCreateWindow(1000, 800, "jojishiGameEngine", NULL, NULL);
	//mode->height = 800;
	//mode->width = 1000;
	//window = glfwCreateWindow(mode->width, mode->height, "jojishiGameEngine", NULL, NULL);
	glfwMakeContextCurrent(window);
	glClearColor(0.1, 0, 0, 0);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glEnable(GL_MULTISAMPLE);
	glfwSwapBuffers(window);
	glEnable(GL_BLEND);
	skyboxGO = renderBuiltIn::create();
	skybox = get_renderGO(skyboxGO);
	skybox->transformHandler = transformBuiltin::create();
	transformBuiltin::scale(skybox->transformHandler, 2000, 2000, 2000);
	glFrontFace(GL_CCW);
}

void			renderBuiltIn::face_culling(t_renderGO *go)
{
	if (go->cullOnMe)
		glEnable(GL_CULL_FACE);
	glCullFace(go->cullMode);
}

void			renderBuiltIn::shutdown()
{
	glfwDestroyWindow(window);
}

uint32_t		renderBuiltIn::create()
{
	uint32_t h = (dynamicMemoryManager::create_slot(cluster_id));
	dynamicMemoryManager::zerofy(h, sizeof(t_renderGO));
	return (h);
}

void			renderBuiltIn::update()
{
	t_camera			*camera;

	glfwGetWindowSize(window, &(mode->width), &(mode->height));
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glfwPollEvents();
	for (uint32_t i = 0; i < numCamera; i++)
	{
		camera = renderBuiltIn::get_camera(_cameras[i]);
		glViewport(camera->posx * mode->width, camera->posy * mode->height, camera->sizex * mode->width, camera->sizey * mode->height);
		render_skybox(camera);
	}
	for (uint32_t i = 0; i < numCamera; i++)
	{
		camera = renderBuiltIn::get_camera(_cameras[i]);
		glViewport(camera->posx * mode->width, camera->posy * mode->height, camera->sizex * mode->width, camera->sizey * mode->height);
		renderBuiltIn::render(camera);
	}
	numCamera = 0;
	sizeList = 0;
	_numLight = 0;
	glFinish();
	glfwSwapBuffers(window);
}

GLFWvidmode				*renderBuiltIn::get_mode()
{
	return (mode);
}

t_renderGO 		*renderBuiltIn::get_renderGO(uint32_t ref)
{
	return ((t_renderGO*)dynamicMemoryManager::get_ptr(ref));
}

void			renderBuiltIn::render(t_camera *camera)
{
	for (uint32_t i = 0; i < sizeList; i++)
	{
		renderBuiltIn::render_object(list[i], camera);
		glDisable(GL_CULL_FACE);
	}
}

void					renderBuiltIn::add_camera(uint32_t camHandler)
{
	_cameras[numCamera++] = camHandler;
}

void					renderBuiltIn::render_me(uint32_t assetHandler)
{
	list[sizeList++] = assetHandler;
}

GLFWwindow*				renderBuiltIn::get_window()
{
	return (window);
}

uint32_t	renderBuiltIn::create_camera()
{
	return (dynamicMemoryManager::create_slot(camCluster_id));
}

void		renderBuiltIn::destroy_camera(uint32_t ref)
{
	dynamicMemoryManager::clear_data(ref, camCluster_id);
}

t_camera	*renderBuiltIn::get_camera(uint32_t ref)
{
	return ((t_camera*)dynamicMemoryManager::get_ptr(ref));
}

void		renderBuiltIn::modify_skybox(uint32_t handler)
{
	t_renderGO *skybox;

	skybox = get_renderGO(skyboxGO);
	skybox->assetHandler = handler;
}

void		renderBuiltIn::render_skybox(t_camera *camera)
{
	t_renderGO 		*skybox;
	t_transform 	*camTransform;
	t_transform 	*skyboxTransform;
	t_node 			*node;

	glDisable(GL_DEPTH_TEST);
	camTransform = transformBuiltin::get_transform(camera->transformHandler);
	skybox = renderBuiltIn::get_renderGO(skyboxGO);
	skyboxTransform = transformBuiltin::get_transform(skybox->transformHandler);
	skyboxTransform->position.x = -camTransform->position.x;
	skyboxTransform->position.y = -camTransform->position.y;
	skyboxTransform->position.z = -camTransform->position.z;
	node = (t_node*)staticMemoryManager::get_data_ptr(skybox->assetHandler);
	glUseProgram(node->program);
	GLuint location = glGetUniformLocation(node->program, "sunlight");
	glUniform1f(location, skybox_light);
	render_object(skyboxGO, camera);
	glEnable(GL_DEPTH_TEST);
}

t_renderGO					*renderBuiltIn::get_skyboxGO()
{
	return (get_renderGO(skyboxGO));
}

void						renderBuiltIn::modify_skybox_light(float f)
{
	skybox_light = f;
}

uint32_t					renderBuiltIn::create_light()
{
	return (dynamicMemoryManager::create_slot(lightClusterId));
}

void						renderBuiltIn::destroy_light(uint32_t ref)
{
	dynamicMemoryManager::clear_data(ref, lightClusterId);
}

void						renderBuiltIn::add_light(uint32_t ref)
{
	_lightsHandlers[_numLight++] = ref;
}

t_light						*renderBuiltIn::get_light(uint32_t ref)
{
	return ((t_light*)dynamicMemoryManager::get_ptr(ref));
}
