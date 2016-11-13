#ifndef BOSS_ENTRY_H_
#define BOSS_ENTRY_H_

#include "../../../Base/Actor.h"

// �{�X�̐N�����N���X
class BossEntry : public Actor {
public:
	BossEntry(IWorld* world, const Vector2&  position, const Vector2& addPosition, const float bodyScale);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

public:
	// �ʒu�̐ݒ�����܂�
	void setBossPosition(const Vector2& position);
	// ������ݒ肵�܂�
	void setDirection(const Vector2& direction);
	// �{�X�̑̓��ɓ���邩��ݒ肵�܂�
	void setIsEntry(bool isEntry);
	// �{�X�̑̓��ɓ���������Ԃ��܂�
	bool isEntered();
	// �v���C���[���{�X�̑̓��ɏo�����Ƃɂ��܂�
	void letOut();

private:
	bool isEntry_;			// �̓��ɓ���邩
	bool isEntered_;		// �̓��ɓ�������
	Vector2 direction_;		// ����
	Vector2 bossPosition_;	// �{�X�̈ʒu
	Vector2 addPosition_;	// �ǉ��ʒu
};

#endif