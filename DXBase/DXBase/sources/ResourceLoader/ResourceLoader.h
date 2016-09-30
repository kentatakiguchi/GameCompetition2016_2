#pragma once

#include <DxLib.h>

#include <unordered_map>
#include <string>

enum class ModelID {
	PLAYER,
	ENEMY,
	STAGE,
	STAGE_COLL,
	SKYDOME
};

enum class TextureID {

};

class ResourceLoader{
private:
	ResourceLoader();
	~ResourceLoader();
public:
	static ResourceLoader& GetInstance();

	void loadModel(ModelID id, const char* file_name);
	void loadTexture(TextureID id, const char* file_name);

	int getModelID(ModelID id);
	int getTextureID(TextureID id);

	void clearResources();
private:
	std::unordered_map<ModelID, int> models_;
	std::unordered_map<TextureID, int> textures_;

};