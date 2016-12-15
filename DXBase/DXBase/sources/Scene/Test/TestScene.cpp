#include "TestScene.h"
#include"../../Scene/Test/TestChara.h"
#include"../../Field/TurnFloor.h"

TestScene::TestScene(SceneDataKeeper* keeper) :
	id(0)// a(nullptr, "a", Vector2(200, 200), CollisionBase(Vector2( 150,150 ),30.f)), b(nullptr, "a", { 300, 200 }, CollisionBase({ 250,150 }, { 350,150 }, { 250,250 }, { 350,250 })),
	//circle_(Vector2(50, 50), 30), circle2_(Vector2(150, 150), 30.0f), segment_({ 200,200 }, { 400,200 }), segment2_({ 200,200 }, { 400,200 }), box_({ 100,100 }, { 150,100 }, { 100,150 }, { 150,150 }), box2_({ 100,150 }, { 150,100 }, { 150,200 }, { 200,150 }), capsule_({ 250,400 }, { 200, 250 }, 30), capsule2_({ 200,250 }, { 100,350 }, 30)
{
	keeper_ = keeper;

	isEnd_ = false;
}

TestScene::~TestScene() {

}

void TestScene::start() {
	isEnd_ = false;

	world_ = std::make_shared<World>();

	id = static_cast<int>(segment2_.getLength());
	MapGenerator gener = MapGenerator(world_.get());
	gener.create("test.csv");
	world_->addActor(ActorGroup::Player, std::make_shared<TestChara>(world_.get(),Vector2(0,0)));
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	//// グラフィックのロード
	//id = LoadGraph("./resources/Player.png");

}

void TestScene::update() {
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT))
	//{
	//	a.position_+=Vector3( 10,0,0);
	//	//box_ = box_.translate({ 10,0 });
	//}
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT))
	//{
	//	a.position_+= Vector3(-10, 0, 0);
	////	box_ = box_.translate({ -10,0 });
	//}
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::UP))
	//{
	//	a.position_ += Vector3(0,-10, 0);
	//	//box_ = box_.translate({ 0,-10 });
	//}
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::DOWN))
	//{
	//	a.position_+= Vector3(0, 10, 0);
	//	//		box_ = box_.translate({ 0,10 });
	//}
	world_->update(1);
	DrawFormatString(static_cast<int>(a.position_.x), static_cast<int>(a.position_.y), GetColor(255, 255, 255), "a");
	DrawFormatString(static_cast<int>(b.position_.x), static_cast<int>(b.position_.y), GetColor(255, 255, 255), "b");
	//if (a.isCollide(b))
	//{
	//	DrawFormatString(250, 100, GetColor(255, 255, 255), "deta");
	//}
}

void TestScene::draw() const {

	a.draw();
	b.draw();

	world_->draw();
	//if (isEnd_)DrawGraph(250, 500, id, TRUE);

	//DrawFormatString(375, 200, GetColor(255, 255, 255), "タイトル");
	//DrawFormatString(300, 500, GetColor(255, 255, 255), "SPACEボタンでゲームスタート");
}

void TestScene::end() {

}

bool TestScene::isEnd()const {
	return isEnd_;
}

Scene TestScene::next() const {
	return Scene::GamePlay;
}
