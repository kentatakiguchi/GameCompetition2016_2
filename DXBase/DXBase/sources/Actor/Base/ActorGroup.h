#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

enum class ActorGroup {
	Player,				// プレーヤ
	Player_Collider,		// プレーヤ
	Player_AttackRange,		// プレーヤ弾
	Enemy,				// 敵
	Enemy_AttackRange,		// プレーヤ弾
	Enemy_Spawner,		// プレーヤ弾
	EnemyBullet,		// 敵弾
	Effect,				// エフェクト
	BACKGRAUND,
	SCROOLSTOP,
	PuyoVertex,
	Field				//ステージ
};

#endif
