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
#include"NavChip.h"
#include"TranslessTurnFloor.h"
#include"StageClearPoint.h"
#include"GameOverPoint.h"
#include"CollidelessFloor.h"
#include"../Actor/Person/Enemy/ImportEnemys.h"
#include"../ResourceLoader/ResourceLoader.h"

class MapGenerator {
public:
	//�}�b�v�𐶐����邽�߂̃N���X�@world:�}�b�v��ǉ�����Ώ�(IWorld*)
	MapGenerator(IWorld* world) :reader_(){
		world_ = world;

		ResourceLoader::GetInstance().loadTexture(TextureID::CHIP1_TEX, "./resources/sprite/chip1.png");
		ResourceLoader::GetInstance().loadTexture(TextureID::CHIP2_TEX, "./resources/sprite/chip2.png");

		//world_->addActor(ActorGroup::Field, std::make_shared<MapChip>(world_, Vector2(rowN*CHIPSIZE, colN*CHIPSIZE)));
		chips[1] = std::make_shared<MovelessFloor>(world_, Vector2(0, 0));
		chips[2] = std::make_shared<MoveFloorUpDown>(world_, Vector2(0, 0));
		chips[3] = std::make_shared<MoveFloorRightLeft>(world_, Vector2(0, 0));
		chips[4] = std::make_shared<TurnFloor>(world_, Vector2(0, 0));
		chips[5] = std::make_shared<NavChip>(world_, Vector2(0, 0));
		chips[6] = std::make_shared<TranslessTurnFloor>(world_, Vector2(0, 0));
		chips[11] = std::make_shared<StageClearPoint>(world_, Vector2(0, 0));
		chips[12] = std::make_shared<GameOverPoint>(world_, Vector2(0, 0));
		chips[15] = std::make_shared<CollidelessFloor>(world_, Vector2(0, 0));

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
				if (reader_.geti(rowN, colN) == 5) {
					world_->addActor(ActorGroup::Field, std::make_shared<NavChip>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
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
					// �N���{�[�G�l�~�[
					world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 51) {
					// �S���h�G�l�~�[
					world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 52) {
					// �n�l�N���{�[�G�l�~�[
					world_->addActor(ActorGroup::Enemy, std::make_shared<FlyingEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
				}
				if (reader_.geti(rowN, colN) == 53) {
					// �ǈړ��G�l�~�[
					world_->addActor(ActorGroup::Enemy, std::make_shared<WallMoveEnemy>(world_, Vector2(colN*CHIPSIZE, rowN*CHIPSIZE)));
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