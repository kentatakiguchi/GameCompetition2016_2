#include "TutorealScene.h"
#include "../../Field/MapGenerator.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/Movie.h"
TutorealScene::TutorealScene() :
	tutorealRoopCount_(0)
{
	isEnd_ = false;
	deltaTime_ = 1.0f / 60.0f;
	//名前を入れる
	tutorealCsvs_.push_back("tutoreal01");
	tutorealCsvs_.push_back("tutoreal02");
	tutorealMovies_.push_back(MOVIE_ID::TEST_MOVE);
	tutorealMovies_.push_back(MOVIE_ID::TEST2_MOVIE);
	//サイズを入れる
	tutorealSize_ = tutorealCsvs_.size();

}

TutorealScene::~TutorealScene()
{
}

void TutorealScene::start()
{
	//エンド初期化
	isEnd_ = false;

	deltaTime_ = Time::GetInstance().deltaTime();
	//次も同じ
	nextScene_ = Scene::Tutoreal;
	//ポーズしない
	isStopped_ = false;
	//ワールド
	world_ = std::make_shared<World>();
	MapGenerator gener = MapGenerator(world_.get());

	//ネームをセット
	name_ = tutorealCsvs_[tutorealRoopCount_];
	movieId_ = tutorealMovies_[tutorealRoopCount_];
	//動画を再生
	//Movie::GetInstance().Play(movieId_);
	//セットしたら次の名前にしておく
	if (tutorealSize_-1 > tutorealRoopCount_)
		tutorealRoopCount_++;
	//テュートリアルがない場合タイトルへ
	else
		nextScene_ = Scene::Title;

	//プレイヤーの座標をセット
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));
	//プレイヤーを追加
	world_->addActor(ActorGroup::Player, std::make_shared<Player>
		(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	gener.create("./resources/file/" + name_ + ".csv", 0, 0);
	//スクロールセット
	world_->SetScroolJudge(Vector2(0, 0), Vector2(9999, 9999));


}

void TutorealScene::update()
{
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::J)) {
		isEnd_ = true;
	}
	world_->update(deltaTime_);


}

void TutorealScene::draw() const
{

	world_->draw();
	//Movie::GetInstance().Draw(movieId_, Vector2::Zero,0.5f);
}

void TutorealScene::end()
{
	////再生時間を0に戻す
	//Movie::GetInstance().Seek(movieId_, 0.0f);
	////再生ストップ
	//Movie::GetInstance().Stop(movieId_);
	//チュートリアルの進みをリセット
	if (nextScene_ == Scene::Title) tutorealRoopCount_ = 0;
}

bool TutorealScene::isEnd() const
{
	return isEnd_;
}

Scene TutorealScene::next() const
{
	return nextScene_;
}
