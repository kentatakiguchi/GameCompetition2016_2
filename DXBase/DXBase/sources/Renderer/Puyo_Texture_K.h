#pragma once
#include <vector>
#include "../ResourceLoader/ResourceLoader.h"
#include "../Math/Vector2.h"
#include "../Math/Matrix.h"

struct VertexPos {
	//左上
	Vector2 LeftTopPos=Vector2::Zero;
	//左下
	Vector2 LeftDownPos = Vector2::Zero;
	//右上
	Vector2 RightTopPos = Vector2::Zero;
	//右下
	Vector2 RightDownPos = Vector2::Zero;
};
struct SpringState {
	float veloNum=0.0f;                                 //補間用バネ
	float resNum=0.0f;                                  //補間用現在
	float num = 0.0f;
	float power = 0.0f;                            //加える力
	float maxPower = 0.0f;
	float time=0.0f;						       //経過時間
	float vibrationTime = 0.0f;                    //振動するまでの時間
	float vibrationTimer = 0.0f;                   //振動するまでのカウント
	Vector2 position=Vector2::Zero;		           //振動する中心座標
	Vector2 velocity = Vector2(1, 1);              //振動している方向と大きさ
	bool PowerFlag = true;                         //振動してる種類フラグ

};


class PuyoTextureK {
public:
	//揺らすテクスチャIDと座標と大きさと回転
	PuyoTextureK(TextureID tex,Vector2 pos,Vector2 scale,float rotate);
	~PuyoTextureK();
	//座標とスケールと回転をセットする
	void SetPosition(Vector2 pos, Vector2 scale, float rotate);
	//力を加える頂点(pos:テクスチャから見た力を加える座標,velo:揺らす方向と大きさ)
	void PuyoAddPower(Vector2 pos,Vector2 velo);
	//力を加え続ける頂点（周りににも）(pos:テクスチャから見た力を加える座標,velo:揺らす方向と大きさ)※毎フレーム呼ぶこと
	void PuyoAddPowerDx(Vector2 pos, Vector2 velo);
	void PuyoUpdate();
	void PuyoDraw();
private:
	void PuyoGraphSplit();
	void PuyoGraphVertex();
	void PuyoVertexSet();
	void PuyoVertexSetInit();

private:

	//頂点情報
	VertexPos  spriteVertexH[32][32];
	//インデックス情報
	int  spriteIndexsH[32][32];
	//共通の頂点情報
	SpringState commonVertexH[32][32];
	//共通の頂点情報（移動しないよ）
	SpringState commonVertexHNoMove[32][32];
	//元のテクスチャ情報
	int textureIndex;
	//元のテクスチャサイズ
	Vector2 textureSize;
	//ループ関係
	int loopX;
	int loopY;
	//画像の座標
	Vector2 mPosition;
	//画像のスケール
	Vector2 mScale;
	//画像の回転
	float mRotate;


	float time;

	float tesNum;
	Vector2 test;
	float tesTimer;
	float testVelo;
	float testRes;

};