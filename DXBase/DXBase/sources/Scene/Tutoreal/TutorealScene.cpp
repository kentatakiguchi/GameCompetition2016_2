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
	//���O������
	tutorealCsvs_.push_back("tutoreal01");
	tutorealCsvs_.push_back("tutoreal02");
	tutorealMovies_.push_back(MOVIE_ID::TEST_MOVE);
	tutorealMovies_.push_back(MOVIE_ID::TEST2_MOVIE);
	//�T�C�Y������
	tutorealSize_ = tutorealCsvs_.size();

}

TutorealScene::~TutorealScene()
{
}

void TutorealScene::start()
{
	//�G���h������
	isEnd_ = false;

	deltaTime_ = Time::GetInstance().deltaTime();
	//��������
	nextScene_ = Scene::Tutoreal;
	//�|�[�Y���Ȃ�
	isStopped_ = false;
	//���[���h
	world_ = std::make_shared<World>();
	MapGenerator gener = MapGenerator(world_.get());

	//�l�[�����Z�b�g
	name_ = tutorealCsvs_[tutorealRoopCount_];
	movieId_ = tutorealMovies_[tutorealRoopCount_];
	//������Đ�
	//Movie::GetInstance().Play(movieId_);
	//�Z�b�g�����玟�̖��O�ɂ��Ă���
	if (tutorealSize_-1 > tutorealRoopCount_)
		tutorealRoopCount_++;
	//�e���[�g���A�����Ȃ��ꍇ�^�C�g����
	else
		nextScene_ = Scene::Title;

	//�v���C���[�̍��W���Z�b�g
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));
	//�v���C���[��ǉ�
	world_->addActor(ActorGroup::Player, std::make_shared<Player>
		(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));
	gener.create("./resources/file/" + name_ + ".csv", 0, 0);
	//�X�N���[���Z�b�g
	world_->SetScroolJudge(Vector2(0, 0), Vector2(9999, 9999));


}

void TutorealScene::update()
{
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T)) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::J)) {
		isEnd_ = true;
	}
	world_->update(deltaTime_);


}

void TutorealScene::draw() const
{

	world_->draw();
	//Movie::GetInstance().Draw(movieId_, Vector2::Zero,0.5f);
}

void TutorealScene::end()
{
	////�Đ����Ԃ�0�ɖ߂�
	//Movie::GetInstance().Seek(movieId_, 0.0f);
	////�Đ��X�g�b�v
	//Movie::GetInstance().Stop(movieId_);
	//�`���[�g���A���̐i�݂����Z�b�g
	if (nextScene_ == Scene::Title) tutorealRoopCount_ = 0;
}

bool TutorealScene::isEnd() const
{
	return isEnd_;
}

Scene TutorealScene::next() const
{
	return nextScene_;
}
