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

GLuint					renderBuiltIn::_idsTextureid;
GLuint					renderBuiltIn::_colorTextureid;
GLuint					renderBuiltIn::_frameBufferid;
GLuint					renderBuiltIn::_quadVertexbuffer;

static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
};

int				sort(uint32_t a, uint32_t b)
{
	return (0);
}

/*
bool initBuffers = false;
GLuint *pbo;
int writeIndex = 1, readIndex = 0;
void *data;
float *myBuffer;

#define E printf("%d\n", glGetError());
void FastCaptureBackBuffer(int width, int height)
{
	//Create PBOs:
	E
	E

	GLuint tex;
	if (!initBuffers)
	{
		myBuffer = (float*)malloc(width * height * 4);
		pbo = (uint*)malloc(100);
		initBuffers = true;
E
		 glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		
		glGenBuffers(2, pbo);
		GLuint mdr;
		glGenFramebuffers(1, &mdr);
				glBindFramebuffer(GL_FRAMEBUFFER, mdr);

		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[0]);
		glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 4.0f, 0, GL_STREAM_READ);
E
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 0, 0);
E
	GLenum ouais[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, ouais);
E
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[1]);

		glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 4.0f, 0, GL_STREAM_READ);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, tex, 0);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, tex, 0);
	glDrawBuffers(2, ouais);

	}
	//swap read and write.
	writeIndex = (writeIndex + 1) % 2;
	readIndex = (writeIndex + 1) % 2;

	//read back-buffer.
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[readIndex]);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[writeIndex]);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	void* data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

	//if (data)
	{
		memcpy(myBuffer, data, width * height * 4);
		printf("mdr\n");
		//data = nullptr;
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
	}

	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	for (int i = 0; i < 10000; i++)
	{
		printf("%d %d %d\n", ((int*)myBuffer)[i] & 0X0000FF, (((int*)myBuffer)[i] & 0X00FF00) >> 8, (((int*)myBuffer)[i] & 0xFF0000) >> 16);
	}
	//exit(0);
	printf("\n");
}
*/
void			renderBuiltIn::create_onScreenRendering_data()
{

	GLuint quad_VertexArrayID;
	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
	_quadVertexbuffer = quad_VertexArrayID;
}

void			renderBuiltIn::create_framebuffer()
{
	GLuint	frameBufferid;
	GLuint	colorTexture;
	GLuint	idsTexture;

	glGenFramebuffers(1, &frameBufferid);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferid);

	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mode->width, mode->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	glGenTextures(1, &idsTexture);
	glBindTexture(GL_TEXTURE_2D, idsTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mode->width, mode->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, idsTexture, 0);
	_frameBufferid = frameBufferid;
	_colorTextureid = colorTexture;
	_idsTextureid = idsTexture;
	GLenum attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	create_onScreenRendering_data();
}

void			renderBuiltIn::read_ids_from_frame_buffer()
{

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
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 0);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_MULTISAMPLE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwSwapBuffers(window);
	glEnable(GL_BLEND);
	skyboxGO = renderBuiltIn::create();
	skybox = get_renderGO(skyboxGO);
	skybox->transformHandler = transformBuiltin::create();
	transformBuiltin::scale(skybox->transformHandler, 10000000000, 10000000000, 10000000000);
	glFrontFace(GL_CCW);
	create_framebuffer();
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

	renderDataSys::execute_texture_request();
	renderDataSys::execute_vao_request();
	glfwGetWindowSize(window, &(mode->width), &(mode->height));
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glfwPollEvents();
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferid);
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
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	numCamera = 0;
	sizeList = 0;
	_numLight = 0;
	glFinish();
	renderOnScreen();
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
	uint32_t ref = (dynamicMemoryManager::create_slot(camCluster_id));
	dynamicMemoryManager::zerofy(ref, sizeof(t_camera));
	return (ref);
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
