#pragma once
#include <vector>
#include "../ResourceLoader/ResourceLoader.h"
#include "../Math/Vector2.h"
#include "../Math/Matrix.h"
const Vector2 texSize = ResourceLoader::GetInstance().GetTextureSize(TextureID::PUYO_TEST_TEX);
const int SplitSize = 8.0f;
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
	float amplitude = 0.0f;				           //振幅
	float time=0.0f;						       //経過時間
	float vibrationTime = 0.0f;                    //振動するまでの時間
	float vibrationTimer = 0.0f;                   //振動するまでのカウント
	Vector2 position=Vector2::Zero;		           //振動する中心座標
	Vector2 velocity = Vector2(1, 1);              //振動している方向と大きさ

};


class PuyoTextureK {
public:
	PuyoTextureK(TextureID tex,Vector2 pos,Vector2 scale,float rotate);
	~PuyoTextureK();
	//情報をセット
	void SetPosition(Vector2 pos, Vector2 scale, float rotate);
	//力を加える頂点(xとyは2次元配列に入っている頂点の座標,velocityは揺らす方向と大きさ)
	void PuyoAddPower(int x, int y,Vector2 velocity);
	void PuyoUpdate();
	void PuyoDraw();
private:
	void PuyoGraphSplit();
	void PuyoGraphVertex();
	void PuyoVertexSet();
private:
	//頂点情報
	VertexPos  spriteVertexH[16][16];
	//インデックス情報
	int  spriteIndexsH[16][16];
	//共通の頂点情報
	SpringState commonVertexH[17][17];
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


	//test
	Vector2 test;
	float time;
	//バネ関係
	Vector2 vib_center_;	//振動中心
	float angular_freq_;				//角振動数
	Vector2 phase_;						//位相
	float spring_constant_;				//ばね定数
	float attenuation_constant_;		//減衰定数
	float mass_;						//質量
	float p_;						//質量
	float e_;						//質量

};