#ifndef SCENE_DATA_KEEPER_H_
#define SCENE_DATA_KEEPER_H_
#include<string>
#include<DxLib.h>

class SceneDataKeeper {
public:
	SceneDataKeeper();
	SceneDataKeeper(std::string name);
	//���O�̃V�[���������������܂� name:1�O��GamePlayScene��(std::string)
	void setSceneName(std::string name);
	//���O�̃V�[�������玟�̃V�[�����𒲂ׁA�����Ƃ��Ď󂯎����name�ɑ�����܂� name:�X�V�O�̃V�[����(std::string)
	void getNextSceneName(std::string& name);
	//���O�̃V�[�������󂯎��܂� return:���O�̃V�[����(std::string)
	std::string getSceneName()const;
	void setPlayerHP(int hp);
	int getPlayerHP() const;
	int getInt();
private:
	std::string previousSceneName_;
	int hp_;
};

#endif