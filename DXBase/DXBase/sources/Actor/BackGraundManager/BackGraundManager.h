#pragma once
#include "../../ResourceLoader/ResourceLoader.h"
#include <list>
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
#include "../../Field/MovelessFloor.h"
class TestPlayer;
class Player;

struct IndexPos 
{
	int index;
	Vector2 position;
};

struct BackGraundState
{
	//テクスチャid
	int id = 0;
	//Actorの前に表示するか
	bool frontGraundFlag=false;
	//テクスチャサイズ
	Vector2 size = Vector2::Zero;
	//2つ画像を張るための座標
	std::list<IndexPos> indexPos;
	//レイヤー
	int layer;
	//stage2か
	bool stage2;

};

class BackGraundManager
{
public:
	BackGraundManager(IWorld* world);
	BackGraundManager();
	~BackGraundManager();
	//背景を設定する（ロードしたテクスチャ限定）
	void SetBackGraund(TextureID id1,TextureID id2,float heightY=0.0f,bool frontGraund=false,bool stage2=false);
	//縦の背景を設定する（ロードしたテクスチャ限定）
	void SetTateBackGraund(TextureID id1, TextureID id2);
	//縦の横の背景を設定する(ロードしたテクスチャ限定)
	void SetTateYokoBackGraund(TextureID id1);
	//背景（空）を設定する（ロードしたテクスチャ限定）
	void SetUpBackGraund(TextureID id,int layer);
	//地面を設定する(ロードしたテクスチャ限定)
	void SetDownBackGraund(TextureID id);


	//背景を全部消す
	void AllDeleteBackGraund();
	//横用スクロールUpdate
	void Update(float deltatime, bool title = false);
	//縦用スクロールUpdate
	void TateUpdate(float deltaTime);

	void Draw() const;

	void BackDraw()const;

	//バネ
	void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness=0.05f, float friction=0.5f, float mass=2.0f);

private:
	//ワールド
	IWorld* mWorld;
	//ブロック
	Player* mFloor;
	//地上が表示されているか？
	bool stageFlag;
	//地上の背景
	std::list<BackGraundState> backStates;
	//空の背景
	std::list<BackGraundState> upBackStates;
	//地面の背景
	BackGraundState downBackStates;
	//縦スクロールの横の背景
	BackGraundState tateYokoState;
};