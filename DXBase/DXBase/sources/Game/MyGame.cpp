#include "MyGame.h"
#include "Time.h"
#include "../Input/InputMgr.h"

#include "../Define.h"

#include "../Scene/LoadingScene/LoadingScene.h"
#include "../Scene/Title/TitleScene.h"
#include "../Scene/GamePlay/GamePlayScene.h"
#include "../Scene/GameOver/GameOverScene.h"
#include "../Scene/KataokaScene/KataokaScene.h"
#include "../Scene/StageClear/StageClearScene.h"
#include "../Scene/GameClear/GameClearScene.h"
#include "../Scene/BossStage/BossStage.h"
#include "../Scene/SampleBossScene/SampleBossScene.h"
#include"../Scene/MainMenu/MainMenuScene.h"
#include"../Scene/Credit/CreditScene.h"
#include"../Scene/TeamLogoScene/TeamLogoScene.h"
#include"../Scene/Test/TestScene.h"
#include"../Scene/GameEnd/GameEndScene.h"
#include "../Scene/Tutoreal/TutorealScene.h"

MyGame::MyGame() : 
	Game(WINDOW_NAME, static_cast<int>(SCREEN_SIZE.x), static_cast<int>(SCREEN_SIZE.y), WINDOW_RATE, WINDOW_MODE),
	dataKeeper_(), 
	sceneMgr_(&dataKeeper_){
}

MyGame::~MyGame(){
}

void MyGame::start(){
	////背景色の設定
	//SetBackgroundColor(0, 0, 255);

	//gameDevice_.start();

	sceneMgr_.add(Scene::Loading, std::make_shared<LoadingScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Title, std::make_shared<TitleScene>(&dataKeeper_));
	sceneMgr_.add(Scene::MainMenu, std::make_shared<MainMenuScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GamePlay, std::make_shared<GamePlayScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GameOver, std::make_shared<GameOverScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GameClear, std::make_shared<GameClearScene>(&dataKeeper_));
	sceneMgr_.add(Scene::StageClear, std::make_shared<StageClearScene>(&dataKeeper_));
	sceneMgr_.add(Scene::BossStage01, std::make_shared<BossStage>(&dataKeeper_));
	sceneMgr_.add(Scene::Kataoka, std::make_shared<KataokaScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Credit, std::make_shared<CreditScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GameEnd, std::make_shared<GameEndScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Logo, std::make_shared<TeamLogoScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Test, std::make_shared<TestScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Tutoreal, std::make_shared<TutorealScene>());
	sceneMgr_.change(Scene::Loading);

	//前のゲームプレイシーンの内容を保存する専用のクラスを作る(ステージ番号、キャラクター情報等を保存)
	//ここにインスタンス化して、現在動いているゲームプレイのデータを、遷移(Updateまたはエンド)するタイミングで送るシーン内だとデータが消えてしまうから
	//3ステージ分の切り分けが読み込めるようにする、とりあえずゲームプレイシーンのみ
	//ゲームプレイシーンは使いまわしする、csvの切り替えによって、ステージを変更する(初期化で、オブジェクト位置等のみ再設定する)
	//デバッグ用に、直接好きなステージに飛べるコマンドを作る(ボタンは余っている好きな物で良い)
	//各シーンには、データ保存用クラスのポインタを渡す
}

void MyGame::update(){
	Time::GetInstance().update();
	InputMgr::GetInstance().GetHitKeyFrameAll();

	sceneMgr_.update();
}

void MyGame::draw(){
	sceneMgr_.draw();

	Time::GetInstance().draw_fps();
}

void MyGame::end(){
	sceneMgr_.end();
}