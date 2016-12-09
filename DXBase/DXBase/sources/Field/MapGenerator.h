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
#include"MoveFloorCenterUpDown.h"
#include"MoveFloorRightLeft.h"
#include"MoveFloorCenterRightLeft.h"
#include"TurnFloor.h"
#include"MovelessFloor.h"
#include"NavChip.h"
#include"TranslessTurnFloor.h"
#include"StageClearPoint.h"
#include"GameOverPoint.h"
#include"CollidelessFloor.h"
#include"SegmentFloor.h"
#include"SticklessFloor.h"
#include"BossAreaFloor.h"
#include"../Actor/Person/Enemy/ImportEnemys.h"
#include"../Actor/Person/Enemy/Bosses/ImportBosses.h"
#include"../ResourceLoader/ResourceLoader.h"

class MapGenerator {
private:
	enum pointSetState {
		FF,//どちらもそのまま
		TF,//始点のみ補正
		FT,//終点のみ補正
		TT//どちらも補正
	};
public:
	//マップを生成するためのクラス　world:マップを追加する対象(IWorld*)
	MapGenerator(IWorld* world) :reader_() {
		world_ = world;

		ResourceLoader::GetInstance().loadTexture(TextureID::CHIP1_TEX, "./resources/sprite/chip1.png");
		ResourceLoader::GetInstance().loadTexture(TextureID::CHIP2_TEX, "./resources/sprite/chip2.png");
		ResourceLoader::GetInstance().loadTexture(TextureID::CHIP3_TEX, "./resources/sprite/chip3.png");
		ResourceLoader::GetInstance().loadTexture(TextureID::CHIP4_TEX, "./resources/sprite/chip4.png");

		//world_->addActor(ActorGroup::Field, std::make_shared<MapChip>(world_, Vector2(rowN*CHIPSIZE, colN*CHIPSIZE)));


		for (int i = 0; i < 20; i++) {
			segmentChecker[100 + i] = false;
		}

	}
	Vector2 findStartPoint(std::string fileName) {
		reader_.load(fileName);
		for (int rowN = 0; rowN < reader_.rows(); rowN++)
		{
			for (int colN = 0; colN < reader_.columns(rowN); colN++)
			{
				if (reader_.geti(rowN, colN) == 999) {
					return Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
				}
			}
		}
		return START_POS;
	}
	//縦のセル数を返す
	int GetRowSize() {
		return rowSize;
	}
	//横のセル数を返す
	int GetColumnSize() {
		return colSize;
	}
	//ファイル名(拡張子まで書く事)から、マップを生成する fileName:マップ用の.csv 0:生成しない 1:MapChipを生成
	void create(std::string fileName,int colDef=0,int rowDef=0)
	{
		reader_.load(fileName);

		rowSize = reader_.rows();
		colSize = reader_.columns();

		int rowCountDef=rowDef-1;
		int colCountDef=colDef-1;
		
		if (colDef == 0 && rowDef == 0) rowCountDef = colCountDef = 0;

		for (int rowN = rowDef; rowN < (reader_.rows()-(rowCountDef)); rowN++)
		{
			for (int colN = colDef; colN < (reader_.columns(rowN)-(colCountDef)); colN++)
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
				if (reader_.geti(rowN, colN) == 11) {
					world_->addActor(ActorGroup::Field, std::make_shared<MoveFloorCenterUpDown>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 3) {
					world_->addActor(ActorGroup::Field, std::make_shared<MoveFloorRightLeft>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 12) {
					world_->addActor(ActorGroup::Field, std::make_shared<MoveFloorCenterRightLeft>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 4) {
					world_->addActor(ActorGroup::Field, std::make_shared<TurnFloor>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 6) {
					world_->addActor(ActorGroup::Field, std::make_shared<TranslessTurnFloor>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 7) {
					world_->addActor(ActorGroup::Field, std::make_shared<StageClearPoint>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 8) {
					world_->addActor(ActorGroup::Field, std::make_shared<GameOverPoint>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 9) {
					world_->addActor(ActorGroup::Field, std::make_shared<SticklessFloor>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 10) {
					world_->addActor(ActorGroup::Field, std::make_shared<BossAreaFloor>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}

				if (reader_.geti(rowN, colN) == 20) {
					//world_->addActor(ActorGroup::Field,std::make_shared<MovelessFloor>(chips[(reader_.geti(rowN, colN))], world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
					world_->addActor(ActorGroup::Field, std::make_shared<MovelessFloor>(
						ResourceLoader::GetInstance().getTextureID(TextureID::CHIP1_TEX), world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 21) {
					//world_->addActor(ActorGroup::Field,std::make_shared<MovelessFloor>(chips[(reader_.geti(rowN, colN))], world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
					world_->addActor(ActorGroup::Field, std::make_shared<MovelessFloor>(
						ResourceLoader::GetInstance().getTextureID(TextureID::CHIP2_TEX), world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 30) {
					world_->addActor(ActorGroup::Field, std::make_shared<CollidelessFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::CHIP2_TEX), world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 50) {
					// クリボーエネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)+(Vector2::One*CHIPSIZE/2), -1.0f));
				}
				if (reader_.geti(rowN, colN) == 51) {
					// クリボーエネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}
				if (reader_.geti(rowN, colN) == 52) {
					// ゴルドエネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}
				if (reader_.geti(rowN, colN) == 53) {
					// ゴルドエネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2),  Vector2::Left));
				}
				if (reader_.geti(rowN, colN) == 54) {
					// ハネクリボーエネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<FlyingEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2), -1.0f));
				}
				if (reader_.geti(rowN, colN) == 55) {
					// ハネクリボーエネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<FlyingEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}
				if (reader_.geti(rowN, colN) == 56) {
					// 壁移動エネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<WallMoveEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}
				if (reader_.geti(rowN, colN) == 57) {
					// 壁移動エネミー
					world_->addActor(ActorGroup::Enemy, std::make_shared<WallMoveEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2),Vector2(1.f,1.f)));
				}
				if (reader_.geti(rowN, colN) == 58) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<NeedleEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2), 0));
				}
				if (reader_.geti(rowN, colN) == 59) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<NeedleEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2), 180));
				}
				if (reader_.geti(rowN, colN) == 60) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<NeedleEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2), 90));
				}
				if (reader_.geti(rowN, colN) == 61) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<NeedleEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2), 270));
				}
				if (reader_.geti(rowN, colN) == 65) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<BaseBoss>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}
				if (reader_.geti(rowN, colN) == 66) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<BossBody>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}
				/*if (reader_.geti(rowN, colN) == 67) {
					world_->addActor(ActorGroup::Enemy, std::make_shared<BossHeart>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + (Vector2::One*CHIPSIZE / 2)));
				}*/
				if (reader_.geti(rowN, colN) == 100) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX),world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 101) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 102) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 103) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 104) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 105) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 106) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 107) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 108) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 109) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 110) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
					//if (segmentChecker[reader_.geti(rowN, colN)]) {
					//	segmentChecker[reader_.geti(rowN, colN)] = false;
					//	world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(world_, segmentStartPoints[reader_.geti(rowN, colN)], Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
					//}
					//else {
					//	segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
					//	segmentChecker[reader_.geti(rowN, colN)] = true;
					//}
				}
				if (reader_.geti(rowN, colN) == 111) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 112) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 113) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 114) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 115) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 116) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 117) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 118) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 119) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, FF);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 120) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 121) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 122) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 123) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 124) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 125) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 126) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 127) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 128) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}
				if (reader_.geti(rowN, colN) == 129) {
					if (segmentChecker[reader_.geti(rowN, colN)]) {
						segmentChecker[reader_.geti(rowN, colN)] = false;
						Vector2 startPoint, endPoint;
						SetSegmentPoint(rowN, colN, startPoint, endPoint, TT);
						world_->addActor(ActorGroup::Field, std::make_shared<SegmentFloor>(ResourceLoader::GetInstance().getTextureID(TextureID::SEGMENT_TRI_TEX), world_, startPoint, endPoint));
					}
					else {
						segmentStartPoints[reader_.geti(rowN, colN)] = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);
						segmentChecker[reader_.geti(rowN, colN)] = true;
					}
				}

			}
		}
	}
private:
	void SetSegmentPoint(float rowN, float colN, Vector2& startPoint, Vector2& endPoint,pointSetState state)
	{
		startPoint = segmentStartPoints[reader_.geti(rowN, colN)];
		endPoint = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE);

		Vector2 startSet, endSet;

		startSet = Vector2::Zero;
		endSet = Vector2(CHIPSIZE, 0);
			
		if (segmentStartPoints[reader_.geti(rowN, colN)].x < colN*CHIPSIZE) {
			startPoint = segmentStartPoints[reader_.geti(rowN, colN)] + startSet;
			endPoint = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + endSet;
		}
		else if (segmentStartPoints[reader_.geti(rowN, colN)].x > colN*CHIPSIZE)
		{
			startPoint = Vector2(colN*CHIPSIZE, rowN*CHIPSIZE) + startSet;
			endPoint = segmentStartPoints[reader_.geti(rowN, colN)] + endSet;
		}
	}

private:
	//CSVのデータを引き出すためのクラス
	CsvReader reader_;
	//ゲーム本体、マップを追加する対象
	IWorld* world_;
	//追加したいマップチップはここに入れる
	std::map<int,MapChip> chips;
	std::map<int, bool> segmentChecker;
	std::map<int, Vector2> segmentStartPoints;

	int rowSize;
	int colSize;
};

#endif // !MapGenerator