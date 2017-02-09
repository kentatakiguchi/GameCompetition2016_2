#ifndef SCENE_DATA_KEEPER_H_
#define SCENE_DATA_KEEPER_H_
#include<string>
#include<DxLib.h>
#include<vector>

class SceneDataKeeper {
private:
	struct StageDatas {
		std::string previousSceneName_;
		int hp_;
		int itemCount_;
		std::vector<int> maxItemCount_;
		int maxCombo_;
		std::vector<int> comboCount_;
		int damageCount_;
		int holdCount_;
		int moveDistance_;
		int plusStar_;
		int minusStar_;
		int chargeTime_;
		int enemyCount_;
	};
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
	void setItemCount(int itemCount);
	void addCount(int adds);
	void ItemReset();
	void ItemMinus(int minusCount);
	int GetItemCount();
	//0�Ȃ�S���̍��v
	int GetMaxItemCount(int num = 0);
	void setMaxItemCount(int max, int num);
	void addMaxItemCount(int add, int num);
	void resetMaxItemCount();
	int getJumpCount();
	void setJumpCount(int jumpCount);
	void addJumpCount(int jumpCount);
	void jumpReset();
	void jumpMinus(int minusCount);
	int getDamageCount();
	void setDamageCount(int damageCount);
	void addDamageCount(int damageCount);
	void DamageReset();
	void DamageMinus(int minusCount);
	void resultJumpSet(int result);
	int resultJumpGet();
	void addResultJump(int jumpCountResult);
	void resultJumpReset();
	void resultJumpMinus(int minusCount);
	void resultDamageSet(int result);
	int resultDamageGet();
	void addResultDamage(int damageCountResult);
	void resultDamageReset();
	void resultDamageMinus(int minusCount);

private:
	std::vector<StageDatas> datas_;

	std::string previousSceneName_;
	int hp_;
	int itemCount_;
	std::vector<int> maxItemCount_;
	int jumpCount_;
	int jumpCountResult_;
	int damageCount_;
	int damageCountResult_;
};

#endif