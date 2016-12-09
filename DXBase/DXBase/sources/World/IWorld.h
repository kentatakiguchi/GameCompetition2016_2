#ifndef IWORLD_H_
#define IWORLD_H_

#include "../Actor/Base/Actor.h"
#include "../Field/FieldPtr.h"
#include <string>
#include <vector>
enum class ActorGroup;
enum class EventMessage;

// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	//UIアクターの追加
	virtual void addUIActor(const ActorUIPtr& actor) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// フィールドの取得
	virtual FieldPtr getField() const = 0;
	virtual unsigned int fieldHandle() const = 0;
	//アクターの検索(list返し)
	virtual std::forward_list<ActorPtr> findActors(const ActorGroup group) = 0;
	virtual Vector2 MoveActor() = 0;
	virtual Vector2 ScroolStopFlag() = 0;
	virtual bool is_clear() = 0;
	virtual void clear(bool clear) = 0;

	//縦スクロール横スクロールするかどうか(引数 軸ごとにスクロールする場合は1、しない場合は0)
	virtual void SetScroolJudge(Vector2 scrool=Vector2(1,1))=0;
	virtual Vector2 GetScroolJudge()=0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
};

#endif
