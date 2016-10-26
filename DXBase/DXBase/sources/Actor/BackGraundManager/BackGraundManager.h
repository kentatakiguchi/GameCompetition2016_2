#pragma once
#include "../../ResourceLoader/ResourceLoader.h"
#include <list>
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
class TestPlayer;

struct BackGraundState
{
	//テクスチャid
	int id = 0;
	//テクスチャサイズ
	Vector2 size = Vector2::Zero;
	//2つ画像を張るための座標
	std::list<Vector2> positions;
};

class BackGraundManager
{
public:
	BackGraundManager(IWorld* world);
	~BackGraundManager();
	//背景を設定する（ロードしたテクスチャ限定）
	void SetBackGraund(TextureID id);
	//背景（空）を設定する（ロードしたテクスチャ限定）
	void SetUpBackGraund(TextureID id);
	//地面を設定する(ロードしたテクスチャ限定)
	void SetDownBackGraund(TextureID id);
	//背景を全部消す
	void AllDeleteBackGraund();
	void Update(float deltatime);
	void Draw() const;

private:
	//ワールド
	IWorld* mWorld;
	//プレイヤー
	TestPlayer* mPlayer;
	//地上の背景
	std::list<BackGraundState> backStates;
	//空の背景
	BackGraundState upBackStates;
	//地面の背景
	BackGraundState downBackStates;
	//補正関係
	Vector3 restPos;
	Vector3 velo;
};