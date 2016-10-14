#pragma once

#include "../../Math/Math.h"
#include "Body.h"


class BoundingBox : public Body {
public:
	//四角の判定を作成する(判定を行う場合) topLeft:左上の点(Vector2) topRight:右上の点(Vector2) bottomLeft:左下の点(Vector2) bottomRight:右下の点(Vector2)
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//四角の判定を作成する(判定を行うかどうかを指定する場合) (trueなら行い、falseなら行わない) topLeft:左上の点(Vector2) topRight:右上の点(Vector2) bottomLeft:左下の点(Vector2) bottomRight:右下の点(Vector2) isEnabled:判定をするかどうか(bool)
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight,bool isEnabled);
	//四角の判定を作成する(判定を行わない場合)
	explicit BoundingBox();
	//使用しない
	virtual bool intersects(BoundingSphere& other) override { return false; }
	//使用しない
	virtual bool intersects(Capsule& other) override { return false; }
	//使用しない
	virtual bool intersects(Model& other) override { return false; }
	// 自身(Box)と相手(Box)の判定 other:判定したい相手(BoundingBox) return:判定結果(bool)
	virtual bool intersects(BoundingBox & other) override;
	// 自身(Box)と相手(Capsule)の判定 other:判定したい相手(BoundingCapsule) return:判定結果(bool)
	virtual bool intersects(BoundingCapsule & other) override;
	//自身の判定の更新を行う(現在未使用)
	virtual void update(const Vector2 & center) override;
	//使用しない
	virtual void update(const Vector3& center) override {}
	//使用しない
	virtual void debug() const override;
	//判定の表示(デバッグ用)
	virtual void draw() const override;
	//自身(Box)を移動する position:移動量(Vector2) return:移動した結果(BoundingBox)
	BoundingBox translate(const Vector2& position) const;
	//自身(Box)を変形する topLeft:左上の点(Vector2) topRight:右上の点(Vector2) bottomLeft:左下の点(Vector2) bottomRight:右下の点(Vector2) return:変形した結果(BoundingBox)
	BoundingBox transform(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight) const;
private:
	//自身(Box)の直線と相手(Capsule)の線分が当たっているかを調べる、pointはComponentの物を利用する other:相手の判定(BoundingCapsule) point1:自身のどの点を始点とするか(int) point2:自身のどの点を終点とするか(int)
	bool isIntersectOtherRayToThisLine(BoundingCapsule & other, int point1, int point2);
	//自身(Box)の線分と相手(Capsule)の直線が当たっているかを調べる、pointはComponentの物を利用する other:相手の判定(BoundingCapsule) point1:自身のどの点を始点とするか(int) point2:自身のどの点を終点とするか(int)
	bool isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2);



public:
	struct Component {
		// [0]:左上 [1]:右上 [2]:左下 [3]:右下
		Vector2 point[4];

		Component(Vector2 topLeft, Vector2 topRight, Vector2 bottomLeft, Vector2 bottomRight) {
			point[0] = topLeft;
			point[1] = topRight;
			point[2] = bottomLeft;
			point[3] = bottomRight;

		}
	};
	//四角を生成するための4点を保存する
	Component component_;

	//intersectsを使うかどうか true:判定する false:判定しない
	bool enabled;


};

