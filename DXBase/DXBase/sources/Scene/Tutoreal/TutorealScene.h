#pragma once
#include <memory>
#include "../Base/IScene.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include <vector>
#include <string>
#include "../GamePlay/MoveScreen.h"
#include "../GamePlay/PauseScreen.h"
class World;
class TutorealScene : public IScene {
public:
	TutorealScene();
	~TutorealScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	//�f���^�^�C��
	float deltaTime_;
	using WorldPtr = std::shared_ptr<World>;
	// ���[���h
	WorldPtr	world_;
	//�|�[�Y�t���O
	bool isStopped_;
	//�`���[�g���A���T�C�Y
	int tutorealSize_;
	//����J��Ԃ�����
	int tutorealRoopCount_;
	//���̃V�[��
	Scene nextScene_;
	//����ID
	MOVIE_ID movieId_;
	//�`���[�g���A��csv���O����
	std::vector<std::string> tutorealCsvs_;
	//�`���[�g���A�����悽��
	std::vector<MOVIE_ID> tutorealMovies_;
};