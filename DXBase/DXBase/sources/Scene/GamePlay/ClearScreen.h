#pragma once

#include "DxLib.h"
#include"../Base/Scene.h"
#include<vector>
#include<map>
#include"../StageClear/StageClearTextAnm.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include"../Base/SceneDataKeeper.h"

class ClearScreen {
public:
	ClearScreen() {}
	ClearScreen(SceneDataKeeper* keeper);
	bool update(std::string name, Scene& next);
	void draw() const;
	bool isCounT() const{
		return Count_ <= 0;
	};
	void drawNumber(int drawNum, int baseNum,int posx,int posy,int maxSize=3) const{
		int posCount = 0;
		std::vector<int> drawNumberList;

		for (int i = 0;i<maxSize;i++) {

			if (baseNum < 10) {
				drawNumberList.push_back(baseNum);
				//DrawGraph((SCREEN_SIZE.x - CountPos)
				//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[baseNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[baseNum]), TRUE);
				//break;
				baseNum = 0;
				continue;
			}

			drawNum = (int)(baseNum*0.1);
			drawNum = drawNum * 10;
			int textNum = baseNum - drawNum;

			drawNumberList.push_back(textNum);
			//DrawGraph((SCREEN_SIZE.x - CountPos) 
			//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[textNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[textNum]), TRUE);

			baseNum = (int)(baseNum*0.1);
			posCount++;
			//DrawFormatString(SCREEN_SIZE.x - 100, 50, GetColor(0, 0, 0), "%d", );
		}
		
		int drawPosCount = drawNumberList.size() - 1;
		for (int i = 0; i < (int)drawNumberList.size(); i++) {

			DrawGraph(posx +ResourceLoader::GetInstance().GetTextureSize(numberTexes_[drawNumberList[i]]).x*drawPosCount,posy, ResourceLoader::GetInstance().getTextureID(numberTexes_[drawNumberList[i]]), TRUE);
			drawPosCount--;
		}

	}
private:
	std::vector<std::string> changeTextList;
	std::vector<std::vector<std::string>> listBase;
	std::vector<Vector2> textPosList;
	std::map<int, TextureID> textIDs;

	std::map<std::string, Vector2> textPositions;

	std::vector<TextureID> numberTexes_;

	StageClearTextAnm anmer_;
	SceneDataKeeper* keeper_;
	int Count_;
	int ints;
};