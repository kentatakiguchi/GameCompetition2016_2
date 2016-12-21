#pragma once
#include <memory>
#include "../Base/IScene.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include <vector>
#include <string>
#include "../GamePlay/MoveScreen.h"
#include "../GamePlay/PauseScreen.h"
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
	//チュートリアルcsv名前たち
	std::vector<std::string> tutorealCsvs_;
	//チュートリアル動画たち
	std::vector<MOVIE_ID> tutorealMovies_;
};