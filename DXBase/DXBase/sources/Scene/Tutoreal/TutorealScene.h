#pragma once
#include <memory>
#include "../Base/IScene.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include <vector>
#include <string>
#include "../GamePlay/MoveScreen.h"
#include "../GamePlay/PauseScreen.h"
#include "../../Animation/Base/Animation2D.h"
class PlayerConnector;

struct TutorealName {
	std::string csvName;
	MOVIE_ID movieID;
	std::string moviePas;
	std::vector<TextureID> textIDs;
	std::vector<TextureID> timeCountIDs;
};
struct StarState {
	Vector2 position;
	float Scale;
	float alpha;
	float angle;
};

class World;
class TutorealScene : public IScene {
public:
	TutorealScene(SceneDataKeeper* keeper);
	~TutorealScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	bool EndTutoreal(int num);
	//�I���t���O����
	bool Tutoreal1();
	bool Tutoreal2();
	bool Tutoreal3();
	bool Tutoreal4();
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
	//�`���[�g���A������
	std::vector<TutorealName> tutorels_;
	//�����I��������
	bool isMovie_;
	//����̈ʒu
	Vector2 movieResPos1_;
	Vector2 movieResPos2_;
	Vector2 moviePos_;
	//�T�C�Y
	float size_;
	//�`���[�g���A���̃e�L�X�g����
	std::vector<TextureID> tutorealTexs_;
	//���l
	float alpha_;
	//�t�F�[�h�p��
	float feedAlpha_;
	//����ړ��̕��
	float movieMoveTime_;
	//���������̃`���[�g���A���e�L�X�g�ԍ�
	int tutorealTexCount_;
	//�{���̃e�L�X�g�ԍ�
	int resTutorealTexCount_;
	//�J�E���g�⎞��
	std::vector<TextureID> tutorealTimes_;
	//�`���[�g���A���̎��ԂƂ��J�E���g�Ƃ�
	int countAndTime_;
	int endTutorealCount_;
	//�`���[�g���A��1,2
	float stickTime_;
	//�`���[�g���A��3
	int endCount_;
	float attackRagCount_;
	bool attackRagFalg;
	//�N���A�[������̎���
	float clearTime_;
	//�N���A�[������
	bool isClear_;
	//�Ō�Ɏg���t���O
	bool tutoreal4Flag;
	//�v���C���[�R�l�N�^�[
	PlayerConnector* playerConnector_;
	//�v���C���[����ɋ�����
	float playerUpAlpha_;
	float playerUpCount_;
	//����̃��l
	float mMovieAlpha;
	//�`���[�g���A���N���A�[�̃T�C�Y
	float mClerScale;
	//�`���[�g���A���N���A�[�̃�
	float mClerAlpha;
	std::vector<StarState> starState_;
	std::vector<Vector2>starPoss_;
	Animation2D starAnim_;
	//�v���C���[����ɂ��邩
	bool isPlayerUp_;
};