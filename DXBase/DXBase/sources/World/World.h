#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>

enum class EventMessage;

class World : public IWorld {
public:
	// コンストラクタ
	World();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	// フィールドの追加
	void addField(const FieldPtr& field);
	// カメラの追加
	void addCamera(const ActorPtr& camera);
	// ライトの追加
	void addLight(const ActorPtr& light);

	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) override;
	// フィールドの取得
	virtual FieldPtr getField() const override;
	virtual unsigned int fieldHandle() const override;

	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// イベントリスナーの追加
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);

	//速度
	virtual Vector2 MoveActor() override;
	//unsigned int fieldHandle();

	// コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	// アクターマネージャー
	ActorManager	actors_;
	// ライト
	ActorPtr		light_;
	// カメラ
	ActorPtr		camera_;
	// フィールド
	FieldPtr		field_;
	// イベントリスナー
	std::function<void(EventMessage, void*)> listener_;
};

#endif

