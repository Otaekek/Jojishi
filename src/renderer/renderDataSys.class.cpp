#include "renderDataSys.class.hpp"

renderDataSys::renderDataSys()
{

}

renderDataSys::~renderDataSys()
{

}

uint32_t renderDataSys::createVAO()
{
	GLuint vaoid;

	glGenVertexArrays(1, &(vaoid));
	return (vaoid);
}

uint32_t renderDataSys::createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId)
{
	GLuint 	vertexBufferID;
	GLuint	normalBufferID;
	GLuint	textCoordBufferID;

	glBindVertexArray(vaoId);

	glGenBuffers(1, &(vertexBufferID));
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBufferData(GL_ARRAY_BUFFER,  vertex_size * sizeof(float) * 8, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*6));
	return vertexBufferID;
}

uint32_t renderDataSys::createVBO_Indice(uint32_t *indices, uint32_t indice_size, uint32_t vaoId)
{
	GLuint indiceBufferId;
	glBindVertexArray(vaoId);

	glGenBuffers(1, &(indiceBufferId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferId);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  indice_size * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	return indiceBufferId;
}

void 		renderDataSys::copy_vertices(stackAllocator *allocator, aiMesh *mesh, t_renderMeshData *meshData, const aiScene *scene)
{
	float 						*vertices;
	GLuint						*indices;
	aiMaterial					*material;
	uint32_t					indices_size;
	uint32_t					vertex_size;
	aiColor4D 					color;
	aiString					texturePath;
	FREE_IMAGE_FORMAT			format;
	FIBITMAP*					image;
	GLuint 						textureID;

	material = scene->mMaterials[mesh->mMaterialIndex];
	indices_size = mesh->mNumFaces;
	vertex_size = mesh->mNumVertices;
	indices = (GLuint*)allocator->mem_alloc(indices_size * 3 * sizeof(uint32_t));
	for (uint32_t i = 0; i < indices_size; i++)
	{
		for (uint32_t j = 0; j < 3; j++)
		{
			GLuint indice = mesh->mFaces[i].mIndices[j];
			indices[i * 3 + j] = indice;
		}
	}
	vertices = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 8);
	for (uint32_t i = 0; i < vertex_size; i++)
	{
		vertices[i * 8] = mesh->mVertices[i].x;
		vertices[i * 8 + 1] = mesh->mVertices[i].y;
		vertices[i * 8 + 2] = mesh->mVertices[i].z;
		vertices[i * 8 + 3] = mesh->mNormals[i].x;
		vertices[i * 8 + 4] = mesh->mNormals[i].y;
		vertices[i * 8 + 5] = mesh->mNormals[i].z;
		if (mesh->GetNumUVChannels() > 0) {
			vertices[i * 8 + 6] = mesh->mTextureCoords[0][i].x;
			vertices[i * 8 + 7] = mesh->mTextureCoords[0][i].y;
		}
	}

	aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
	meshData->material.diffuse[0] = color.r;
	meshData->material.diffuse[1] = color.g;
	meshData->material.diffuse[2] = color.b;
	aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
	meshData->material.specular[0] = color.r;
	meshData->material.specular[1] = color.g;
	meshData->material.specular[2] = color.b;
	aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
	meshData->material.ambiant[0] = color.r;
	meshData->material.ambiant[1] = color.g;
	meshData->material.ambiant[2] = color.b;

	if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
		material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
		format = FreeImage_GetFileType(texturePath.C_Str(), 0);
		image = FreeImage_Load(format, texturePath.C_Str());
		if (image != NULL)
		{
			meshData->material.has_diffuse_texture = true;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(image), FreeImage_GetHeight(image), 0,
				GL_BGR, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(image));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			meshData->material.diffuseTexture = textureID;
		}
	}
	if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
	{
		material->GetTexture(aiTextureType_SPECULAR, 0, &texturePath);
		if (meshData->material.specularTexture  != 0)
		{
			meshData->material.has_specular_texture = true;
			glBindTexture(GL_TEXTURE_2D, meshData->material.specularTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	meshData->vaoId = renderDataSys::createVAO();
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertices, vertex_size, meshData->vaoId);
	meshData->indiceBufferId = renderDataSys::createVBO_Indice(indices, indices_size * 3, meshData->vaoId);
	meshData->indiceNum = indices_size * 3;
	meshData->indices = indices;
}

uint32_t 	renderDataSys::node_to_mesh(stackAllocator *allocator, const aiNode *node, glm::mat4 trans, const aiScene *scene)
{
	t_node 				*nodeData;
	t_renderMeshData	*mesh;
	uint32_t			k;

	nodeData = (t_node*)allocator->mem_alloc(sizeof(t_node));
	nodeData->meshs = staticMemoryManager::create_slot_child(staticMemoryManager::E_OBJ_FILE);
	for (int indexMesh = 0; indexMesh < node->mNumMeshes; indexMesh++)
	{
		nodeData->has_mesh = true;
		mesh = (t_renderMeshData*)allocator->mem_alloc(sizeof(t_renderMeshData));
		copy_vertices(allocator, scene->mMeshes[node->mMeshes[indexMesh]], mesh, scene);
		mesh->has_child = true;
		mesh->child = staticMemoryManager::create_slot_child(staticMemoryManager::E_OBJ_FILE);
	}
	if (node->mNumMeshes)
	{
		mesh->has_child = false;
		nodeData->has_mesh = true;
	}
	else
		nodeData->has_mesh = false;
	for (k = 0; k < node->mNumChildren; k++)
	{
		nodeData->child[k] = staticMemoryManager::create_slot_child(staticMemoryManager::E_OBJ_FILE);
		node_to_mesh(allocator, node->mChildren[k], trans, scene);
	}
	nodeData->childNum = k;
}

void	renderDataSys::obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene)
{
	glm::mat4 n;

	node_to_mesh(allocator, scene->mRootNode, n, scene);
}


std::string 		readfile(std::string path)
{
	std::string line;
	std::string file;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )
			file += line + '\n';
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
		exit(0);
	}
	return file;
}

uint32_t renderDataSys::load_programVertexFrag(std::string vertexPath, std::string fragPath)
{
	GLchar			*vertexCode;
	GLchar			*fragCode;
	GLuint			vertexShaderObject;
	GLuint			fragmentShaderObject;
	GLint			flength, vlength;
	GLint			compiled;
	char			log[4096];
	GLint			slen, blen;
	std::string 	file;


	vertexCode = (GLchar*)malloc(4096);
	fragCode = (GLchar*)malloc(4096);
	file = readfile(vertexPath);
	memcpy(vertexCode, file.c_str(), file.length() + 1);
	file = readfile(fragPath);
	memcpy(fragCode, file.c_str(), file.length() + 1);
	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	vlength = strlen(vertexCode);
	flength = strlen(fragCode);
	glShaderSource(vertexShaderObject, 1, (const GLchar **)&(vertexCode), &vlength);
	glCompileShader(vertexShaderObject);
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH , &blen);
		printf("%d\n", compiled);
		glGetShaderInfoLog(vertexShaderObject, blen, &slen, log);
		printf("VertexShader compilation: %s\n", log);
		exit(0);
	}
	glShaderSource(fragmentShaderObject, 1, (const GLchar **)&(fragCode), &flength);
	glCompileShader(fragmentShaderObject);
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH , &blen);
		glGetShaderInfoLog(fragmentShaderObject, blen, &slen, log);
		printf("Frag shder compilation: %s\n", log);
		exit(0);
	}
	GLint ProgramObject = glCreateProgram();
	glAttachShader(ProgramObject, vertexShaderObject);
	glAttachShader(ProgramObject, fragmentShaderObject);
	glLinkProgram(ProgramObject);
	free(vertexCode);
	free(fragCode);
	return (ProgramObject);
}


/*

*/