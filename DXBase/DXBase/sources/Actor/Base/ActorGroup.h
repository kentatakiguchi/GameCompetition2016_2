#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

enum class ActorGroup {
	Player,				// �v���[��
	Player_Collider,		// �v���[��
	Player_AttackRange,		// �v���[���e
	Enemy,				// �G
	Enemy_AttackRange,		// �v���[���e
	Enemy_Spawner,		// �v���[���e
	EnemyBullet,		// �G�e
	Effect,				// �G�t�F�N�g
	EffectBack,			// �G�t�F�N�g(����`��p)
	BACKGRAUND,
	SCROOLSTOP,
	PuyoVertex,
	Tubo,               //�c�{
	Field,				//�X�e�[�W
	Item
};

#endif
