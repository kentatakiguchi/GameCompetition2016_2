#ifndef FIELD_H_
#define FIELD_H_

#include "DxLib.h"
#include "../Math/Vector3.h"

class Field {
public:
	// �R���X�g���N�^
	Field(unsigned int field, unsigned int field_coll, unsigned int skybox);
	//�X�V
	void update(float deltaTime);
	// �`��
	void draw() const;

	unsigned int modelHandle();
	// �R�s�[�֎~
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	unsigned int field_;
	unsigned int field_coll_;
	unsigned int skybox_;
};

#endif
