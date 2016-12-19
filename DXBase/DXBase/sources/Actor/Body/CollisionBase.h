#pragma once

#include"BoundingBox.h"
#include"BoundingCapsule.h"
#include"BoundingCircle.h"
#include"BoundingSegment.h"

class CollisionBase
{

public:
	//判定を利用しない場合
	CollisionBase();
	//四角判定を利用する場合
	CollisionBase(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//カプセル判定を利用する場合
	CollisionBase(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//円判定を利用する場合
	CollisionBase(Vector2& center, float circleRadius);
	//線分判定を利用する場合
	explicit CollisionBase(Vector2& startPoint, Vector2& endPoint);
	void setPosition(Vector2 position);
	Vector2 setSegmentPoint(Vector2& position, Vector2& startPoint, Vector2& endPoint);
	void RotateCapsule(Vector2 point1, Vector2 point2, float radius);
	void RotateSegment(Vector2 point1, Vector2 point2);
	void RotateBox(int rotation);
	void RotateFreeBox(int rotation);
	//デバッグ用の判定表示
	void draw(Matrix inv = Matrix::Identity) const;
	//スプライトのIDを渡す事で、対応したスプライトを表示する各判定のdrawを呼び出す(BOX以外は通常のdrawと同じ)
	void draw(int spriteID, Matrix inv = Matrix::Identity) const;
	void draw(int spriteID, int rotation, Matrix inv = Matrix::Identity) const;
	//
	void update(Vector2 position);
	//四角判定の大きさ、形状の変更
	void transform(Vector2& topLeft, Vector2& topRight, Vector2& bottomLeft, Vector2& bottomRight);
	//カプセル判定の大きさ、形状の変更
	void transform(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//円判定の大きさ、形状の変更
	void transform(Vector2& center, float circleRadius);
	//線分判定の大きさ、形状を変更
	void transform(Vector2& startPoint, Vector2& endPoint);
	//判定の移動(自身のポジションを参照)
	void MovePos(Vector2 & position);
	//判定の移動
	void translate(Vector2 position);
	//対象と当たっているか  other:判定したい相手(CollisionBase) return:判定結果(bool)
	bool intersects(CollisionBase& other);
	//どの種類の当たり判定を利用しているかを取得 return:判定の種類(CollisionType)
	CollisionType GetType() const;
	//四角判定を取得/四角判定以外を利用している場合、動作しない四角判定を返す return:自身の四角判定(BoundingBox)
	CollisionBase GetBox() const;
	//カプセル判定を取得/カプセル判定以外を利用している場合、動作しないカプセル判定を返す return:自身のカプセル判定(BoundingCapsule)
	CollisionBase GetCapsule() const;
	//円判定を取得/円判定以外を利用している場合、動作しない円判定を返す return:自身の円判定(BoundingCircle)
	CollisionBase GetCircle() const;
	//線分判定を取得/線分判定以外を利用している場合、動作しない線分判定を返す return:自身の線分判定(BoundingSegment)
	CollisionBase GetSegment() const;
	float getRadius() {
		return radius_;
	}
	float getWidth() {
		return 0;
	}
	float getHeight() {
		return 0;
	}
	float getSize() {
		return 0;
	}
	Vector2 GetColliderVelocity();
	//判定を利用するかどうかを変更する
	void enabled(bool change);
public:
	//利用している判定の種類
	CollisionType type_;
	//四角判定
	BoundingBox box_;
	//カプセル判定
	BoundingCapsule capsule_;
	//円判定
	BoundingCircle circle_;
	//線分判定
	BoundingSegment segment_;

	struct component
	{
		Vector2 point[4];
		float radius;
		component()
		{
			point[0] = 0;
			point[1] = 0;
			point[2] = 0;
			point[3] = 0;
			radius = 0;
		}
		component(Vector2 one, Vector2 two, Vector2 three, Vector2 four) {
			point[0] = one;
			point[1] = two;
			point[2] = three;
			point[3] = four;
			radius = 0;
		}

	};
	component component_;
	Vector2 movePoint[4];
	Vector2 position_;
	Vector2 previousPosition_;
	Vector2 testVect[4];
	Vector2 myvect[4];
	float radius_;

	bool enabled_;
};