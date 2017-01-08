#include "texture_builtin.class.hpp"

uint32_t	texture_builtin::cluster_id;

uint32_t	texture_builtin::init()
{
	cluster_id = dynamicMemoryManager::init_cluster(4096, sizeof(t_textureInstance));
}

void		texture_builtin::load_texture(void *data)
{
	FREE_IMAGE_FORMAT		format;
	FIBITMAP*				image;
	t_loadHeader 			*loadheader;
	t_texture				*texture;
	char					*textureData;

	loadheader = (t_loadHeader*)data;
	format = FreeImage_GetFileType(loadheader->path, 0);
	image = FreeImage_Load(format, loadheader->path);
	image = FreeImage_ConvertTo32Bits(image);
	staticMemoryManager::alloc_asset(loadheader->ref, sizeof(t_texture));
	texture = (t_texture*)staticMemoryManager::get_data_ptr(loadheader->ref);
	texture->sizex = FreeImage_GetWidth(image);
	texture->sizey = FreeImage_GetHeight(image);
	texture->textureData = staticMemoryManager::create_asset(loadheader->ref, loadheader->cluster, texture->sizex * texture->sizey * 4);
	textureData = (char*)staticMemoryManager::get_data_ptr(texture->textureData);
	memcpy(textureData, FreeImage_GetBits(image), texture->sizex * texture->sizey * 4);
}

uint32_t 	texture_builtin::create_instance(uint32_t ref)
{
	t_textureInstance *texture;
	uint32_t			instanceRef;

	instanceRef = dynamicMemoryManager::create_slot(cluster_id);
	texture = get_texture(instanceRef);
	texture->textureData = ref;
	return (instanceRef);
}

uint32_t 	texture_builtin::destroy_instance(uint32_t ref)
{
	dynamicMemoryManager::clear_slot(ref);
}

t_textureInstance 	*texture_builtin::get_texture(uint32_t textureHandler)
{
	return (t_textureInstance*)dynamicMemoryManager::get_ptr(textureHandler);
}

GLuint	texture_builtin::convert_to_opengl(uint32_t textureInstanceHandler)
{
	GLuint		textureID;
	t_texture	*texture;

	texture = (t_texture*)(staticMemoryManager::get_data_ptr(((t_textureInstance*)(get_texture(textureInstanceHandler)))->textureHandler));
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->sizex, texture->sizey, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, (char*)staticMemoryManager::get_data_ptr(texture->textureData));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (textureID);
}
