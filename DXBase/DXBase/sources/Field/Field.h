#ifndef FIELD_H_
#define FIELD_H_

#include "DxLib.h"
#include "../Math/Math.h"

#include"../FileReader/CsvReader.h"

#include <map>

enum class FieldEnum {

};

class Field {
public:
	// �R���X�g���N�^
	Field(const std::string& fileName, int colDef = 0, int rowDef = 0, int stagenum = 0);
	void load(const std::string& fileName, int colDef = 0, int rowDef = 0, int stagenum = 0);
	//�X�V
	void update(float deltaTime);
	// �`��
	void draw() const;

	unsigned int modelHandle();

	Vector2 calcColl(Vector2& position);
	// �R�s�[�֎~
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	//CSV�̃f�[�^�������o�����߂̃N���X
	CsvReader reader_;

	typedef std::vector<std::vector<int>> FieldData;
	FieldData field_;
};

#endif
