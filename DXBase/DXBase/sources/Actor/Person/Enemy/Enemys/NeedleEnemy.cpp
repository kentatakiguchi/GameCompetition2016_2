#include "NeedleEnemy.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../../Define.h"

NeedleEnemy::NeedleEnemy(
	IWorld * world,
	const Vector2 & position,
	const Vector2& direction) :
	BaseEnemy(world, position, CHIPSIZE)
{
	// �㉺���E�������悤�ɂ���
	direction_ = direction;
}

void NeedleEnemy::update(float deltaTime){}

void NeedleEnemy::onDraw() const
{
	// �j�̉摜�̕�����ς���
	// direction_
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �j�̕\��
	DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), 0);
}

void NeedleEnemy::onCollide(Actor &){}

void NeedleEnemy::onMessage(EventMessage event, void *){}

// �����Ȃ��̂ŉ������Ȃ�
void NeedleEnemy::idel(){}
