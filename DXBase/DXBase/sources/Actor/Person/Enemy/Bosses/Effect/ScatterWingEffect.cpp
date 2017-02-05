#include "ScatterWingEffect.h"
#include "BossWingEffect.h"
#include "../../../../Base/ActorGroup.h"
#include "../../../../../World/IWorld.h"
#include <random>

ScatterWingEffect::ScatterWingEffect(
	IWorld * world,
	const Vector2 & position) :
	Actor(world, "ScatterWingEffect", position, CollisionBase())
{
	auto range = 100;
	// �����̎擾
	std::random_device random;
	// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
	// ����Seed�l��n��
	std::mt19937 mt(random());
	// �͈͂̎w��(int�^)
	std::uniform_int_distribution<> cRange(-range, range);
	std::uniform_int_distribution<> scale(8, 14);
	// �H�G�t�F�N�g�̐���
	for (int i = 0; i != 6; i++) {
		auto wingEffect = std::make_shared<BossWingEffect>(
			world_, position_ + Vector2((float)cRange(mt), cRange(mt) / 10.0f), 
			(float)scale(mt));
		world_->addActor(ActorGroup::EnemyBullet, wingEffect);
	}
}

void ScatterWingEffect::onUpdate(float deltaTime){}

void ScatterWingEffect::onDraw() const{}

void ScatterWingEffect::onCollide(Actor & actor){}
