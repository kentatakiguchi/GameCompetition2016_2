#include "SceneChange.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include"../../Game/Time.h"
#include"../../Define.h"

static const float SdefTime = 0.05;
static const float SfallSpeed = 30;
static const float SSlimePadd = 46;
static const Vector2 SSlimeSize = Vector2(290, 130);
static const int LineSize = 8;
SceneChange::SceneChange():isMainMenu_(false),isEnd_(true),isSlimeMax_(true),slimeCount(0),timeCount(SdefTime),deltaTime_(0),slimesetline(0), switchCount(0), mt(random_()), rand256(0, 255),randL(0, LineSize-1),changeCount(0)
{
	spawnPoses[0][0] = (Vector2((SSlimeSize.x - SSlimePadd)*(-0.5), 0));
	spawnPoses[0][1] = (Vector2((SSlimeSize.x - SSlimePadd) * 0.5, 0));
	spawnPoses[0][2] = (Vector2((SSlimeSize.x - SSlimePadd) * 1.5, 0));
	spawnPoses[0][3] = (Vector2((SSlimeSize.x - SSlimePadd) * 2.5, 0));
	spawnPoses[0][4] = (Vector2((SSlimeSize.x - SSlimePadd) * 3.5, 0));
	spawnPoses[0][5] = (Vector2((SSlimeSize.x - SSlimePadd) * 4.5, 0));
	spawnPoses[0][6] = (Vector2((SSlimeSize.x - SSlimePadd) * 5.5, 0));
	spawnPoses[0][7] = (Vector2((SSlimeSize.x - SSlimePadd) * 6.5, 0));
	//spawnPoses[0][8] = (Vector2((SSlimeSize.x - SSlimePadd) * 7.5, 0));

	spawnPoses[1][0] = (Vector2((spawnPoses[0].at(1).x-(SSlimeSize.x/2)) + SSlimePadd, 0));
	spawnPoses[1][1] = (Vector2((spawnPoses[0].at(2).x - (SSlimeSize.x / 2)) + SSlimePadd, 0));
	spawnPoses[1][2] = (Vector2((spawnPoses[0].at(3).x - (SSlimeSize.x / 2) + SSlimePadd), 0));
	spawnPoses[1][3] = (Vector2((spawnPoses[0].at(4).x - (SSlimeSize.x / 2) + SSlimePadd), 0));
	spawnPoses[1][4] = (Vector2((spawnPoses[0].at(5).x - (SSlimeSize.x / 2) + SSlimePadd), 0));
	spawnPoses[1][5] = (Vector2((spawnPoses[0].at(6).x - (SSlimeSize.x / 2) + SSlimePadd), 0));
	spawnPoses[1][6] = (Vector2((spawnPoses[0].at(7).x - (SSlimeSize.x / 2) + SSlimePadd), 0));
	//spawnPoses[1][7] = (Vector2((spawnPoses[0].at(8).x - (SSlimeSize.x / 2) + SSlimePadd), 0));
	spawnPoses[1][7] = (Vector2((((SSlimeSize.x - SSlimePadd) *7.5) - (SSlimeSize.x / 2) + SSlimePadd), 0));
	//spawnPoses[1][8] = (Vector2((((SSlimeSize.x - SSlimePadd) * 8.5) - (SSlimeSize.x / 2) + SSlimePadd), 0));

	allSizes = spawnPoses[0].size() + spawnPoses[1].size();
}

void SceneChange::start(std::string next)
{
	changeCount = 0;

	isEnd_ = false;
	isSlimeMax_ = false;

	if (next != "MainMenu") {
		isMainMenu_ = false;
		return;
	}
	isMainMenu_ = true;

		slimeCount = 0;
		switchCount = 0;
		slimesetline = 0;
		timeCount = SdefTime;
		slimes.clear();
		slimeColors.clear();
		deltaTime_ = Time::GetInstance().deltaTime();

		numberMap.clear();
		for (int i = 0; i < LineSize; i++) {
 			numberMap.push_back(i);
		}
		randL = std::uniform_int_distribution<>(0, numberMap.size() - 1);
}

void SceneChange::update()
{

	if (isEnd_)return;

	if (!isMainMenu_) {
		changeCount++;
		if (!isMainMenu_) {
			changeCount >= fadeTime ? isEnd_ = true : isEnd_ = false;
		}if (!isMainMenu_) {
			changeCount >= fadeTime / 2 ? isSlimeMax_ = true : isSlimeMax_ = false;
		}
		return;
	}
	if (isSlimeMax_)
	{
		fallSlimes();
		return;
	}

	deltaTime_ = Time::GetInstance().deltaTime();
	timeCount -= deltaTime_;

	float setline = 0;

	for (int i = 0; i < slimeCount; i++) {
		slimes[i] += Vector2(0,SfallSpeed);

		if (slimes[i].y >= SCREEN_SIZE.y-SSlimeSize.y - (SSlimeSize.y*setline)) {
			slimes[i].y = (SCREEN_SIZE.y-SSlimeSize.y)-(SSlimeSize.y*setline);
			


			if (i % spawnPoses[slimesetline % 2].size() == spawnPoses[slimesetline % 2].size() -1&&i!=0) {
				setline++;


				if (setline > (int)(SCREEN_SIZE.y/SSlimeSize.y)) {
					isSlimeMax_ = true;
				}
			}
		}
	}

	if (timeCount < 0) {
		if (slimes.size() % spawnPoses[slimesetline % 2].size() == 0) {
			slimesetline++;

		}
		timeCount = SdefTime;

		//if (i % spawnPoses[slimesetline % 2].size() == spawnPoses[slimesetline % 2].size() - 1 && i != 0) {}

		//slimes[slimeCount] = spawnPoses[slimesetline % 2].at(switchCount%spawnPoses[slimesetline % 2].size());

		int setInt = randL(mt);
			

		slimes[slimeCount] = spawnPoses[slimesetline%2].at(numberMap[setInt]);


		if(numberMap.size()>0)numberMap.erase(numberMap.begin()+ setInt);

		slimeColors[slimeCount] = ChangeSColor(rand256(mt), rand256(mt), rand256(mt));
		slimeCount++;
		switchCount++;
		// /8=7
		if (slimes.size() % spawnPoses[slimesetline % 2].size() ==0/* spawnPoses[slimesetline % 2].size()*/ && slimes.size() > 1) {
			for (int i = 0; i < LineSize; i++) {
				numberMap.push_back(i);
			}
		}
		randL = std::uniform_int_distribution<>(0, numberMap.size() - 1);

	}
}

void SceneChange::fallSlimes()
{
	for (int i = 0; i < slimes.size(); i++) {
		slimes[i] += Vector2(0, 80);
	}
	if (slimes.at(slimes.size()-1).y >= SCREEN_SIZE.y) isEnd_ = true;
}

void SceneChange::draw() const
{
	if (isEnd_)return;



	for (int i = 0; i < slimeCount; i++) {
		SetDrawBright(slimeColors.at(i).Red, slimeColors.at(i).Green, slimeColors.at(i).Blue);
		DrawGraph(slimes.at(i).x, slimes.at(i).y, ResourceLoader::GetInstance().getTextureID(TextureID::CHANGE_SCENE_TEX), TRUE);
		SetDrawBright(255, 255, 255);
	}
}
