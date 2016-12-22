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
	//初期化たち
	isEnd_ = false;
	isMovie_ = false;
	//補間初期化
	size_ = 0.1f;
	movieMoveTime_ = 0.0f;
	moviePos_ = Vector2(128, 64);
	movieResPos1_ = moviePos_;
	movieResPos2_ = Vector2(SCREEN_SIZE.x / 2 , SCREEN_SIZE.y / 2 );
	//デルタタイム
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
	//チュートリアル動画をセット
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
	//マップ生成
	gener.create("./resources/file/" + name_ + ".csv", 0, 0);
	//スクロールセット
	world_->SetScroolJudge(Vector2(0, 0), Vector2(9999, 9999));
}

void TutorealScene::update()
{
	//Tを押したらチュートリアル動画が再生される
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
		isMovie_ = !isMovie_;
		if (isMovie_) {
			//Movie::GetInstance().Stop(movieId_);
			//Movie::GetInstance().Seek(movieId_, 0.0f);
		}
	}
	//補間時間関係
	if (isMovie_) movieMoveTime_ += 90 * Time::GetInstance().deltaTime();
	else movieMoveTime_ -= 90*Time::GetInstance().deltaTime();
	
	//クランプ
	movieMoveTime_=MathHelper::Clamp(movieMoveTime_, 0.0f, 90.0f);
	//拡大し終わったら再生する
	//if (movieMoveTime_ >= 90) Movie::GetInstance().Play(movieId_);

	//サイズを線形補間
	size_=MathHelper::Lerp(0.1f, 0.8f, MathHelper::Sin(movieMoveTime_));
	//移動を線形補間
	moviePos_ = Vector2::Lerp(movieResPos1_, movieResPos2_, MathHelper::Sin(movieMoveTime_));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::J)) {
		isEnd_ = true;
	}
	world_->update(deltaTime_);
}

void TutorealScene::draw() const
{
	world_->draw();
	//動画の後ろの画像
	int id = ResourceLoader::GetInstance().getTextureID(TextureID::MOVIEBACK_TEX);
	DrawRotaGraph(moviePos_.x, moviePos_.y, size_, 0.0f, id, TRUE);
	//動画
	//Movie::GetInstance().DrawRotaMovie(movieId_, moviePos_,size_);
}

void TutorealScene::end()
{
	//再生時間を0に戻す
	Movie::GetInstance().Seek(movieId_, 0.0f);
	//再生ストップ
	Movie::GetInstance().Stop(movieId_);
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
