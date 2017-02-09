#include "SceneDataKeeper.h"

SceneDataKeeper::SceneDataKeeper() :previousSceneName_("stage04"), hp_(0),itemCount_(0),jumpCount_(0),damageCount_(0)
{
	maxItemCount_.resize(5);
	datas_.clear();
}

SceneDataKeeper::SceneDataKeeper(std::string name):previousSceneName_(name),hp_(0), itemCount_(0), jumpCount_(0), damageCount_(0){
}

//直前のシーン名を書き換えます name:1つ前のGamePlayScene名(std::string)

void SceneDataKeeper::setSceneName(std::string name){
	if (name == "bossStage01") {
		previousSceneName_ = name;
		return;
	}
	std::string::size_type pos = name.find("stage");
	if (pos == std::string::npos) return;

	previousSceneName_ = name;
	//OutputDebugString(name.c_str());
}

//直前のシーン名から次のシーン名を調べ、引数として受け取ったnameに代入します name:更新前のシーン名(std::string)

int SceneDataKeeper::getNextSceneName(std::string & name){
	for (int i = 1; i < 5; i++) {
		if (previousSceneName_.find(std::to_string(i)) != std::string::npos) {
			int plus = 1;
			if (i == 4) plus = -3;
			name = "stage0" + std::to_string(i + plus);
			return i + plus;
		}
	}
	name = previousSceneName_;
	return 0;
}

//直前のシーン名を受け取ります return:直前のシーン名(std::string)

std::string SceneDataKeeper::getSceneName() const{
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

void SceneDataKeeper::setPlayerHP(int hp){
	hp_ = hp;
}

int SceneDataKeeper::getPlayerHP() const{
	return hp_;
}

int SceneDataKeeper::getInt(){
	for (int i = 1; i < 5; i++) {
		if (previousSceneName_.find(std::to_string(i)) != std::string::npos) {
			int myi;
			int plus = 1;
			if (i == 4) plus = -3;
			myi = i + plus;
			return myi;
		}
	}
}

void SceneDataKeeper::setItemCount(int itemCount) {
	itemCount_ = itemCount;
}

void SceneDataKeeper::addCount(int adds) {
	itemCount_ += adds;
}

void SceneDataKeeper::ItemReset() {
	itemCount_ = 0;
}

void SceneDataKeeper::ItemMinus(int minusCount) {
	itemCount_ -= minusCount;
}

int SceneDataKeeper::GetItemCount() {
	return itemCount_;
}

//0なら全部の合計

int SceneDataKeeper::GetMaxItemCount(int num) {
	if (num == 0) {
		int mas = 0;
		for (int i = 0; i < maxItemCount_.size(); i++) {
			mas += maxItemCount_[i];
		}
		return mas;
	}
	return maxItemCount_[num];
}

void SceneDataKeeper::setMaxItemCount(int max, int num) {
	maxItemCount_[num] = max;
}

void SceneDataKeeper::addMaxItemCount(int add, int num) {
	maxItemCount_[num] += add;
}

void SceneDataKeeper::resetMaxItemCount() {
	for (int i = 0; i < maxItemCount_.size(); i++) {
		maxItemCount_[i] = 0;
	}
}

int SceneDataKeeper::getJumpCount() {
	return jumpCount_;
}

void SceneDataKeeper::setJumpCount(int jumpCount) {
	jumpCount_ = jumpCount;
}

void SceneDataKeeper::addJumpCount(int jumpCount) {
	jumpCount_ += jumpCount;
}

void SceneDataKeeper::jumpReset() {
	jumpCount_ = 0;
}

void SceneDataKeeper::jumpMinus(int minusCount) {
	jumpCount_ -= minusCount;
}

int SceneDataKeeper::getDamageCount() {
	return damageCount_;
}

void SceneDataKeeper::setDamageCount(int damageCount) {
	damageCount_ = damageCount;
}

void SceneDataKeeper::addDamageCount(int damageCount) {
	damageCount_ += damageCount;
}

void SceneDataKeeper::DamageReset() {
	damageCount_ = 0;
}

void SceneDataKeeper::DamageMinus(int minusCount) {
	damageCount_ -= minusCount;
}

void SceneDataKeeper::resultJumpSet(int result) {
	jumpCountResult_ += result;
}

int SceneDataKeeper::resultJumpGet() {
	return jumpCountResult_;
}

void SceneDataKeeper::addResultJump(int jumpCountResult) {
	jumpCountResult_ += jumpCountResult;
}

void SceneDataKeeper::resultJumpReset() {
	jumpCountResult_ = 0;
}

void SceneDataKeeper::resultJumpMinus(int minusCount) {
	jumpCountResult_ -= minusCount;
}

void SceneDataKeeper::resultDamageSet(int result) {
	damageCountResult_ += result;
}

int SceneDataKeeper::resultDamageGet() {
	return damageCountResult_;
}

void SceneDataKeeper::addResultDamage(int damageCountResult) {
	damageCountResult_ += damageCountResult;
}

void SceneDataKeeper::resultDamageReset() {
	damageCountResult_ = 0;
}

void SceneDataKeeper::resultDamageMinus(int minusCount) {
	damageCountResult_ -= minusCount;
}

