#include "ResourceLoader.h"

ResourceLoader::ResourceLoader() {
}

ResourceLoader::~ResourceLoader() {
}

ResourceLoader & ResourceLoader::GetInstance() {
	static ResourceLoader instance;
	return instance;
}

void ResourceLoader::loadModel(const ModelID& id, const char* file_name) {
	//if (MV1LoadModel(file_name) == -1)DxLib_End();
	models_[id] = MV1LoadModel(file_name);
}

void ResourceLoader::loadTexture(const TextureID& id, const char* file_name) {
	//if (LoadGraph(file_name) == -1)DxLib_End();
	textures_[id] = LoadGraph(file_name);
}

void ResourceLoader::loadAnimation(const AnimationID& id, const char * file_name, const int & size, const int & row, const int & column, const int & surplus){
	int handle = LoadGraph(file_name);	
	for (int i = 0; i < column; ++i) {
		for (int j = 0; j < ((i < column - 1) ? row : row - surplus); ++j) {
			// 切り取る左上の座標
			Vector2 src = Vector2(j, i) * size;
			animations_[id].push_back(DerivationGraph(src.x, src.y, size, size, handle));
		}
	}
}

void ResourceLoader::loadSound(const SoundID& id, const char * file_name){
	sounds_[id] = LoadSoundMem(file_name);
}

int ResourceLoader::getModelID(const ModelID& id) {
	return models_[id];
}

int ResourceLoader::getTextureID(const TextureID& id) {
	return textures_[id];
}

int ResourceLoader::getSoundID(const SoundID& id){
	return sounds_[id];
}

std::vector<int> ResourceLoader::getAnimationIDs(const AnimationID& id){
	return animations_[id];
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
