#include "TutorealScene.h"
#include "../../Field/MapGenerator.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/Movie.h"
TutorealScene::TutorealScene() :
	tutorealRoopCount_(0)
{
	isEnd_ = false;
	deltaTime_ = 1.0f / 60.0f;
	//�`���[�g���A���ݒ�
	//1��
	TutorealName name1;
	name1.csvName = "tutoreal01";
	name1.movieID = MOVIE_ID::TEST_MOVE;
	name1.textIDs.push_back(TextureID::TUTOREAL1_1_TXT_TEX);
	name1.textIDs.push_back(TextureID::TUTOREAL1_2_TXT_TEX);
	//2��
	TutorealName name2;
	name2.csvName = "tutoreal02";
	name2.movieID = MOVIE_ID::TEST_MOVE;
	name2.textIDs.push_back(TextureID::TUTOREAL2_1_TXT_TEX);
	name2.textIDs.push_back(TextureID::TUTOREAL2_2_TXT_TEX);
	name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_1_TEX);
	name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_2_TEX);
	name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_3_TEX);
	//3��
	TutorealName name3;
	name3.csvName = "tutoreal03";
	name3.movieID = MOVIE_ID::TEST2_MOVIE;
	name3.textIDs.push_back(TextureID::TUTOREAL3_1_TXT_TEX);
	name3.textIDs.push_back(TextureID::TUTOREAL3_2_TXT_TEX);
	name3.timeCountIDs.push_back(TextureID::TUTOREAL_COUNT_1_TEX);
	name3.timeCountIDs.push_back(TextureID::TUTOREAL_COUNT_2_TEX);
	//4��
	TutorealName name4;
	name4.csvName = "tutoreal04";
	name4.movieID = MOVIE_ID::TEST2_MOVIE;
	name4.textIDs.push_back(TextureID::TUTOREAL4_1_TXT_TEX);
	name4.textIDs.push_back(TextureID::TUTOREAL4_2_TXT_TEX);
	name4.textIDs.push_back(TextureID::TUTOREAL4_3_TXT_TEX);

	//�ݒ肵���������
	tutorels_.push_back(name1);
	tutorels_.push_back(name2);
	tutorels_.push_back(name3);
	tutorels_.push_back(name4);

	//�T�C�Y������
	tutorealSize_ = tutorels_.size();

}

TutorealScene::~TutorealScene()
{
}

void TutorealScene::start()
{
	//����������
	isEnd_ = false;
	isMovie_ = false;
	tutorealTexCount_ = 0;
	countAndTime_ = 0;
	//���l��������
	alpha_ = 1.0f;
	//��ԏ�����
	size_ = 0.2f;
	movieMoveTime_ = 0.0f;
	//����T�C�Y�擾
	Vector2 movieSize = Movie::GetInstance().GetMovieSize(tutorels_[tutorealRoopCount_].movieID);
	//����̈ʒu�ݒ�
	moviePos_ = Vector2(SCREEN_SIZE.x-movieSize.x-320, 128);
	movieResPos1_ = moviePos_;
	movieResPos2_ = Vector2(SCREEN_SIZE.x / 2 , SCREEN_SIZE.y / 2 );
	//�f���^�^�C��
	deltaTime_ = Time::GetInstance().deltaTime();
	//��������
	nextScene_ = Scene::Tutoreal;
	//�|�[�Y���Ȃ�
	isStopped_ = false;
	//���[���h
	world_ = std::make_shared<World>();
	MapGenerator gener = MapGenerator(world_.get());
	//�l�[�����Z�b�g
	name_ = tutorels_[tutorealRoopCount_].csvName;
	//�`���[�g���A��������Z�b�g
	movieId_ = tutorels_[tutorealRoopCount_].movieID;
	//�e�L�X�g���Z�b�g
	tutorealTexs_ = tutorels_[tutorealRoopCount_].textIDs;
	//���ԂƃJ�E���g���Z�b�g
	tutorealTimes_ = tutorels_[tutorealRoopCount_].timeCountIDs;
	//������Đ�
	//Movie::GetInstance().Play(movieId_);
	//�Z�b�g�����玟�̖��O�ɂ��Ă���
	if (tutorealSize_-1 > tutorealRoopCount_)
		tutorealRoopCount_++;
	//�e���[�g���A�����Ȃ��ꍇ�^�C�g����
	else
		nextScene_ = Scene::MainMenu;
	//�v���C���[�̍��W���Z�b�g
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));
	//�v���C���[��ǉ�
	world_->addActor(ActorGroup::Player, std::make_shared<Player>
		(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	//�}�b�v����
	gener.create("./resources/file/" + name_ + ".csv", 0, 0);
	//�X�N���[���Z�b�g
	world_->SetScroolJudge(Vector2(0, 0), Vector2(9999, 9999));
}

void TutorealScene::update()
{
	//T����������`���[�g���A�����悪�Đ������
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
		isMovie_ = !isMovie_;
		if (isMovie_) {
			//Movie::GetInstance().Stop(movieId_);
			//Movie::GetInstance().Seek(movieId_, 0.0f);
		}
	}
	//��Ԏ��Ԋ֌W
	if (isMovie_) movieMoveTime_ += 90 * Time::GetInstance().deltaTime();
	else movieMoveTime_ -= 90*Time::GetInstance().deltaTime();
	
	//�N�����v
	movieMoveTime_=MathHelper::Clamp(movieMoveTime_, 0.0f, 90.0f);
	//�g�債�I�������Đ�����
	//if (movieMoveTime_ >= 90) Movie::GetInstance().Play(movieId_);
	//���l����`�ۊ�
	alpha_ = MathHelper::Lerp(255.0f, 0.0f, movieMoveTime_ / 90.0f);
	//�T�C�Y����`���
	size_=MathHelper::Lerp(0.2f, 0.8f, MathHelper::Sin(movieMoveTime_));
	//�ړ�����`���
	moviePos_ = Vector2::Lerp(movieResPos1_, movieResPos2_, MathHelper::Sin(movieMoveTime_));
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::J)) {
		isEnd_ = true;
	}
	world_->update(deltaTime_);
}

void TutorealScene::draw() const
{
	world_->draw();

	//���u�����h
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	//��̕���
	//DrawGraph(16, 8, ResourceLoader::GetInstance().getTextureID(TextureID::TUTOREAL_BACK_TEX), TRUE);
	//�e�L�X�g����
	DrawGraph(32, 16, ResourceLoader::GetInstance().getTextureID(tutorealTexs_[tutorealTexCount_]), TRUE);
	//���ԂƃJ�E���g����
	if(!tutorealTimes_.empty())
	DrawGraph(32, 256, ResourceLoader::GetInstance().getTextureID(tutorealTimes_[0]), TRUE);
	//���u�����h�I���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0.0f);

	//����̌��̉摜
	int id = ResourceLoader::GetInstance().getTextureID(TextureID::MOVIEBACK_TEX);
	DrawRotaGraph(moviePos_.x, moviePos_.y, size_, 0.0f, id, TRUE);
	//����
	//Movie::GetInstance().DrawRotaMovie(movieId_, moviePos_,size_);
}

void TutorealScene::end()
{
	//�Đ����Ԃ�0�ɖ߂�
	Movie::GetInstance().Seek(movieId_, 0.0f);
	//�Đ��X�g�b�v
	Movie::GetInstance().Stop(movieId_);
	//�`���[�g���A���̐i�݂����Z�b�g
	if (nextScene_ == Scene::MainMenu) tutorealRoopCount_ = 0;
}

bool TutorealScene::isEnd() const
{
	return isEnd_;
}

Scene TutorealScene::next() const
{
	return nextScene_;
}
