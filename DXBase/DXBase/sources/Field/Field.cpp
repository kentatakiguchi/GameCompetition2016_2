#include "Field.h"
//#include "Ray.h"
//#include "Line.h"
#include "../Actor/Body/BoundigShphere.h"

const float FIELD_SIZE = 1000.0f;
const float FIELD_SCALE = 5.0f;

// コンストラクタ
Field::Field(unsigned int field, unsigned int field_coll, unsigned int skybox) :
	field_(field), field_coll_(field_coll), skybox_(skybox) {
	//MV1SetPosition(field_, Vector3::Vector3ToVECTOR(Vector3(500, 0, 475) * FIELD_SCALE));
	//MV1SetPosition(field_coll_, Vector3::Vector3ToVECTOR(Vector3(500, 0, 475) * FIELD_SCALE));
	MV1SetPosition(field_, Vector3::Vector3ToVECTOR(Vector3::Zero * FIELD_SCALE));
	MV1SetPosition(field_coll_, Vector3::Vector3ToVECTOR(Vector3::Zero * FIELD_SCALE));
	MV1SetScale(field_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(field_coll_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));

	MV1SetPosition(skybox_, Vector3::Vector3ToVECTOR(Vector3(FIELD_SIZE, 0, FIELD_SIZE) * FIELD_SCALE * 0.5f));
	MV1SetScale(skybox_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE * 15));

}

void Field::update(float deltaTime) {
}

// 描画
void Field::draw() const {
	MV1DrawModel(skybox_);
	MV1DrawModel(field_);
	//MV1DrawModel(field_coll_);

	//GSrect srcRect(0.0f, scroll_, 640.0f, 480.0f + scroll_);
	//gsDrawSprite2D(bg_, NULL, &srcRect, NULL, NULL, NULL, 0.0f);
}

unsigned int Field::modelHandle(){
	return field_coll_;
}
