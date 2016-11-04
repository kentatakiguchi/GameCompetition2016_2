#pragma once
#ifndef MapGenerator
#define Mapgenerator
#include"../FileReader/CsvReader.h"
#include"../Actor/Base/Actor.h"
#include"../World/IWorld.h"
#include"../Actor/Base/ActorGroup.h"
#include"MapChip.h"
#include"../World/IWorldPtr.h"
#include<map>
#include"MoveFloorUpDown.h"
#include"MoveFloorRightLeft.h"
#include"TurnFloor.h"
#include"MovelessFloor.h"

class MapGenerator {
public:
	//マップを生成するためのクラス　world:マップを追加する対象(IWorld*)
	MapGenerator(IWorld* world) :reader_(){
		world_ = world;

		//world_->addActor(ActorGroup::Field, std::make_shared<MapChip>(world_, Vector2(rowN*CHIPSIZE, colN*CHIPSIZE)));
		chips[1] = std::make_shared<MovelessFloor>(world_, Vector2(0, 0));
		chips[2] = std::make_shared<MoveFloorUpDown>(world_, Vector2(0, 0));
		chips[3] = std::make_shared<MoveFloorRightLeft>(world_, Vector2(0, 0));
		chips[4] = std::make_shared<TurnFloor>(world_, Vector2(0, 0));
	}
	//ファイル名(拡張子まで書く事)から、マップを生成する fileName:マップ用の.csv 0:生成しない 1:MapChipを生成
	void create(std::string fileName)
	{
		reader_.load(fileName);
		for (int rowN = 0; rowN < reader_.rows(); rowN++)
		{
			for (int colN = 0; colN < reader_.columns(rowN); colN++)
			{

				typeid(chips[(reader_.geti(rowN, colN))]).raw_name();

				if (reader_.geti(rowN, colN) == 0) continue;

				if (reader_.geti(rowN, colN) == 1) {//テンプレートを使って複数種類生成出来るようにする
				//world_->addActor(ActorGroup::Field,std::make_shared<MovelessFloor>(chips[(reader_.geti(rowN, colN))], world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
					world_->addActor(ActorGroup::Field, std::make_shared<MovelessFloor>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 2) {
					world_->addActor(ActorGroup::Field, std::make_shared<MoveFloorUpDown>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 3) {
					world_->addActor(ActorGroup::Field, std::make_shared<MoveFloorRightLeft>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 4) {
					world_->addActor(ActorGroup::Field, std::make_shared<TurnFloor>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
			}
		}
	}
private:
	//CSVのデータを引き出すためのクラス
	CsvReader reader_;
	//ゲーム本体、マップを追加する対象
	IWorld* world_;
	//追加したいマップチップはここに入れる
	std::map<int,MapChip> chips;
};

#endif // !MapGenerator