#pragma once

#include "DxLib.h"
#include"../Base/Scene.h"
#include<vector>
#include<map>
#include"../StageClear/StageClearTextAnm.h"
#include"../../ResourceLoader/ResourceLoader.h"

class ClearScreen {
public:
	ClearScreen();
	bool update(std::string name, Scene& next);
	void draw() const;
	bool isCounT() const{
		return Count_ <= 0;
	};

private:
	std::vector<std::string> changeTextList;
	std::vector<std::vector<std::string>> listBase;
	std::vector<Vector2> textPosList;
	std::map<int, TextureID> textIDs;

	StageClearTextAnm anmer_;
	
	int Count_;
	int ints;
};