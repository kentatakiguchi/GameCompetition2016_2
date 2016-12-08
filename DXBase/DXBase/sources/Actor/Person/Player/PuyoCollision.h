#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include <vector>
//ぷよテクスチャのあたり判定があるところ
class PuyoCollision : public Actor {
public:
	PuyoCollision(IWorld* world, Vector2& position,Vector2 arrayState,Vector2 &center);
	~PuyoCollision();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
public:
	//逆行列かけていないポジションを
	void SetPos(Vector2 pos,Vector2 center) {
		position_ = pos*Matrix::Invert(inv_);
		mCenter = center;
	}
	//どの2次元配列にいるか取得
	Vector2 GetArrayState() {
		return mArrayState;
	}
	Vector2 GetVec() {
		return mVec;
	}
private:
	//線と線のあたり判定と交点を求める
	bool SegmentCol(Vector2 A, Vector2 B, Vector2 C, Vector2 D,Vector2 & couten,bool rightLeft);
private:
	//本来の位置と交点のベクトル
	Vector2 mVec;
	//最終的な交点
	Vector2 mIntersection;
	//2次元配列のどこか
	Vector2 mArrayState;
	//ぷよテクスチャの中心
	Vector2 mCenter;
	//バネ補間関係
	Vector2 mResIntersection;
	Vector2 mVelo;
	//ステージと当たっているか
	bool mIsCol;
	//交点たち
	Vector2 mIntersections[4];
	//最終的な交点たち
	std::vector<Vector2> mIntersectionsVector;


	bool top;
	bool right;
	bool bot;
	bool left;
};

