#ifndef SCENE_DATA_KEEPER_H_
#define SCENE_DATA_KEEPER_H_
#include<string>
#include<DxLib.h>

class SceneDataKeeper {
public:
	SceneDataKeeper();
	SceneDataKeeper(std::string name);
	//直前のシーン名を書き換えます name:1つ前のGamePlayScene名(std::string)
	void setSceneName(std::string name);
	//直前のシーン名から次のシーン名を調べ、引数として受け取ったnameに代入します name:更新前のシーン名(std::string)
	void getNextSceneName(std::string& name);
	//直前のシーン名を受け取ります return:直前のシーン名(std::string)
	std::string getSceneName()const;
	void setPlayerHP(int hp);
	int getPlayerHP() const;
	int getInt();
private:
	std::string previousSceneName_;
	int hp_;
};

#endif