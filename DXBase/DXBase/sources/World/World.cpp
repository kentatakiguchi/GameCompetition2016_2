#include "World.h"
#include "../Field/Field.h"
#include "../Actor/TestPlayer/TestPlayer.h"
#include "../Actor/Person/Player/Player.h"
#include "../Actor/ScroolStop/ScroolStop.h"
#include"../Actor/Person/Player/PlayerBody.h"
// コンストラクタ
World::World() :
	listener_([](EventMessage, void*) {}),
	is_clear_(false),
	mNoPlayerMove(false){
}

// 更新
void World::update(float deltaTime) {
	//field_->update(deltaTime);
	actors_.update(deltaTime);


	//camera_->update(deltaTime);
	//light_->update(deltaTime);
}

// 描画
void World::draw() const {
	//field_->draw();
	//camera_->draw();
	//light_->draw();
	actors_.draw();
}

// メッセージ処理
void World::handleMessage(EventMessage message, void* param) {
	// ワールドのメッセージ処理
	listener_(message, param);
	// アクターのメッセージ処理
	actors_.handleMessage(message, param);
	//camera_->handleMessage(message, param);
	//light_->handleMessage(message, param);
}

// フィールドの追加
void World::addField(const FieldPtr& field) {
	field_ = field;
}

// カメラの追加
void World::addCamera(const ActorPtr& camera) {
	camera_ = camera;
}

// ライトの追加
void World::addLight(const ActorPtr& light) {
	light_ = light;
}

// アクターの追加
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

void World::addUIActor(const ActorUIPtr & actor)
{
	actors_.addUIActor(actor);
}
// アクターの検索
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}
//アクター検索(list返し)
std::forward_list<ActorPtr> World::findActors(const ActorGroup group)
{
	return actors_.GetActors(group);
}

// フィールドの取得
FieldPtr World::getField() const {
	return field_;
}


unsigned int World::fieldHandle() const {
	return field_->modelHandle();
}

// メッセージの送信
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// イベントリスナーの追加
void World::addEventMessageListener(
	std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

bool World::is_clear(){
	return is_clear_;
}

void World::clear(bool clear){
	is_clear_ = clear;
}

void World::SetScroolJudge(Vector2 scroolJudge, Vector2 scroolStopPos)
{
	scrool_.scroolJudge = scroolJudge;
	scrool_.scroolStop = scroolStopPos;
}

ScroolJudge World::GetScroolJudge()
{
	return scrool_;
}


