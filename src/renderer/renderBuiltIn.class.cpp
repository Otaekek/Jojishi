#include <renderBuiltIn.class.hpp>
#include <unistd.h>
#include "/usr/include/GL/gl.h"
#include "/usr/include/GL/glext.h"

uint32_t 				renderBuiltIn::cluster_id;
std::vector<uint32_t> 	renderBuiltIn::list;
GLFWwindow* 			renderBuiltIn::window;
uint32_t				renderBuiltIn::camera[16];
uint32_t				renderBuiltIn::cameraNum;
uint32_t				renderBuiltIn::program;
const GLFWvidmode* 		renderBuiltIn::mode;

int 			sort(uint32_t a, uint32_t b)
{
	return (0);
}

void 			renderBuiltIn::init()
{
	cluster_id = dynamicMemoryManager::cluster_init(sizeof(t_renderGO), 65536);
	glfwInit();
	mode = glfwGetVideoMode(glfwGetPrimaryMonitor());	
	window = glfwCreateWindow(mode->width, mode->height, "jojishiGameEngine", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);
	glClearColor(0, 1, 0, 0);
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
	glm::mat4 proj = glm::perspective(45.0f, (float)mode->width/ (float)mode->height, 1.0f, 100.0f);
	GLint uniProj = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
	std::sort(list.begin(), list.end(), sort);
	//renderBuiltIn::render(transformBuiltin::to_mat(camera[0]));
	glFinish();
	glfwSwapBuffers(window);
}

t_renderGO 		*renderBuiltIn::get_renderGO(uint32_t ref)
{
	return ((t_renderGO*)dynamicMemoryManager::get_ptr(ref));
}

void 			renderBuiltIn::render_unit(uint32_t index)
{
	t_renderMeshData 	*mesh;
	t_renderGO 			*elem;

	elem = (t_renderGO*)dynamicMemoryManager::get_ptr(list[index]);
	mesh = (t_renderMeshData*)staticMemoryManager::get_data_ptr(elem->assetHandler);
	GLint model = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(transformBuiltin::to_mat(elem->transformHandler)));
	glBindVertexArray(mesh->vaoId);
	glDrawElements(GL_TRIANGLES, mesh->indiceNum, GL_UNSIGNED_INT, mesh->indices);
}

void			renderBuiltIn::render(glm::mat4 camera)
{
	GLint cam = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(cam, 1, GL_FALSE, glm::value_ptr(camera));
	for (uint32_t i = 0; i < list.size(); i++)
		renderBuiltIn::render_unit(i);
}
