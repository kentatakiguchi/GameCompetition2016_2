#include "GameDevice.h"

#include "../Scene/LoadingScene/LoadingScene.h"
#include "../Scene/Title/TitleScene.h"
#include "../Scene/GamePlay/GamePlayScene.h"
#include "../Scene/GameOver/GameOverScene.h"
#include "../Scene/KataokaScene/KataokaScene.h"
#include "../Scene/NaganoScene/NaganoScene.h"
#include "../Scene/StageClear/StageClearScene.h"
#include "../Scene/GameClear/GameClearScene.h"

GameDevice::GameDevice():dataKeeper_(),sceneMgr_(&dataKeeper_){}

GameDevice::~GameDevice(){}

void GameDevice::start(){


	sceneMgr_.add(Scene::Loading, std::make_shared<LoadingScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Title, std::make_shared<TitleScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GamePlay, std::make_shared<GamePlayScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GameOver, std::make_shared<GameOverScene>(&dataKeeper_));
	sceneMgr_.add(Scene::GameClear, std::make_shared<GameClearScene>(&dataKeeper_));
	sceneMgr_.add(Scene::StageClear, std::make_shared<StageClearScene>(&dataKeeper_));
	sceneMgr_.add(Scene::Kataoka, std::make_shared<KataokaScene>());
	//sceneMgr_.add(Scene::Nagano, std::make_shared<NaganoScene>());
	sceneMgr_.change(Scene::Loading);

	//�O�̃Q�[���v���C�V�[���̓��e��ۑ������p�̃N���X�����(�X�e�[�W�ԍ��A�L�����N�^�[��񓙂�ۑ�)
	//�����ɃC���X�^���X�����āA���ݓ����Ă���Q�[���v���C�̃f�[�^���A�J��(Update�܂��̓G���h)����^�C�~���O�ő���V�[�������ƃf�[�^�������Ă��܂�����
	//3�X�e�[�W���̐؂蕪�����ǂݍ��߂�悤�ɂ���A�Ƃ肠�����Q�[���v���C�V�[���̂�
	//�Q�[���v���C�V�[���͎g���܂킵����Acsv�̐؂�ւ��ɂ���āA�X�e�[�W��ύX����(�������ŁA�I�u�W�F�N�g�ʒu���̂ݍĐݒ肷��)
	//�f�o�b�O�p�ɁA���ڍD���ȃX�e�[�W�ɔ�ׂ�R�}���h�����(�{�^���͗]���Ă���D���ȕ��ŗǂ�)
	//�e�V�[���ɂ́A�f�[�^�ۑ��p�N���X�̃|�C���^��n��
}

void GameDevice::update(){
	sceneMgr_.update();
}

void GameDevice::draw(){
	sceneMgr_.draw();
}

void GameDevice::end(){
	sceneMgr_.end();
}