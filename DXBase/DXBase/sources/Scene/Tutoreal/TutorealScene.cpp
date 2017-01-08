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
	//チュートリアル設定
	//1番
	TutorealName name1;
	name1.csvName = "tutoreal01";
	name1.movieID = MOVIE_ID::TEST_MOVE;
	name1.textIDs.push_back(TextureID::TUTOREAL1_1_TXT_TEX);
	name1.textIDs.push_back(TextureID::TUTOREAL1_2_TXT_TEX);
	//2番
	TutorealName name2;
	name2.csvName = "tutoreal02";
	name2.movieID = MOVIE_ID::TEST_MOVE;
	name2.textIDs.push_back(TextureID::TUTOREAL2_1_TXT_TEX);
	name2.textIDs.push_back(TextureID::TUTOREAL2_2_TXT_TEX);
	name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_1_TEX);
	name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_2_TEX);
	name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_3_TEX);
	//3番
	TutorealName name3;
	name3.csvName = "tutoreal03";
	name3.movieID = MOVIE_ID::TEST2_MOVIE;
	name3.textIDs.push_back(TextureID::TUTOREAL3_1_TXT_TEX);
	name3.textIDs.push_back(TextureID::TUTOREAL3_2_TXT_TEX);
	name3.timeCountIDs.push_back(TextureID::TUTOREAL_COUNT_1_TEX);
	name3.timeCountIDs.push_back(TextureID::TUTOREAL_COUNT_2_TEX);
	//4番
	TutorealName name4;
	name4.csvName = "tutoreal04";
	name4.movieID = MOVIE_ID::TEST2_MOVIE;
	name4.textIDs.push_back(TextureID::TUTOREAL4_1_TXT_TEX);
	name4.textIDs.push_back(TextureID::TUTOREAL4_2_TXT_TEX);
	name4.textIDs.push_back(TextureID::TUTOREAL4_3_TXT_TEX);

	//設定したやつを入れる
	tutorels_.push_back(name1);
	tutorels_.push_back(name2);
	tutorels_.push_back(name3);
	tutorels_.push_back(name4);

	//サイズを入れる
	tutorealSize_ = tutorels_.size();

}

TutorealScene::~TutorealScene()
{
}

void TutorealScene::start()
{
	//初期化たち
	isEnd_ = false;
	isMovie_ = false;
	tutorealTexCount_ = 0;
	countAndTime_ = 0;
	//α値を初期化
	alpha_ = 1.0f;
	//補間初期化
	size_ = 0.2f;
	movieMoveTime_ = 0.0f;
	//動画サイズ取得
	Vector2 movieSize = Movie::GetInstance().GetMovieSize(tutorels_[tutorealRoopCount_].movieID);
	//動画の位置設定
	moviePos_ = Vector2(SCREEN_SIZE.x-movieSize.x-320, 128);
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
	name_ = tutorels_[tutorealRoopCount_].csvName;
	//チュートリアル動画をセット
	movieId_ = tutorels_[tutorealRoopCount_].movieID;
	//テキストをセット
	tutorealTexs_ = tutorels_[tutorealRoopCount_].textIDs;
	//時間とカウントをセット
	tutorealTimes_ = tutorels_[tutorealRoopCount_].timeCountIDs;
	//動画を再生
	//Movie::GetInstance().Play(movieId_);
	//セットしたら次の名前にしておく
	if (tutorealSize_-1 > tutorealRoopCount_)
		tutorealRoopCount_++;
	//テュートリアルがない場合タイトルへ
	else
		nextScene_ = Scene::MainMenu;
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
	//α値を線形保管
	alpha_ = MathHelper::Lerp(255.0f, 0.0f, movieMoveTime_ / 90.0f);
	//サイズを線形補間
	size_=MathHelper::Lerp(0.2f, 0.8f, MathHelper::Sin(movieMoveTime_));
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

	//αブレンド
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	//上の部分
	//DrawGraph(16, 8, ResourceLoader::GetInstance().getTextureID(TextureID::TUTOREAL_BACK_TEX), TRUE);
	//テキスト部分
	DrawGraph(32, 16, ResourceLoader::GetInstance().getTextureID(tutorealTexs_[tutorealTexCount_]), TRUE);
	//時間とカウント部分
	if(!tutorealTimes_.empty())
	DrawGraph(32, 256, ResourceLoader::GetInstance().getTextureID(tutorealTimes_[0]), TRUE);
	//αブレンド終わり
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0.0f);

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
	if (nextScene_ == Scene::MainMenu) tutorealRoopCount_ = 0;
}

bool TutorealScene::isEnd() const
{
	return isEnd_;
}

Scene TutorealScene::next() const
{
	return nextScene_;
}
