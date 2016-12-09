#pragma once

#include<map>
#include<vector>
#include"../../Math/Vector2.h"
#include<random>
#include"../Base/Scene.h"

static const int fadeTime = 100;

struct ChangeSColor
{
	int Red;
	int Green;
	int Blue;
	ChangeSColor() {

	}
	ChangeSColor(int R,int G,int B) {
		Red = R;
		Green = G;
		Blue = B;
	}
};
class SceneChange {
public:
	SceneChange();
	void start(std::string next);
	void update();
	void fallSlimes();
	void draw()const;
	bool getEnd()const {
			return isEnd_;
		
	}


	bool getIsSlimeMax()const {
			return isSlimeMax_;
	}
private:
	bool isSlimeMax_;
	bool isEnd_;

	int slimesetline;
	float deltaTime_;
	int slimeCount;
	int switchCount;
	float timeCount;
	std::vector<int> numberMap;
	std::map<int, Vector2> slimes;
	std::map<int, ChangeSColor> slimeColors;
	std::map<int, std::map<int, Vector2>> spawnPoses;

	int allSizes;
	
	std::random_device random_;
	std::mt19937 mt;
	std::uniform_int_distribution<> rand256;
	std::uniform_int_distribution<> randL;

	//MainMenu�ȊO�̃V�[�����t�F�[�h�C��,�A�E�g�����邽�߂̒l
	int changeCount;

	bool isMainMenu_;
};