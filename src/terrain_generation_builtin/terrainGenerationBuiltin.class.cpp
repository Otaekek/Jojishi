#include "terrainGenerationBuiltin.class.hpp"
#include <ctime>
t_biom		terrainGenerationBuiltin::bioms[4096] = {0};
uint32_t	terrainGenerationBuiltin::numBiom = 0;

float Get2DPerlinNoiseValue(float x, float y, float res)
{
    float tempX,tempY;
    int x0,y0,ii,jj,gi0,gi1,gi2,gi3;
    float unit = 1.0f/sqrt(2);
    float tmp,s,t,u,v,Cx,Cy,Li1,Li2;
    float gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};
    unsigned int perm[] =
       {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
        142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
        203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
        74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
        105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
        187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
        64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
        47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
        153,101,155,167,43,172,9,129,22,39,253,19,98,10,112,71,113,224,232,178,185,
        112,104,218,246,97,228,251,34,242,193,238,210,144,142,191,179,162,241,81,51,145,
        235,249,14,239,107,49,192,214,31,181,199,106,17,184,84,204,176,115,121,50,45,
        127,4,150,254,138,236,205,93,222,114,67,29,24,72,23,141,128,195,78,66,215,61,
        156,180,160,137,91,90,15,131,13,21,95,96,53,194,233,7,225,140,36,103,30,69,
        142,8,99,37,240,21,10,23,190,6,148,27,120,244,75,0,26,197,62,94,252,219,
        203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
        74,165,71,134,139,48,27,166,7,146,158,231,83,111,229,122,60,211,133,230,220,
        105,92,41,55,46,245,40,244,102,113,54,65,25,63,161,1,216,80,73,209,76,132,
        187,208,89,18,169,200,196,135,130,116,188,139,86,164,100,109,198,173,186,3,
        64,52,217,226,250,124,123,5,202,38,147,18,126,255,82,85,212,207,206,59,227,
        47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
        153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
        112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
        235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
        127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
        156,180};

    //Adapter pour la résolution
    x /= res;
    y /= res;

    //On récupère les positions de la grille associée à (x,y)
    x0 = (int)(x);
    y0 = (int)(y);

    //Masquage
    ii = x0 & 255;
    jj = y0 & 255;

    //Pour récupérer les vecteurs
    gi0 = perm[ii + perm[jj]] % 8;
    gi1 = perm[ii + 1 + perm[jj]] % 8;
    gi2 = perm[ii + perm[jj + 1]] % 8;
    gi3 = perm[ii + 1 + perm[jj + 1]] % 8;

    //on récupère les vecteurs et on pondère
    tempX = x-x0;
    tempY = y-y0;
    s = gradient2[gi0][0]*tempX + gradient2[gi0][1]*tempY;

    tempX = x-(x0+1);
    tempY = y-y0;
    t = gradient2[gi1][0]*tempX + gradient2[gi1][1]*tempY;

    tempX = x-x0;
    tempY = y-(y0+1);
    u = gradient2[gi2][0]*tempX + gradient2[gi2][1]*tempY;

    tempX = x-(x0+1);
    tempY = y-(y0+1);
    v = gradient2[gi3][0]*tempX + gradient2[gi3][1]*tempY;


    //Lissage
    tmp = x-x0;
    Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

    Li1 = s + Cx*(t-s);
    Li2 = u + Cx*(v-u);

    tmp = y - y0;
    Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

    return Li1 + Cy*(Li2-Li1);
}

void		terrainGenerationBuiltin::init()
{

}

void		terrainGenerationBuiltin::update()
{
	for (uint32_t i = 0; i < numBiom; i++)
			renderBuiltIn::render_me(bioms[i].renderGoHandler);
}

t_material	handle_material()
{
	t_material material = {0};

	material.diffuse[0] = 1;
	material.ambiant[0] = 0;
	material.ambiant[1] = 0;
	material.ambiant[2] = 0;
	return (material);
}

void	create_normal(float *data, uint32_t i, uint32_t j, uint32_t size, float *outvec, float divisor)
{
	glm::vec3 base = glm::vec3(0, 0.01 / divisor, 0);

	float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
	int32_t i1, i2,i3,i4,i5,i6,i7,i8;

	i1 = (j - 1) + (i + 1) * size;
	i2 = (j + 0) + (i + 1) * size;
	i3 = (j + 1) + (i + 1) * size;
	i4 = (j - 1) + (i + 0) * size;
	i5 = (j + 1) + (i + 0) * size;
	i6 = (j - 1) + (i - 1) * size;
	i7 = (j + 0) + (i - 1) * size;
	i8 = (j + 1) + (i - 1) * size;

	if (i1 > 0)
		a = data[i1];
	if (i2 > 0)
		b = data[i2];
	if (i3 > 0)
		c = data[i3];
	if (i4 > 0)
		d = data[i4];
	if (i5 > 0)
		e = data[i5];
	if (i6 > 0)
		f = data[i6];
	if (i7 > 0)
		g = data[i7];
	if (i8 > 0)
		h = data[i8];

	base.x = (f- e);
	base.z = (g - b);
	base = glm::normalize(base);
	outvec[0] = base.x;
	outvec[1] = base.y;
	outvec[2] = base.z;

}

void	create_vbo(int32_t size, float *data, t_renderMeshData *meshData, float scale, float ampl)
{
	float		*vertex;
	uint32_t	*indices;
	uint32_t	k;

	k = 0;
	vertex = (float*)malloc(sizeof(float) * size * size * 8);
	indices = (uint32_t*)malloc(sizeof(uint32_t) * size * size * 6);
	float treshOld = size * 0.1;
	float divisor;
	meshData->vaoId = renderDataSys::createVAO();

	meshData->vertexNum = size * size;
	meshData->indiceNum = size * size;
	meshData->material = handle_material();
	bzero(indices, size * size * sizeof(uint32_t) * 6);

	for (int32_t i = 0; i < size; i++)
	{
		for (int32_t j = 0; j < size; j++)
		{
			divisor = 1;
			// Set position

			vertex[i * size * 8 + j * 8] = (float)i * scale;
			if (size - j < treshOld)
					divisor = (float)(size - j) / treshOld;
			if (j < treshOld)
				divisor = fmin(divisor, (float)(j) / treshOld);
			if (size - i < treshOld)
					divisor = fmin(divisor, (float)(size - i) / treshOld);
			if (i < treshOld)
				divisor = fmin(divisor, (float)(i) / treshOld);
			if (divisor < 0.1)
				divisor = 0;

			vertex[i * size * 8 + j * 8 + 1] = data[j + i * size] * ampl * divisor;
			vertex[i * size * 8 + j * 8 + 2] = (float)j * scale;

			// Set normal
			create_normal(data, i, j, size, &vertex[i * size * 8 + j * 8 + 3], divisor);

			// Set UV
			vertex[i * size * 8 + j * 8 + 6] = (float)i / size;
			vertex[i * size * 8 + j * 8 + 7] = (float)j / size;

			// Set indices
			if (j != size - 1 && i != 0 && j != 0 && i != size - 1)
			{
				indices[i * size * 6 + j * 6] = k;
				indices[i * size * 6 + j * 6 + 1] = k + 1;
				indices[i * size * 6 + j * 6 + 2] = k + size;

				indices[i * size * 6 + j * 6 + 3] = k;
				indices[i * size * 6 + j * 6 + 4] = k - 1 + size;
				indices[i * size * 6 + j * 6 + 5] = k + size;
			}
			k++;
		}
	}
	meshData->vboVerticeId = renderDataSys::createVBO_VNT(vertex, size * size, meshData->vaoId);
	meshData->indiceBufferId = renderDataSys::createVBO_Indice(indices, size * size * 6, meshData->vaoId);
	meshData->indiceNum = size * 6 * size;
	free(indices);
	free(vertex);
}

void update_object(uint32_t size, float *data, t_renderMeshData *meshData, float scale, float ampl)
{
	meshData->has_child = false;
	meshData->child = 0;
	create_vbo(size, data, meshData, scale, ampl);
}

void		fill_data(float *data, uint32_t	size, uint32_t res)
{
	for (uint32_t i = 0; i < size * size; i++)
		data[i] = Get2DPerlinNoiseValue((i) / size , (i) % size, res);
}

void		terrainGenerationBuiltin::add_biom(float posx, float posy, float posz, uint32_t size, float scale, float ampl, uint32_t dataHandler, uint32_t datasize)
{
	t_biom				biom;
	uint32_t			i;
	uint32_t			meshDataHandler;
	t_node				*node;

	size += 3;
	biom.posy = posy;
	biom.posx = posx;
	biom.size = size;
	biom.dataRef = dataHandler;
	fill_data((float*)staticMemoryManager::get_data_ptr(biom.dataRef), size, 70);
	meshDataHandler = staticMemoryManager::create_asset(1, sizeof(t_node));
	node = (t_node*)staticMemoryManager::get_data_ptr(meshDataHandler);
	node->has_mesh = 1;
	node->childNum = 0;
	node->meshs = staticMemoryManager::create_asset(staticMemoryManager::E_OBJ_FILE, sizeof(t_renderMeshData));
	renderDataSys::set_programm(E_DEFAULT, meshDataHandler);
	biom.renderGoHandler = renderBuiltIn::create();
	(renderBuiltIn::get_renderGO(biom.renderGoHandler))->assetHandler = meshDataHandler;
	(renderBuiltIn::get_renderGO(biom.renderGoHandler))->transformHandler = transformBuiltin::create();
	transformBuiltin::translate((renderBuiltIn::get_renderGO(biom.renderGoHandler))->transformHandler, posx, posy, posz);
	update_object(size, (float*)staticMemoryManager::get_data_ptr(biom.dataRef), (t_renderMeshData*)staticMemoryManager::get_data_ptr(node->meshs), scale, ampl);
	biom.numFrag = i;
	bioms[numBiom++] = biom;
}
