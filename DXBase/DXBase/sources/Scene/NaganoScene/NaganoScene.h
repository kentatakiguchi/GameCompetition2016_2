#pragma once

#include "../Base/IScene.h"
#include "../../Actor/Person/Player/Status/Status.h"
#include <memory>
#include <vector>
#include "../../Math/Math.h"


class World;
class BackGraundManager;
class NaganoScene : public IScene {
public:
	NaganoScene();
	~NaganoScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
	std::vector<Vector2> getpoint();
private:
	using WorldPtr = std::shared_ptr<World>;
	// ���[���h
	WorldPtr	world_;

	Status status_;

	BackGraundManager* backManager;

	float time_;

	int size_x, size_y;
	Vector2 div_size_;
	Vector2 vib_center_;	//�U�����S
	Vector2 position_;		//���W
	float angular_freq_;				//�p�U����
	float amplitude_;					//�U��
	Vector2 phase_;						//�ʑ�
	
	float spring_constant_;				//�΂˒萔
	float attenuation_constant_;		//�����萔
	float natural_length_;				//���R��
	float mass_;						//����
	float p_;						//����
	float e_;						//����
};



