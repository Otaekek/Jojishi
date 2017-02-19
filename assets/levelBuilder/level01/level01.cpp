#include <stdio.h>
#include <mapEditorBuiltin.class.hpp>
#include <fileLoader.class.hpp>
#include <shutdown.class.hpp>
#include <runtimeLibrary.class.hpp>

void debut()
{
		terrainGenerationBuiltin::add_biom(0, 0, 0, 256,
	500, 1550, texture_builtin::create_instance(fileLoader::load_fs_asset_sync("./assets/graphic/texture/grass.jpg", 1)), 100,
	texture_builtin::create_instance(fileLoader::load_fs_asset_sync("./assets/graphic/texture/hills.jpg", 1)));

}