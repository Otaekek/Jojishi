#include <stdio.h>
#include <mapEditorBuiltin.class.hpp>
#include <fileLoader.class.hpp>
#include <shutdown.class.hpp>
#include <runtimeLibrary.class.hpp>
#include <basicLightFactory.class.hpp>
#include <directorySmartLoader.class.hpp>

void debut()
{
	uint32_t asset = fileLoader::load_fs_asset_sync("./assets/graphic/mesh/cube/cube.obj", E_3D);
	renderDataSys::set_programm(E_SKYBOX, asset);
	renderBuiltIn::modify_skybox(asset);
	basicFPSControlManagerBuiltin::create(256 * 1300 * -0, 0000, -256 * 1300 * 0, 0, 0, 1, 1);
	renderBuiltIn::modify_skybox_light(1.2);
	basicLightFactory::create(glm::vec3(0, 10000, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), E_UNI, glm::vec3(0.4, 0.3, 0.5));
	directorySmartLoader::execute();
	terrainGenerationBuiltin::add_biom(0, 0, 0, 256,
	500, 4550, texture_builtin::create_instance(fileLoader::load_fs_asset_sync("./assets/graphic/texture/rock.jpeg", 1)), 100,
	texture_builtin::create_instance(fileLoader::load_fs_asset_sync("./assets/graphic/texture/hills.jpg", 1)));
	
	/*			terrainGenerationBuiltin::add_biom(0, 0, 0, 256,
	500, 1550, texture_builtin::create_instance(fileLoader::load_fs_asset_sync("./assets/graphic/texture/grass.jpg", 1)), 100,
	texture_builtin::create_instance(fileLoader::load_fs_asset_sync("./assets/graphic/texture/hills.jpg", 1)));
	*/
}
