#pragma once

#include <DxLib.h>

#include <unordered_map>
#include <string>
#include "../Math/Vector2.h"
enum class ModelID {
	PLAYER,
	ENEMY,
	STAGE,
	STAGE_COLL,
	SKYDOME
};

enum class TextureID {
	BACKGRAUND1_TEX,
	BACKGRAUND2_TEX,
	BACKGRAUND3_TEX,
	BACKGRAUND4_TEX,
	BACKGRAUND_BOT_TEX,
	BACKGRAUND_TOP_TEX,
	ENEMY_SAMPLE_TEX
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
	//テクスチャのサイズを取得する(引数:テクスチャハンドル,戻り値:Vector2)
	Vector2 GetTextureSize(TextureID id);
	void clearResources();
private:
	std::unordered_map<ModelID, int> models_;
	std::unordered_map<TextureID, int> textures_;

};