#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>
#include <vector>
#include "../Actor/Base/ActorGroup.h"
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
	//UIアクターの追加
	virtual void addUIActor(const ActorUIPtr& actor) override;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) override;
	//アクターの検索(list返し)
	virtual std::forward_list<ActorPtr>findActors(const ActorGroup group) override;
	// フィールドの取得
	virtual FieldPtr getField() const override;
	virtual unsigned int fieldHandle() const override;

	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// イベントリスナーの追加
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);
	//クリア条件
	virtual bool is_clear()override;
	virtual void clear(bool clear)override;
	virtual void SetScroolJudge(Vector2 scroolJudge,Vector2 scroolStopPos) override;
	virtual ScroolJudge GetScroolJudge()override;
	virtual void PlayerNotMove(bool flag) override {
		mNoPlayerMove = flag;
	}
	virtual bool GetPlayerNotMove() override {
		return mNoPlayerMove;
	}
	virtual Matrix GetInv()override {
		Matrix mat;
		mat.Translation(Vector3(mPlayerPos.x, mPlayerPos.y,0.0f));
		return Matrix::Invert(mat) *
			Matrix::CreateTranslation(Vector3(PLAYER_SCREEN_POSITION.x, PLAYER_SCREEN_POSITION.y));
	}
	virtual void SetPlayerPos(Vector2 pos) override
	{
		mPlayerPos = pos;
	}
	virtual Vector2 GetPlayerPos() override
	{
		return mPlayerPos;
	}

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

	bool is_clear_;

	ScroolJudge scrool_;
	
	Vector2 mPlayerPos;
	
	bool mNoPlayerMove;
};

#endif

