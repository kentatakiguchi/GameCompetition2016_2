#include "ResourceLoader.h"

ResourceLoader::ResourceLoader() {
}

ResourceLoader::~ResourceLoader() {
}

ResourceLoader & ResourceLoader::GetInstance() {
	static ResourceLoader instance;
	return instance;
}

void ResourceLoader::loadModel(ModelID id, const char* file_name) {
	//if (MV1LoadModel(file_name) == -1)DxLib_End();
	models_[id] = MV1LoadModel(file_name);
}

void ResourceLoader::loadTexture(TextureID id, const char* file_name) {
	//if (LoadGraph(file_name) == -1)DxLib_End();
	textures_[id] = LoadGraph(file_name);
}

void ResourceLoader::loadSound(SoundID id, const char * file_name){
	sounds_[id] = LoadSoundMem(file_name);
}

int ResourceLoader::getModelID(ModelID id) {
	return models_[id];
}

int ResourceLoader::getTextureID(TextureID id) {
	return textures_[id];
}

int ResourceLoader::getSoundID(SoundID id){
	return sounds_[id];
}

Vector2 ResourceLoader::GetTextureSize(TextureID id)
{
	int x, y, flag;
	//テクスチャのサイズ取得
	flag = GetGraphSize(ResourceLoader::GetInstance().getTextureID(id), &x, &y);
	//エラーだ
	if (flag < 0) return Vector2::Zero;
	//成功だ
		return Vector2(x, y);
}

void ResourceLoader::clearResources()
{
	for (auto model : models_) {
		MV1DeleteModel(model.second);
	}
	models_.clear();
	for (auto texture : textures_) {
		MV1DeleteModel(texture.second);
	}
	textures_.clear();
}
