#ifndef FIELD_H_
#define FIELD_H_

#include "DxLib.h"
#include "../Math/Vector3.h"

class Field {
public:
	// コンストラクタ
	Field(unsigned int field, unsigned int field_coll, unsigned int skybox);
	//更新
	void update(float deltaTime);
	// 描画
	void draw() const;

	unsigned int modelHandle();
	// コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	unsigned int field_;
	unsigned int field_coll_;
	unsigned int skybox_;
};

#endif
