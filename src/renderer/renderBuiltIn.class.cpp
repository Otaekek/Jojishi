#include <renderBuiltIn.class.hpp>
#include <unistd.h>

uint32_t 				renderBuiltIn::cluster_id;
std::vector<uint32_t> 	renderBuiltIn::list;
GLFWwindow* 			renderBuiltIn::window;
std::vector<uint32_t>	renderBuiltIn::_cameras(16);
GLFWvidmode* 			renderBuiltIn::mode;

int 			sort(uint32_t a, uint32_t b)
{
	return (0);
}

void 			renderBuiltIn::init()
{
	cluster_id = dynamicMemoryManager::cluster_init(sizeof(t_renderGO), 65536);
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
	//window = glfwCreateWindow(mode->width, mode->height, "jojishiGameEngine", glfwGetPrimaryMonitor(), NULL);
	//window = glfwCreateWindow(1000, 800, "jojishiGameEngine", NULL, NULL);
	//mode->height = 1000;
	//mode->width = 800;
	window = glfwCreateWindow(mode->width, mode->height, "jojishiGameEngine", NULL, NULL);
	glViewport(0, 0, mode->height, mode->width);
	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0.1, 0);
	glfwSwapInterval(1);
	_cameras[0] = transformBuiltin::create();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glEnable(GL_MULTISAMPLE);
	glfwSwapBuffers(window);
	glEnable(GL_BLEND);
}

void 			renderBuiltIn::shutdown()
{
	glfwDestroyWindow(window);
}

uint32_t 		renderBuiltIn::create()
{
	return (dynamicMemoryManager::create_slot(cluster_id));
}

void 			renderBuiltIn::destroy(uint32_t ref)
{
	dynamicMemoryManager::clear_data(ref, cluster_id);
}

void 			renderBuiltIn::subscribe(uint32_t dataHandler)
{
	list.push_back(dataHandler);
}

void 			renderBuiltIn::unsubscribe(uint32_t dataHandler)
{
	list.erase(std::find(list.begin(), list.end(), dataHandler));
}

void			renderBuiltIn::update()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glfwPollEvents();
	std::sort(list.begin(), list.end(), sort);
	renderBuiltIn::render(transformBuiltin::to_mat(_cameras[0]));
	glFinish();
	glfwSwapBuffers(window);
}

t_renderGO 		*renderBuiltIn::get_renderGO(uint32_t ref)
{
	return ((t_renderGO*)dynamicMemoryManager::get_ptr(ref));
}

void 			renderBuiltIn::render_unit(glm::mat4 camera, t_renderMeshData *mesh, t_renderGO *elem, uint32_t program)
{
	GLuint location;

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->vaoId);
	location = glGetUniformLocation(program, "diffuse");
	glUniform3f(location, mesh->material.diffuse[0], mesh->material.diffuse[1], mesh->material.diffuse[2]);
	location = glGetUniformLocation(program, "specular");
	glUniform3f(location, mesh->material.specular[0], mesh->material.specular[1], mesh->material.specular[2]);
	location = glGetUniformLocation(program, "ambiant");
	glUniform3f(location, mesh->material.ambiant[0], mesh->material.ambiant[1], mesh->material.ambiant[2]);
	location = glGetUniformLocation(program, "has_diffuse");
	glUniform1i(location, (int)mesh->material.has_diffuse_texture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indiceBufferId);
	glBindTexture(GL_TEXTURE_2D, mesh->material.diffuseTexture);
	glDrawElements(GL_TRIANGLES, mesh->indiceNum, GL_UNSIGNED_INT, 0);
}

void			renderBuiltIn::render_node(t_node node, t_renderGO *elem, glm::mat4 camera, uint32_t program)
{
	t_renderMeshData	*mesh;
	bool 				mesh_has_child;

	if (node.has_mesh)
	{
		mesh = (t_renderMeshData*)staticMemoryManager::get_data_ptr(node.meshs);
		do
		{
			render_unit(camera, mesh, elem, program);
			mesh_has_child = mesh->has_child;
			mesh = (t_renderMeshData*)staticMemoryManager::get_data_ptr(mesh->child);
		}	while (mesh_has_child);
	}
	for (int i = 0; i < node.childNum; i++)
		render_node(*(t_node*)(staticMemoryManager::get_data_ptr(node.child[i])), elem, camera, program);
}

void 			renderBuiltIn::render_object(uint32_t index, glm::mat4 camera)
{
	t_renderMeshData	*mesh;
	t_node				*node;
	bool 				mesh_has_child;
	bool 				node_has_child;
	t_renderGO 			*elem;

	elem = (t_renderGO*)renderBuiltIn::get_renderGO(list[index]);
	node = (t_node*)staticMemoryManager::get_data_ptr(elem->assetHandler);

	glUseProgram(node->program);

	/*Set projection Matrix*/
	glm::mat4 proj = glm::perspective(45.0f, (float)mode->width / mode->height, 1.0f, 100.0f);
	GLint uniProj = glGetUniformLocation(node->program, "P");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	/*Set camera */
	GLint cam = glGetUniformLocation(node->program, "V");
	glUniformMatrix4fv(cam, 1, GL_FALSE, glm::value_ptr(camera));

	/* Set model */
	GLint model = glGetUniformLocation(node->program, "M");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(transformBuiltin::to_mat(elem->transformHandler)));

	render_node(*node, elem, camera, node->program);
}

void			renderBuiltIn::render(glm::mat4 camera)
{
	for (uint32_t i = 0; i < list.size(); i++)
		renderBuiltIn::render_object(i, camera);
}

void			renderBuiltIn::add_camera(uint32_t camHandler)
{
	_cameras.push_back(camHandler);
}

void			renderBuiltIn::remove_camera(uint32_t camHandler)
{
	_cameras.erase(std::find(_cameras.begin(), _cameras.end(), camHandler));
}

