#include "Animation.h"

#include <math.h>

#define ANIM_BLEND_SPEED 0.1f;
#define PLAY_ANIM_SPEED 0.8f;

Animation::Animation(const unsigned int &modelHandle_) :
	modelHandle_(modelHandle_), animBlendRate_(1.0f){

}

void Animation::update(float deltaTime){
	process();
}

void Animation::process(){
	float AnimTotalTime;		// 再生しているアニメーションの総時間

	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate_ < 1.0f)
	{
		animBlendRate_ += ANIM_BLEND_SPEED;
		if (animBlendRate_ > 1.0f)
		{
			animBlendRate_ = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (currAnim_.id_ != -1)
	{
		// アニメーションの総時間を取得
		AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle_, currAnim_.id_);

		// 再生時間を進める
		currAnim_.count_ += PLAY_ANIM_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (currAnim_.count_ >= AnimTotalTime)
		{
			currAnim_.count_ = fmodf(currAnim_.count_, AnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle_, currAnim_.id_, currAnim_.count_);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle_, currAnim_.id_, animBlendRate_);
	}

	// 再生しているアニメーション２の処理
	if (prevAnim_.id_ != -1)
	{
		// アニメーションの総時間を取得
		AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle_, prevAnim_.id_);

		// 再生時間を進める
		prevAnim_.count_ += PLAY_ANIM_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevAnim_.count_ > AnimTotalTime)
		{
			prevAnim_.count_ = fmodf(prevAnim_.count_, AnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle_, prevAnim_.id_, prevAnim_.count_);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle_, prevAnim_.id_, 1.0f - animBlendRate_);
	}
}

void Animation::changeAnim(int id){
	if (id_ == id)return;
	id_ = id;
	// 再生中のモーション２が有効だったらデタッチする
	if (prevAnim_.id_ != -1){
		MV1DetachAnim(modelHandle_, prevAnim_.id_);
		prevAnim_.id_ = -1;
	}

	// 今まで再生中のモーション１だったものの情報を２に移動する
	prevAnim_ = currAnim_;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	currAnim_.id_ = MV1AttachAnim(modelHandle_, id);
	currAnim_.count_ = 0.0f;

	// ブレンド率は再生中のモーション２が有効ではない場合は１．０ｆ( 再生中のモーション１が１００％の状態 )にする
	animBlendRate_ = prevAnim_.id_ == -1 ? 1.0f : 0.0f;
}

bool Animation::isAnimEnd(){
	// 再生しているアニメーションの総時間
	float AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle_, currAnim_.id_);
	return 	currAnim_.count_ >= AnimTotalTime - 1;
}
