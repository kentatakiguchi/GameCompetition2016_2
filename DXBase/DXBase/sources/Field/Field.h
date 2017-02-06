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
	// コンストラクタ
	Field(const std::string& fileName, int colDef = 0, int rowDef = 0, int stagenum = 0);
	void load(const std::string& fileName, int colDef = 0, int rowDef = 0, int stagenum = 0);
	//更新
	void update(float deltaTime);
	// 描画
	void draw() const;

	unsigned int modelHandle();

	Vector2 calcColl(Vector2& position);
	// コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	//CSVのデータを引き出すためのクラス
	CsvReader reader_;

	typedef std::vector<std::vector<int>> FieldData;
	FieldData field_;
};

#endif
