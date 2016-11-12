#include "SceneDataKeeper.h"

SceneDataKeeper::SceneDataKeeper() :previousSceneName_("stage03"), hp_(0)
{
}

SceneDataKeeper::SceneDataKeeper(std::string name):previousSceneName_(name),hp_(0)
{
}

void SceneDataKeeper::setSceneName(std::string name)
{
	std::string::size_type pos = name.find("stage");
	if (pos == std::string::npos) return;

	previousSceneName_ = name;
	OutputDebugString(name.c_str());
}
void SceneDataKeeper::getNextSceneName(std::string& name)
{
	for (int i = 1; i < 4; i++) {
		if (previousSceneName_.find(std::to_string(i)) != std::string::npos) {
			int plus = 1;
			if (i == 3) plus = -2;
			name = "stage0" + std::to_string(i + plus);
			return;
		}
	}
	name= previousSceneName_;
}
std::string SceneDataKeeper::getSceneName()const
{	
	return previousSceneName_;
	//for (int i = 0; i < 3; i++) {
	//	if (previousSceneName_.find("stage01") != std::string::npos) {
	//		previousSceneName_ = "stage02";
	//		}
	//	else if (previousSceneName_.find("stage02") != std::string::npos) {
	//		previousSceneName_ = "stage03";
	//	}
	//	else if (previousSceneName_.find("stage03") != std::string::npos) {
	//		previousSceneName_ = "stage01";
	//	}
}

void SceneDataKeeper::setPlayerHP(int hp)
{
	hp_ = hp;
}

int SceneDataKeeper::getPlayerHP() const
{
	return hp_;
}
