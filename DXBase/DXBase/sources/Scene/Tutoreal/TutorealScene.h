#pragma once
#include <memory>
#include "../Base/IScene.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include <vector>
#include <string>
#include "../GamePlay/MoveScreen.h"
#include "../GamePlay/PauseScreen.h"


struct TutorealName {
	std::string csvName;
	MOVIE_ID movieID;
	std::vector<TextureID> textIDs;
	std::vector<TextureID> timeCountIDs;
};


class World;
class TutorealScene : public IScene {
public:
	TutorealScene();
	~TutorealScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	//デルタタイム
	float deltaTime_;
	using WorldPtr = std::shared_ptr<World>;
	// ワールド
	WorldPtr	world_;
	//ポーズフラグ
	bool isStopped_;
	//チュートリアルサイズ
	int tutorealSize_;
	//何回繰り返したか
	int tutorealRoopCount_;
	//次のシーン
	Scene nextScene_;
	//動画ID
	MOVIE_ID movieId_;
	//チュートリアルたち
	std::vector<TutorealName> tutorels_;
	//動画を選択したか
	bool isMovie_;
	//動画の位置
	Vector2 movieResPos1_;
	Vector2 movieResPos2_;
	Vector2 moviePos_;
	//サイズ
	float size_;
	//チュートリアルのテキストたち
	std::vector<TextureID> tutorealTexs_;
	//α値
	float alpha_;
	//動画移動の補間
	float movieMoveTime_;
	//チュートリアルテキスト番号
	int tutorealTexCount_;
	//カウントや時間
	std::vector<TextureID> tutorealTimes_;
	//チュートリアルの時間とかカウントとか
	int countAndTime_;
};