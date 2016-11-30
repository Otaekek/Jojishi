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

void 	renderDataSys::obj_scene_to_memory_as_mesh(stackAllocator *allocator, const aiScene *scene)
{
	t_renderMeshData 			*meshData;
	aiMesh						*mesh;
	float 						*vertices;
	GLuint						*indices;
	uint32_t					indices_size;
	uint32_t					vertex_size;
	void 						*to_free;


	meshData = (t_renderMeshData*)allocator->mem_alloc(sizeof(t_renderMeshData));

	mesh = scene->mMeshes[0];
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
	to_free = allocator->get_offset();
	vertices = (float*)allocator->mem_alloc(vertex_size * sizeof(float) * 8);
	for (uint32_t i = 0; i < vertex_size; i++)
	{
		vertices[i * 8] = mesh->mVertices[i].x;
		vertices[i * 8 + 1] = mesh->mVertices[i].y;
		vertices[i * 8 + 2] = mesh->mVertices[i].z;

		vertices[i * 8 + 3] = mesh->mNormals[i].x;
		vertices[i * 8 + 4] = mesh->mNormals[i].y;
		vertices[i * 8 + 5] = mesh->mNormals[i].z;

		vertices[i * 8 + 6] = mesh->mTextureCoords[0][i].x;
		vertices[i * 8 + 7] = mesh->mTextureCoords[0][i].y;
	}

	meshData->has_texture = true;
	meshData->has_normals = true;
	meshData->vaoId = renderDataSys::createVAO();
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertices, vertex_size, meshData->vaoId);
	meshData->indiceBufferId = renderDataSys::createVBO_Indice(indices, indices_size * 3, meshData->vaoId);
	meshData->indiceNum = indices_size * 3;
	meshData->indices = indices;
	//allocator->mem_free((char*)allocator->get_offset() - (char*)to_free);
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
