#pragma once
#include"../../Math/Vector2.h"

// マスヘルパークラス
class CollisionUtil {
public:
	static void PushOut_Circle_Box() {}
	static bool Intersects_Segment_Segment(Vector2 thisstart, Vector2 thisend, Vector2 otherstart, Vector2 otherend);
	static bool Intersects_Segment_Box(Vector2 thisstart, Vector2 thisend, Vector2 othertopLeft, Vector2 othertopRight, Vector2 otherbottomLeft, Vector2 otherbottomRight);
	static bool Intersects_Segment_Circle(Vector2 thisstart, Vector2 thisend, Vector2 othercenter, float otherradius);
	static bool Intersects_Segment_Capsule(Vector2 thisstart, Vector2 thisend, Vector2 otherstart, Vector2 otherend, float otherradius);
	static bool Intersects_Box_Box(Vector2 thistopLeft, Vector2 thistopRight, Vector2 thisbottomLeft, Vector2 thisbottomRight,
		Vector2 othertopLeft, Vector2 othertopRight, Vector2 otherbottomLeft, Vector2 otherbottomRight);
	static bool Intersects_Box_Circle(Vector2 thistopLeft, Vector2 thistopRight, Vector2 thisbottomLeft, Vector2 thisbottomRight,
		Vector2 othercenter, float otherradius);
	static bool Intersects_Box_Capsule(Vector2 thistopLeft, Vector2 thistopRight, Vector2 thisbottomLeft, Vector2 thisbottomRight,
		Vector2 otherstart, Vector2 otherend, float otherradius);
	static bool Intersects_Circle_Circle(Vector2 thiscenter, float thisradius, Vector2 othercenter, float otherradius);
	static bool Intersects_Circle_Capsule(Vector2 thiscenter, float thisradius, Vector2 otherstart, Vector2 otherend, float otherradius);
	static bool Intersects_Capsule_Capsule(Vector2 thisstart, Vector2 thisend, float thisradius, Vector2 otherstart, Vector2 otherend, float otherradius);

	static bool IsCross(Vector2 thisprevPos, Vector2 thisPos, Vector2 otherStart, Vector2 otherEnd);
};