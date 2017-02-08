#ifndef SCENE_DATA_KEEPER_H_
#define SCENE_DATA_KEEPER_H_
#include<string>
#include<DxLib.h>
#include<vector>


class SceneDataKeeper {
public:
	SceneDataKeeper();
	SceneDataKeeper(std::string name);
	//���O�̃V�[���������������܂� name:1�O��GamePlayScene��(std::string)
	void setSceneName(std::string name);
	//���O�̃V�[�������玟�̃V�[�����𒲂ׁA�����Ƃ��Ď󂯎����name�ɑ�����܂� name:�X�V�O�̃V�[����(std::string)
	int getNextSceneName(std::string& name);
	//���O�̃V�[�������󂯎��܂� return:���O�̃V�[����(std::string)
	std::string getSceneName()const;
	void setPlayerHP(int hp);
	int getPlayerHP() const;
	int getInt();
	void setItemCount(int itemCount) {
		itemCount_ = itemCount;
	}
	void addCount(int adds) {
		itemCount_ += adds;
	}
	void ItemReset() {
		itemCount_ = 0;
	}
	void ItemMinus(int minusCount) {
		itemCount_ -= minusCount;
	}
	int GetItemCount() {
		return itemCount_;
	}
	//0�Ȃ�S���̍��v
	int GetMaxItemCount(int num=0) {
		if (num == 0) {
			int mas=0;
			for(int i = 0; i < maxItemCount_.size(); i++) {
				mas += maxItemCount_[i];
			}
			return mas;
		}
		return maxItemCount_[num];
	}
	void setMaxItemCount(int max, int num) {
		maxItemCount_[num] = max;
	}
	void addMaxItemCount(int add, int num) {
		maxItemCount_[num] += add;
	}
	void resetMaxItemCount() {
		for (int i = 0; i < maxItemCount_.size(); i++) {
			maxItemCount_[i] = 0;
		}
	}
	int getJumpCount() {
		return jumpCount_;
	}
	void setJumpCount(int jumpCount) {
		jumpCount_ = jumpCount;
	}
	void addJumpCount(int jumpCount) {
		jumpCount_ += jumpCount;
	}
	void jumpReset() {
		jumpCount_ = 0;
	}
	void jumpMinus(int minusCount) {
		jumpCount_ -= minusCount;
	}
	int getDamageCount() {
		return damageCount_;
	}
	void setDamageCount(int damageCount) {
		damageCount_ = damageCount;
	}
	void addDamageCount(int damageCount) {
		damageCount_ += damageCount;
	}
	void DamageReset() {
		damageCount_ = 0;
	}
	void DamageMinus(int minusCount) {
		damageCount_ -= minusCount;
	}

private:
	std::string previousSceneName_;
	int hp_;
	int itemCount_;
	std::vector<int> maxItemCount_;
	int jumpCount_;
	int damageCount_;
};

#endif