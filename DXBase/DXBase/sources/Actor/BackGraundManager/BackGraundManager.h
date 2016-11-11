#pragma once
#include "../../ResourceLoader/ResourceLoader.h"
#include <list>
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
class TestPlayer;
class Player;

struct BackGraundState
{
	//テクスチャid
	int id = 0;
	//テクスチャサイズ
	Vector2 size = Vector2::Zero;
	//2つ画像を張るための座標
	std::list<Vector2> positions;
	//補正関係
	Vector2 resVelo = Vector2::Zero;
	Vector2 springVelo = Vector2::Zero;
	Vector2 velocity = Vector2::Zero;
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

	//バネ
	void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness=0.05f, float friction=0.5f, float mass=2.0f);

private:
	//ワールド
	IWorld* mWorld;
	//プレイヤー
	Player* mPlayer;
	//地上が表示されているか？
	bool stageFlag;
	//地上の背景
	std::list<BackGraundState> backStates;
	//空の背景
	BackGraundState upBackStates;
	//地面の背景
	BackGraundState downBackStates;
	//補正関係
	Vector2 restPos;
	Vector2 velo;
};