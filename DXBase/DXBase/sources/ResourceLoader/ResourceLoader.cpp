#include "ResourceLoader.h"

ResourceLoader::ResourceLoader(){
}

ResourceLoader::~ResourceLoader(){
}

ResourceLoader & ResourceLoader::GetInstance(){
	static ResourceLoader instance;
	return instance;
}

void ResourceLoader::loadModel(ModelID id, const char* file_name){
	models_[id] = MV1LoadModel(file_name);
}

void ResourceLoader::loadTexture(TextureID id, const char* file_name){
	textures_[id] = LoadGraph(file_name);
}

int ResourceLoader::getModelID(ModelID id){
	return models_[id];
}

int ResourceLoader::getTextureID(TextureID id){
	return textures_[id];
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
