#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../Actor/Camera/Camera.h"
#include "../../Actor/Light/Light.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/Enemy.h"
#include "../../Actor/Person/Enemy/EnemySpawner.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/Person/Player/TestColl.h"
#include "../../Field/MapGenerator.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include "../../Actor/TestPlayer/TestPlayer.h"
#include <memory>
#include <random>

const Vector3 START_POS = Vector3(800/2, 600/2, 0);

GamePlayScene::GamePlayScene() : 
	id(0){
	isEnd_ = false;
}

GamePlayScene::~GamePlayScene(){

}

void GamePlayScene::start() {
	vector.x = 200;
	vector.y = 200;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addCamera(std::make_shared<Camera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), Vector3(10.0f, 10.0f, 10.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), START_POS));
	
	MapGenerator gener = MapGenerator(world_.get());
	gener.create("test.csv");

	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 0, 400, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 1, 400, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 2, 400, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 3, 400, 0)));
	//
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 6, 400, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 6, 300, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 6, 200, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<TestColl>(world_.get(), Vector3(100 * 6, 100, 0)));
	//world_->addActor(ActorGroup::Enemy_Spawner, std::make_shared<EnemySpawner>(world_.get(), "./resources/file/test.csv"));

	//for (int i = 0; i < 10; i++) {
	//	world_->addActor(ActorGroup::Enemy, std::make_shared<Enemy>(world_.get(), Vector3::Zero));
	//}

	status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);


	texHandle = LoadGraph("resources/sprite/001.jpg");
	//GetGraphSize(texHandle, &size_x, &size_y);

	////分割した際の個々の画像サイズ
	//div_size_ = Vector2(size_x / row_, size_y / column_);

	////配列の確保
	//sprites_ = std::vector<std::vector<int>>(column_, std::vector<int>(row_));
	////分割後のidを格納
	//for (int i = 0; i < column_; ++i) {
	//	for (int j = 0; j < row_; ++j) {
	//		float src_x = size_x / row_ * j;
	//		float src_y = size_y / column_ * i;
	//		sprites_[i][j] = DerivationGraph(src_x, src_y, div_size_.x, div_size_.y, texHandle);
	//	}
	//}

	//vib_center_ = div_size_ * 2;

	//position_.x = div_size_.x * 4;
	//position_.y = div_size_.y * 2;

	//velocity_ = Vector2::Zero;
	//accelarate_ = Vector2::Zero;

	//natural_length_ = div_size_.x * 2;


	//spring_constant_ = 10.0f;
	//attenuation_constant_ = 0.5f;
	//mass_ = 0.3f;
	//angular_freq_ = std::sqrtf(spring_constant_ / mass_);
	//p_ = attenuation_constant_ / 2 / mass_;
	//e_ = 2.7f;
	//time_ = 0;

	//amplitude_ = div_size_.x * 3;

	//phase_ = position_;

	//puyo_ = Puyo_Texture(texHandle, 10, 10);
}

void GamePlayScene::update() {
	world_->update(Time::GetInstance().deltaTime());
	backManager->Update(Time::GetInstance().deltaTime());
	time_ += Time::GetInstance().deltaTime();


	//position_.x = div_size_.x * 4 + velocity_.x;
	//position_.y = div_size_.y * 2 + velocity_.y;
	//velocity_.x = amplitude_ * angular_freq_ * std::cos(angular_freq_ * time_ + phase_.x);
	//velocity_.y = amplitude_ * angular_freq_ * std::cos(angular_freq_ * time_ + phase_.y);


	//position_.x = div_size_.x * 4 + amplitude_ * std::pow(e_ ,-p_ * time_) * std::sin(angular_freq_ * time_ + phase_.x);
	//position_.y = div_size_.y * 2 + amplitude_ * std::pow(e_, -p_ * time_) * std::sin(angular_freq_ * time_ + phase_.y);


	//position_.x += velocity_.x * time_;
	////position_y_ += velocity_y_ * time_;

	//velocity_.x += accelarate_.x * time_;
	////velocity_y_ += accelarate_y_ * time_;

	//accelarate_.x = -spring_constant_ * ((position_.x - vib_center_.x) - natural_length_);
	////accelarate_y_ = 0;

	//DrawGraph(position_.x, position_.y, sprites_[2][2], FALSE);
	////DrawGraph(vib_center_.x, vib_center_.y, sprites_[2][2], FALSE);

	//DrawFormatString(550, 150, GetColor(255, 255, 255), "%d, %d", (int)position_.x, (int)position_.y);


	//puyo_.calc_acc();
	//puyo_.calc_pos();

	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE)) puyo_.trans_node_pos();
	
	//DrawFormatString(550, 150, GetColor(255, 255, 255), "%d, %d", (int)(puyo_.get_node_data(3, 3).get_pos().x), (int)(puyo_.get_node_data(3, 3).get_pos().y));
	//DrawFormatString(550, 175, GetColor(255, 255, 255), "%d, %d", (int)(puyo_.get_node_data(3, 3).get_acc().x), (int)(puyo_.get_node_data(3, 3).get_acc().y));
	//DrawFormatString(550, 200, GetColor(255, 255, 255), "%d, %d", (int)(puyo_.get_node_data(2, 2).get_acc().x), (int)(puyo_.get_node_data(2, 2).get_acc().y));

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void GamePlayScene::draw() const {
	backManager->Draw();
	//world描画
	world_->draw();

	//puyo_.draw();

	DrawFormatString(550, 25, GetColor(255, 255, 255), "キャラ移動：方向キー");
	DrawFormatString(550, 50, GetColor(255, 255, 255), "カメラ回転：WASDキー");
	DrawFormatString(550, 75, GetColor(255, 255, 255), "ジャンプ：SPACEキー");
	DrawFormatString(550, 100, GetColor(255, 255, 255), "攻撃1：Zキー");
	DrawFormatString(550, 125, GetColor(255, 255, 255), "攻撃2：Xキー");

	DrawFormatString(550, 550, GetColor(255, 255, 255), "ENTERボタンでリザルトへ");



}

void GamePlayScene::end() {

}

bool GamePlayScene::isEnd() const {
	return isEnd_;
}

Scene GamePlayScene::next() const {
	return Scene::GameOver;
}

