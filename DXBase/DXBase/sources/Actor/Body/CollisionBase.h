#pragma once

#include"BoundingBox.h"
#include"BoundingCapsule.h"
enum CollisionType
{
	BoxCol,
	CapsuleCol,
	NoneCol
};
class CollisionBase
{

public:
	//判定を利用しない場合
	CollisionBase();
	//四角判定を利用する場合
	CollisionBase(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//カプセル判定を利用する場合
	CollisionBase(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//デバッグ用の判定表示
	void draw() const;
	//四角判定の大きさ、形状の変更
	void transform(Vector2& topLeft, Vector2& topRight, Vector2& bottomLeft, Vector2& bottomRight);
	//カプセル判定の大きさ、形状の変更
	void transoform(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//判定の移動
	void translate(Vector2 position);
	//対象と当たっているか  other:判定したい相手(CollisionBase) return:判定結果(bool)
	bool intersects(CollisionBase& other);
	//どの種類の当たり判定を利用しているかを取得 return:判定の種類(CollisionType)
	CollisionType GetType() const;
	//四角判定を取得/四角判定以外を利用している場合、動作しない四角判定を返す return:自身の四角判定(BoundingBox)
	BoundingBox GetBox() const;
	//カプセル判定を取得/カプセル判定以外を利用している場合、動作しないカプセル判定を返す return:自身のカプセル判定(BoundingBox)
	BoundingCapsule GetCapsule() const;
	//判定を利用するかどうかを変更する
	void enabled(bool change);
private:
	//利用している判定の種類
	CollisionType type_;
	//四角判定
	BoundingBox box_;
	//カプセル判定
	BoundingCapsule capsule_;
};