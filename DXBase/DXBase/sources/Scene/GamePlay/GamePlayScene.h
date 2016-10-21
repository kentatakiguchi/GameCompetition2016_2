#ifndef _GAME_PLAY_SCENE_H_
#define _GAME_PLAY_SCENE_H_

#include "../Base/IScene.h"
#include "../../Actor/Person/Player/Status/Status.h"
#include <memory>
#include "../../Math/Math.h"

#include "../../Renderer/Puyo_Texture.h"

class World;

class GamePlayScene : public IScene{
public:
	GamePlayScene();
	~GamePlayScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	VECTOR vector;

	using WorldPtr = std::shared_ptr<World>;
	// ���[���h
	WorldPtr	world_;

	int id;

	Status status_;


	int texHandle;
	int size_x, size_y;
	Vector2 div_size_;
	Vector2 vib_center_;	//�U�����S
	Vector2 position_;		//���W
	float time_;						//�o�ߎ���
	float angular_freq_;				//�p�U����
	float amplitude_;					//�U��
	Vector2 phase_;						//�ʑ�

	float spring_constant_;				//�΂˒萔
	float attenuation_constant_;		//�����萔
	float natural_length_;				//���R��
	float mass_;						//����
	float p_;						//����
	float e_;						//����

	Vector2 velocity_;

	Vector2 accelarate_;

	Vector2 vec_left_top;
	Vector2 vec_right_top;
	Vector2 vec_right_bot;
	Vector2 vec_left_bot;

	//�������id�i�[�p�������z��
	std::vector<std::vector<int>> sprites_;

	int column_ = 80;
	int row_ = 80;

	int ModelHandle;
	int GradTexHandle;

	//Puyo_Texture puyo_;

};

#endif