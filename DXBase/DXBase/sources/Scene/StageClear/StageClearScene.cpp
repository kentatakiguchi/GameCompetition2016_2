#include "StageClearScene.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include"../../Actor/Person/Player/PlayerBody.h"
#include"../../Actor/Base/ActorPtr.h"

StageClearScene::StageClearScene(SceneDataKeeper* keeper){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "StageClear";
	nextScene = Scene::GamePlay;

}

StageClearScene::~StageClearScene() {

}

void StageClearScene::start() {

	SetDrawScreen(DX_SCREEN_BACK);

	//Worldを生成し、プレイヤーを追加
	world_ = std::make_shared<World>();
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), Vector2(-400, 900)));

	//プレイヤーは自動での移動、判定等は行わないようにする
	world_->PlayerNotMove(true);
	world_->CollisitionOffOn(false);

	//経過時間の初期化
	mIvemtTime = 0;

	//ボスの初期位置を設定する
	bossPosition = Vector2(-100, 500);

	//アニメーションの初期化
	anmer_ = SceneChangeBossAnm();

	//stage04をクリアした場合のみ、次のシーンをボスステージに変更する
	if (keeper_->getSceneName() == "stage04")nextScene = Scene::BossStage01;

}
void StageClearScene::update() {
	//アニメーションの更新
	anmer_.update_e(Time::GetInstance().deltaTime());

	//経過時間の更新
	mIvemtTime += Time::GetInstance().deltaTime();
	//～1秒の間は何もしない
	if (mIvemtTime <= 1.0f) {
	}
	//～3秒の間はボスを右上に移動する
	else if (mIvemtTime <= 3.0f) {
		bossPosition += Vector2(800, -200)*Time::GetInstance().deltaTime();
	}
	//～5秒の間はプレイヤーを画面に登場させる
	else if (mIvemtTime <= 5) {
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody1").get())->ForcedMove(Vector2(400, 0.0f));
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody2").get())->ForcedMove(Vector2(400.0f, 0.0f));
	}
	//～9秒の間はプレイヤーを停止させる
	else if (mIvemtTime <= 9.f) {
	}
	//～11秒の間はプレイヤーを画面外に出す
	else if (mIvemtTime <= 11.0f) {
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody1").get())->ForcedMove(Vector2(-400, 0.0f));
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody2").get())->ForcedMove(Vector2(-400.0f, 0.0f));
	}
	//～12秒の間はボスの向きを回転させる
	else if (mIvemtTime <= 12.0f) {
		anmer_.Turn();
	}
	//～15秒の間はボスを画面外に出す
	else if(mIvemtTime <= 15.0f) {
		bossPosition -= Vector2(1200, -300)*Time::GetInstance().deltaTime();
	}
	//全ての工程が終了したら、シーンを終了する
	else {
		isEnd_ = true;
	}
	
	//World(プレイヤー)の更新を行う
	world_->update(Time::GetInstance().deltaTime());
}

void StageClearScene::draw() const {
	//World(プレイヤー)の描画
	world_->draw();

	//ボスの描画
	anmer_.draw_e(bossPosition);
}

void StageClearScene::end() {
}

bool StageClearScene::isEnd() const {
	return isEnd_;
}

Scene StageClearScene::next() const {
	return nextScene;
}
