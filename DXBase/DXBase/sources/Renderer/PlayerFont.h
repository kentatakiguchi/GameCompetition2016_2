#pragma once

#include "../Math/Vector2.h"
#include "../World/IWorld.h"
#include "PlayerTxt.h"
#include "../Math/MathHelper.h"
#include <memory>
#include <map>
#include "../Actor/Base/Actor.h"
enum TxtEvent
{
	ONE_EVENT,
	TWO_EVENT,
	SURI_EVENT
};
class PlayerFont {

public:

	typedef std::shared_ptr<PlayerTxt> PlayerTxtPtr;
public:
	PlayerFont(IWorld* world, const Vector2& pos);
	~PlayerFont();
	void Update();
	void Draw();
public:
	//フォントをスタートする
	void StartFont();
	//フォントをチェンジ
	void ChangeFont(TxtEvent txtEvent);
	//イベントを追加する 引数: イベントID　イベントのテキストファイルパス ファイルの改行数
	void AddEvent(TxtEvent txtEvent, char* txtFile, int lineNum);
private:

	IWorld* world_;
	//
	Actor* playerB;
	Actor* playerR;
	//プレイヤーの座標
	Vector2 playerPosB;
	Vector2 playerPosR;
	//吹き出しの座標を入れます
	Vector2 fontPosB_;
	Vector2 fontPosR_;

	std::map<TxtEvent, PlayerTxtPtr> eventFonts_;

	//現在しているイベント
	TxtEvent nowEvent_;

	bool isPlayFont_;
	float alphaB_;
	float alphaR_;

	Vector2 textSize_;

};