#include "Field.h"

#include "../Define.h"

#include <algorithm>

// コンストラクタ
Field::Field(const std::string& fileName, int colDef, int rowDef, int stagenum) {
	load(fileName, colDef, rowDef, stagenum);
}

void Field::load(const std::string& fileName, int colDef, int rowDef, int stagenum){
	reader_.load(fileName);

	for (int rowN = rowDef; rowN < (reader_.rows() - std::max<int>(rowDef - 1, 0)); rowN++)	{
		std::vector<int> column;
		for (int colN = colDef; colN < (reader_.columns(rowN) - std::max<int>(colDef - 1, 0)); colN++){
			if (reader_.geti(rowN, colN) == 1 || reader_.geti(rowN, colN) == 20) {
				column.push_back(reader_.geti(rowN, colN));
			}
			else {
				column.push_back(0);
			}
		}
		field_.push_back(column);
	}
}

void Field::update(float deltaTime) {

}

// 描画
void Field::draw() const {

}

unsigned int Field::modelHandle(){
	return 0;
}

Vector2 Field::calcColl(Vector2& position){
	Vector2 cell = position / CHIPSIZE;

	return cell;
}
