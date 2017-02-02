#include "StageClearScene.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include"../../Actor/Person/Player/PlayerBody.h"
#include"../../Actor/Base/ActorPtr.h"

StageClearScene::StageClearScene(SceneDataKeeper* keeper){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "StageClear";
	nextScene = Scene::GamePlay;

}

StageClearScene::~StageClearScene() {

}

void StageClearScene::start() {

	SetDrawScreen(DX_SCREEN_BACK);

	//World�𐶐����A�v���C���[��ǉ�
	world_ = std::make_shared<World>();
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), Vector2(-400, 900)));

	//�v���C���[�͎����ł̈ړ��A���蓙�͍s��Ȃ��悤�ɂ���
	world_->PlayerNotMove(true);
	world_->CollisitionOffOn(false);

	//�o�ߎ��Ԃ̏�����
	mIvemtTime = 0;

	//�{�X�̏����ʒu��ݒ肷��
	bossPosition = Vector2(-100, 500);

	//�A�j���[�V�����̏�����
	anmer_ = SceneChangeBossAnm();

	//stage04���N���A�����ꍇ�̂݁A���̃V�[�����{�X�X�e�[�W�ɕύX����
	if (keeper_->getSceneName() == "stage04")nextScene = Scene::BossStage01;

}
void StageClearScene::update() {
	//�A�j���[�V�����̍X�V
	anmer_.update_e(Time::GetInstance().deltaTime());

	//�o�ߎ��Ԃ̍X�V
	mIvemtTime += Time::GetInstance().deltaTime();
	//�`1�b�̊Ԃ͉������Ȃ�
	if (mIvemtTime <= 1.0f) {
	}
	//�`3�b�̊Ԃ̓{�X���E��Ɉړ�����
	else if (mIvemtTime <= 3.0f) {
		bossPosition += Vector2(800, -200)*Time::GetInstance().deltaTime();
	}
	//�`5�b�̊Ԃ̓v���C���[����ʂɓo�ꂳ����
	else if (mIvemtTime <= 5) {
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody1").get())->ForcedMove(Vector2(400, 0.0f));
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody2").get())->ForcedMove(Vector2(400.0f, 0.0f));
	}
	//�`9�b�̊Ԃ̓v���C���[���~������
	else if (mIvemtTime <= 9.f) {
	}
	//�`11�b�̊Ԃ̓v���C���[����ʊO�ɏo��
	else if (mIvemtTime <= 11.0f) {
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody1").get())->ForcedMove(Vector2(-400, 0.0f));
		dynamic_cast<PlayerBody*>(world_->findActor("PlayerBody2").get())->ForcedMove(Vector2(-400.0f, 0.0f));
	}
	//�`12�b�̊Ԃ̓{�X�̌�������]������
	else if (mIvemtTime <= 12.0f) {
		anmer_.Turn();
	}
	//�`15�b�̊Ԃ̓{�X����ʊO�ɏo��
	else if(mIvemtTime <= 15.0f) {
		bossPosition -= Vector2(1200, -300)*Time::GetInstance().deltaTime();
	}
	//�S�Ă̍H�����I��������A�V�[�����I������
	else {
		isEnd_ = true;
	}
	
	//World(�v���C���[)�̍X�V���s��
	world_->update(Time::GetInstance().deltaTime());
}

void StageClearScene::draw() const {
	//World(�v���C���[)�̕`��
	world_->draw();

	//�{�X�̕`��
	anmer_.draw_e(bossPosition);
}

void StageClearScene::end() {
}

bool StageClearScene::isEnd() const {
	return isEnd_;
}

Scene StageClearScene::next() const {
	return nextScene;
}
