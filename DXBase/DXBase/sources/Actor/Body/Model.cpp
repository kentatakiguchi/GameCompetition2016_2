#include "Model.h"

Model::Model(const int modelHandle, const Vector3 & center) :
	modelHandle_(modelHandle){
	// モデル全体のコリジョン情報を構築
	MV1SetupCollInfo(modelHandle_, -1, 8, 8, 8);
}

Model::Model(const Vector3 & center):
	Model(modelHandle_, center){
}

int Model::handle(){
	return modelHandle_;
}

bool Model::intersects(BoundingSphere & other){
	return false;
}

bool Model::intersects(Capsule & other){
	return false;
}

void Model::update(const Vector3 & center){

}

void Model::debug() const{

}

void Model::draw() const{

}
