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
	//�}�b�v�𐶐����邽�߂̃N���X�@world:�}�b�v��ǉ�����Ώ�(IWorld*)
	MapGenerator(IWorld* world) :reader_(){
		world_ = world;

		//world_->addActor(ActorGroup::Field, std::make_shared<MapChip>(world_, Vector2(rowN*CHIPSIZE, colN*CHIPSIZE)));
		chips[1] = std::make_shared<MovelessFloor>(world_, Vector2(0, 0));
		chips[2] = std::make_shared<MoveFloorUpDown>(world_, Vector2(0, 0));
		chips[3] = std::make_shared<MoveFloorRightLeft>(world_, Vector2(0, 0));
		chips[4] = std::make_shared<TurnFloor>(world_, Vector2(0, 0));
	}
	//�t�@�C����(�g���q�܂ŏ�����)����A�}�b�v�𐶐����� fileName:�}�b�v�p��.csv 0:�������Ȃ� 1:MapChip�𐶐�
	void create(std::string fileName)
	{
		reader_.load(fileName);
		for (int rowN = 0; rowN < reader_.rows(); rowN++)
		{
			for (int colN = 0; colN < reader_.columns(rowN); colN++)
			{

				typeid(chips[(reader_.geti(rowN, colN))]).raw_name();

				if (reader_.geti(rowN, colN) == 0) continue;

				if (reader_.geti(rowN, colN) == 1) {//�e���v���[�g���g���ĕ�����ސ����o����悤�ɂ���
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
	//CSV�̃f�[�^�������o�����߂̃N���X
	CsvReader reader_;
	//�Q�[���{�́A�}�b�v��ǉ�����Ώ�
	IWorld* world_;
	//�ǉ��������}�b�v�`�b�v�͂����ɓ����
	std::map<int,MapChip> chips;
};

#endif // !MapGenerator