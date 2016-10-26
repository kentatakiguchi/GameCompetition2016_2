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

class MapGenerator {
public:
	//�}�b�v�𐶐����邽�߂̃N���X�@world:�}�b�v��ǉ�����Ώ�(IWorld*)
	MapGenerator(IWorld* world) :reader_(){
		world_ = world;
		//world_->addActor(ActorGroup::Field, std::make_shared<MapChip>(world_, Vector2(rowN*CHIPSIZE, colN*CHIPSIZE)));
		chips[1] = std::make_shared<MapChip>(world_, Vector2(0,0));
	}
	//�t�@�C����(�g���q�܂ŏ�����)����A�}�b�v�𐶐����� fileName:�}�b�v�p��.csv 0:�������Ȃ� 1:MapChip�𐶐�
	void create(std::string fileName)
	{
		reader_.load(fileName);
		for (int rowN = 0; rowN < reader_.rows(); rowN++)
		{
			for (int colN = 0; colN < reader_.columns(rowN); colN++)
			{
				if (reader_.geti(rowN, colN) == 0) continue;
				world_->addActor(ActorGroup::Field, std::make_shared<MapChip>(chips[(reader_.geti(rowN, colN))], Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));

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