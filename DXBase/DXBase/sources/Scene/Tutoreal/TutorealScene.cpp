#include "TutorealScene.h"
#include "../../Field/MapGenerator.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/Movie.h"
#include "../../Input/InputMgr.h"
#include "../../Math/MathHelper.h"
#include "../../Actor/Person/Player/PlayerConnector.h"
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
	//name1.textIDs.push_back(TextureID::TUTOREAL1_2_TXT_TEX);
	//name1.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_1_TEX);
	//name1.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_2_TEX);
	//name1.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_3_TEX);
	//2��
	TutorealName name2;
	name2.csvName = "tutoreal02";
	name2.movieID = MOVIE_ID::TEST_MOVE;
	name2.textIDs.push_back(TextureID::TUTOREAL2_1_TXT_TEX);
	//name2.textIDs.push_back(TextureID::TUTOREAL2_2_TXT_TEX);
	//name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_1_TEX);
	//name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_2_TEX);
	//name2.timeCountIDs.push_back(TextureID::TUTOREAL_TIME_3_TEX);
	//3��
	TutorealName name3;
	name3.csvName = "tutoreal03";
	name3.movieID = MOVIE_ID::TEST_MOVE;
	name3.textIDs.push_back(TextureID::TUTOREAL3_1_TXT_TEX);
	//name3.textIDs.push_back(TextureID::TUTOREAL3_2_TXT_TEX);
	//name3.timeCountIDs.push_back(TextureID::TUTOREAL_COUNT_1_TEX);
	//name3.timeCountIDs.push_back(TextureID::TUTOREAL_COUNT_2_TEX);
	////4��
	//TutorealName name4;
	//name4.csvName = "tutoreal02";
	//name4.movieID = MOVIE_ID::TEST_MOVE;
	//name4.textIDs.push_back(TextureID::TUTOREAL4_1_TXT_TEX);
	//name4.textIDs.push_back(TextureID::TUTOREAL4_2_TXT_TEX);
	////name4.textIDs.push_back(TextureID::)
	//name4.textIDs.push_back(TextureID::TUTOREAL4_3_TXT_TEX);

	//�ݒ肵���������
	tutorels_.push_back(name1);
	tutorels_.push_back(name2);
	tutorels_.push_back(name3);
	//tutorels_.push_back(name4);

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
	isClear_ = false;
	tutoreal4Flag = false;
	tutorealTexCount_ = 0;
	resTutorealTexCount_ = 0;
	countAndTime_ = 0;
	stickTime_ = 3.0f;
	endCount_ = 2;
	attackRagCount_ = 0.0f;
	clearTime_ = 0.0f;
	feedAlpha_ = 1.0f;
	//�I���t���O�̔ԍ���ݒ�
	endTutorealCount_ = tutorealRoopCount_;
	//���l��������
	alpha_ = 1.0f;
	//��ԏ�����
	size_ = 0.2f;
	movieMoveTime_ = 0.0f;
	//����T�C�Y�擾
	Vector2 movieSize = Movie::GetInstance().GetMovieSize(tutorels_[tutorealRoopCount_].movieID)*0.1f;
	//����̈ʒu�ݒ�
	moviePos_ = Vector2(SCREEN_SIZE.x - movieSize.x - 16, 150);
	movieResPos1_ = moviePos_;
	movieResPos2_ = Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);
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
	Movie::GetInstance().Play(movieId_);
	//�Z�b�g�����玟�̖��O�ɂ��Ă���
	if (tutorealSize_ - 1 > tutorealRoopCount_)
		tutorealRoopCount_++;
	//�e���[�g���A�����Ȃ��ꍇ�^�C�g����
	else
		nextScene_ = Scene::MainMenu;
	//�v���C���[�̍��W���Z�b�g
	world_->SetPlayerPos(gener.findStartPoint("./resources/file/" + name_ + ".csv"));
	//�v���C���[��ǉ�
	world_->addActor(ActorGroup::Player, std::make_shared<Player>
		(world_.get(), gener.findStartPoint("./resources/file/" + name_ + ".csv")));

	world_->CollisitionOffOn(true);
	//�}�b�v����
	gener.create("./resources/file/" + name_ + ".csv", 0, 0);
	//�X�N���[���Z�b�g
	world_->SetScroolJudge(Vector2(0, 0), Vector2::Zero, Vector2(9999, 9999));
	//�v���C���[�R�l�N�^�[
	playerConnector_ = dynamic_cast<PlayerConnector*>(world_->findActor("PlayerConnector").get());
}

void TutorealScene::update()
{
	//T����������`���[�g���A�����悪�Đ������
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T) && !isClear_) {
		isStopped_ ? deltaTime_ = Time::GetInstance().deltaTime() : deltaTime_ = 0;
		isStopped_ = !isStopped_;
		isMovie_ = !isMovie_;
		if (isMovie_) {
			Movie::GetInstance().Stop(movieId_);
			Movie::GetInstance().Seek(movieId_, 0.0f);
		}
	}
	//��Ԏ��Ԋ֌W
	if (isMovie_) {
		movieMoveTime_ += 90 * Time::GetInstance().deltaTime();
		playerUpCount_ -= movieMoveTime_ / 90.0f;
	}
	else {
		movieMoveTime_ -= 90 * Time::GetInstance().deltaTime();
	}

	//�N�����v
	movieMoveTime_ = MathHelper::Clamp(movieMoveTime_, 0.0f, 90.0f);
	//�g�債�I�������Đ�����
	if (movieMoveTime_ >= 90) Movie::GetInstance().Play(movieId_);
	//���l����`�ۊ�
	alpha_ = MathHelper::Lerp(255.0f, 0.0f, movieMoveTime_ / 90.0f);
	//�T�C�Y����`���
	size_ = MathHelper::Lerp(0.2f, 0.8f, MathHelper::Sin(movieMoveTime_));
	//�ړ�����`���
	moviePos_ = Vector2::Lerp(movieResPos1_, movieResPos2_, MathHelper::Sin(movieMoveTime_));

	if (world_->findActor("Player")->getPosition().y <= 600.0f) {
		playerUpCount_ -= 3.0f* Time::GetInstance().deltaTime();
	}
	else {
		if(!isMovie_)
		playerUpCount_ += 3.0f*Time::GetInstance().deltaTime();
	}
	playerUpCount_ = MathHelper::Clamp(playerUpCount_, 0.0f, 1.0f);
	playerUpAlpha_ = MathHelper::Lerp(0.0f, 255.0f, playerUpCount_);
	//�N���A�[�֌W
	if (isClear_&&endTutorealCount_ != 3) {
		clearTime_ += Time::GetInstance().deltaTime();

		if (tutorealTexCount_ == 0)
			feedAlpha_ -= 2.0f*Time::GetInstance().deltaTime();
		else
			feedAlpha_ += 2.0f*Time::GetInstance().deltaTime();

		if (feedAlpha_ <= 0.0f) /*tutorealTexCount_ = 1*/;

		if (clearTime_ >= 4.0f) isEnd_ = true;
	}
	//�Ō�̃`���[�g���A�������̏���
	else if (isClear_) {
		if (tutorels_.back().textIDs.size() - 1 == tutorealTexCount_&&
			InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE)) {
			isEnd_ = true;
		}
		//�N���A�[��������������
		if (resTutorealTexCount_ == 0) resTutorealTexCount_++;

		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE) && feedAlpha_ >= 1.0f) {
			resTutorealTexCount_++;
		}
		if (resTutorealTexCount_ != tutorealTexCount_) {
			feedAlpha_ -= 2.0f*Time::GetInstance().deltaTime();
			if (feedAlpha_ <= 0.0f) {
				tutorealTexCount_ = resTutorealTexCount_;
			}
		}
		if (resTutorealTexCount_ == tutorealTexCount_)
			feedAlpha_ += 2.0f*Time::GetInstance().deltaTime();
		//�N�����v
		feedAlpha_ = MathHelper::Clamp(feedAlpha_, 0.0f, 1.0f);
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::J))
		isClear_ = true;

	if (!isClear_)
		EndTutoreal(endTutorealCount_);


	if (!isStopped_)
		world_->update(deltaTime_);
}

void TutorealScene::draw() const
{
	world_->draw();

	//���u�����h
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, playerUpAlpha_);
	//�e�L�X�g����
	Vector2 size = ResourceLoader::GetInstance().GetTextureSize(TextureID::TUTOREAL_BACK_TEX)*0.93f / 2.0f;
	DrawRotaGraphF(32 + size.x, 16 + size.y, 0.93f, 0, ResourceLoader::GetInstance().getTextureID(TextureID::TUTOREAL_BACK_TEX), TRUE);
	//if (isClear_)SetDrawBlendMode(DX_BLENDMODE_ALPHA, MathHelper::Lerp(0, 255, feedAlpha_));
	DrawGraph(64, 64, ResourceLoader::GetInstance().getTextureID(tutorealTexs_[tutorealTexCount_]), TRUE);
	////���ԂƃJ�E���g����
	//if (!tutorealTimes_.empty() && (int)stickTime_ != -1 && (int)endCount_ != -1)
	//	DrawGraph(32, 256 + 128, ResourceLoader::GetInstance().getTextureID(tutorealTimes_[countAndTime_]), TRUE);
	//���u�����h�I���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0.0f);

	//����
	Movie::GetInstance().DrawRotaMovie(movieId_, moviePos_, size_);

	//����̌��̉摜
	int id = ResourceLoader::GetInstance().getTextureID(TextureID::MOVIEBACK_TEX);
	DrawRotaGraph(moviePos_.x, moviePos_.y, size_, 0.0f, id, TRUE);
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

bool TutorealScene::EndTutoreal(int num)
{
	if (world_->findActors(ActorGroup::Item).empty())isClear_ = true;
	//switch (num)
	//{
	//case 0: {

	//	break;
	//}
	//case 1: {
	//	if (world_->getCount() >= 1)return true;
	//	break;
	//}
	//case 2: {
	//	if (world_->getCount() >= 1)return true;
	//	break;
	//}
	//case 3: {
	//	if (world_->getCount() >= 1)return true;
	//	break;
	//}
	//}
	return false;
}

bool TutorealScene::Tutoreal1()
{
	if (std::fabsf(InputMgr::GetInstance().AnalogPadVectorL().x) != 0.0f ||
		std::fabsf(InputMgr::GetInstance().AnalogPadVectorR().x) != 0.0f) {
		stickTime_ -= Time::GetInstance().deltaTime();
	}
	else {
		//��������3�b�ɖ߂�
		stickTime_ = 3.9f;
	}
	//�J�E���g
	countAndTime_ = (int)stickTime_ - 1;
	//0�b�ɂȂ�����I���
	if (stickTime_ < 1.0f) {
		isClear_ = true;
		return true;
	}
	return false;
}

bool TutorealScene::Tutoreal2()
{
	if (playerConnector_->stateMgr_.currentActionType(ActionType::Right) ||
		playerConnector_->stateMgr_.currentActionType(ActionType::Left) &&
		playerConnector_->stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
		stickTime_ -= Time::GetInstance().deltaTime();
	}
	else {
		//��������3�b�ɖ߂�
		stickTime_ = 3.9f;
	}
	//�J�E���g
	countAndTime_ = (int)stickTime_ - 1;
	//0�b�ɂȂ�����I���
	if (stickTime_ < 1.0f) {
		isClear_ = true;
		return true;
	}
	return false;
}

bool TutorealScene::Tutoreal3()
{
	//���O�^�C�����Ȃ��ƈ�u�ŏI��邽��
	if (playerConnector_->stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::ATTACK) &&
		!attackRagFalg) {
		endCount_--;
		attackRagFalg = true;
	}

	if (attackRagFalg) {
		attackRagCount_ += Time::GetInstance().deltaTime();
		if (attackRagCount_ >= 3.0f) {
			attackRagCount_ = 0.0f;
			attackRagFalg = false;
		}
	}
	countAndTime_ = endCount_ - 1;
	if (endCount_ <= 0) {
		isClear_ = true;
		return true;
	}
	return false;
}

bool TutorealScene::Tutoreal4()
{
	if (world_->is_clear()) {
		isClear_ = true;
		return true;
	}
	return false;
}
