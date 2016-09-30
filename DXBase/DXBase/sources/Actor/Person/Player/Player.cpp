#include "Player.h"
#include "State/Player_StateMgr.h"
#include "State/States/State_Dammy.h"
#include "State/States/PlayerState_Idle.h"
#include "State/States/PlayerState_Move.h"
#include "State/States/PlayerState_Jump.h"
#include "State/States/PlayerState_Attack.h"
#include "State/States/PlayerState_Attack2.h"
#include "State/States/PlayerState_Damage.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Math/Vector3.h"
#include <memory>

const float CENTER_HEIGHT = 5.0f;

Player::Player(IWorld * world, const Vector3 & position) :
	Actor(world, "Player", position, BoundingSphere(5.0f)){

	// モデルの読み込み
	modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::PLAYER));
	animation_ = Animation(modelHandle_);
	
	//初期状態を正面に設定
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 90);
	rotation_.NormalizeRotationMatrix();

	stateMgr_.add((unsigned int)Player_EnumState::IDLE, std::make_shared<PlayerState_Idle>());
	stateMgr_.add((unsigned int)Player_EnumState::MOVE, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)Player_EnumState::JUMP, std::make_shared<PlayerState_Jump>());
	stateMgr_.add((unsigned int)Player_EnumState::QUICK, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)Player_EnumState::ATTACK, std::make_shared<PlayerState_Attack>());
	stateMgr_.add((unsigned int)Player_EnumState::ATTACK2, std::make_shared<PlayerState_Attack2>());
	stateMgr_.add((unsigned int)Player_EnumState::DAMAGE, std::make_shared<PlayerState_Damage>());
	stateMgr_.changeState(*this, (unsigned int)Player_EnumState::IDLE);

	hp_ = 10;
}

Player::~Player(){
}

void Player::onUpdate(float deltaTime) {

	stateMgr_.action(*this, deltaTime);

	animation_.changeAnim(motion_);
	animation_.update(deltaTime);

	field();

	position_ = Vector3::Clamp(position_, Vector3::Zero + Vector3(50, 0, 50), Vector3::One * 1000 * 5 - Vector3(500,0,100));

	MV1SetMatrix(modelHandle_, Matrix::MatrixToMATRIX(getPose()));

	//モーション遷移
	changeMotion(deltaTime);
}

void Player::onDraw() const{
	// プレイヤーモデルの描画
	MV1DrawModel(modelHandle_);
	body_.translate(position_ + Vector3(0, CENTER_HEIGHT, 0)).draw(); // デバッグ表示

	DrawFormatString(25, 25, GetColor(255, 255, 255), "座標 : x->%d, z->%d", (int)position_.x, (int)position_.z);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "HP : %d", hp_);
}

void Player::onCollide(Actor & other){
	if (stateMgr_.currentState() == (unsigned int)Player_EnumState::DAMAGE)return;

	if (other.getName() == "Enemy_AttackRange") {
		stateMgr_.changeState(*this, (unsigned int)Player_EnumState::DAMAGE);
		hp_ -= 1;
	}
}

void Player::changeMotion(float deltaTime){

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L)) {
		motion_ = (motion_ + 1) % 10;
		//animation_.changeAnim(motion_);
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::K)) {
		motion_ = ((motion_ - 1) + 10) % 10;
		//animation_.changeAnim(motion_);
	}
}

const int PLAYER_MAX_HITCOLL = 2048;		// 処理するコリジョンポリゴンの最大数
const int PLAYER_HIT_TRYNUM = 1000;			// 壁押し出し処理の最大試行回数
const float PLAYER_HIT_SLIDE_LENGTH = 10.0f;	// 一度の壁押し出し処理でスライドさせる距離
const float SLOPE_LIMIT = 0.5f;

void Player::field() {
	int i, j, k;						// 汎用カウンタ変数
	int moveFlag;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
	int hitFlag;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
	MV1_COLL_RESULT_POLY_DIM HitDim;	// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int KabeNum;						// 壁ポリゴンと判断されたポリゴンの数
	int YukaNum;						// 床ポリゴンと判断されたポリゴンの数
	MV1_COLL_RESULT_POLY *Kabe[PLAYER_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY *Yuka[PLAYER_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY *Poly;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
	HITRESULT_LINE LineRes;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
	
	// 移動前の座標を保存
	prePosition = curPosition;
	// 移動後の座標を算出
	curPosition = position_;

	auto field = world_;
	// プレイヤーの周囲にあるステージポリゴンを取得する
	// ( 検出する範囲は移動距離も考慮する )
	HitDim = MV1CollCheck_Sphere(world_->fieldHandle(), -1, Vector3::Vector3ToVECTOR(position_ + Vector3(0, CENTER_HEIGHT,0)), 5.0f);
	//HitDim = MV1CollCheck_Sphere(stg.ModelHandle, -1, pl.Position, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));

	Vector3 dir = curPosition - prePosition;

	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (std::abs(dir.x)  > 0.01f || std::abs(dir.z) > 0.01f)moveFlag = 1;
	else moveFlag = 0;

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断する
	{
		// 壁ポリゴンと床ポリゴンの数を初期化する
		KabeNum = 0;
		YukaNum = 0;

		// 検出されたポリゴンの数だけ繰り返し
		for (i = 0; i < HitDim.HitNum; i++)
		{
			Vector3 hitDimNor = Vector3(HitDim.Dim[i].Normal.x, HitDim.Dim[i].Normal.y, HitDim.Dim[i].Normal.z);

			//壁の場合
			if (Vector3::Dot(hitDimNor, Vector3::Up) < SLOPE_LIMIT) {
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (KabeNum < PLAYER_MAX_HITCOLL)
				{
					// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
					Kabe[KabeNum++] = &HitDim.Dim[i];
				}
			}
			//床の場合
			else{
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (YukaNum < PLAYER_MAX_HITCOLL)
				{
					// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
					Yuka[YukaNum++] = &HitDim.Dim[i];
				}
			}
		}
	}

	// 壁ポリゴンとの当たり判定処理
	if (KabeNum != 0)
	{
		// 壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
		hitFlag = 0;

		// 移動したかどうかで処理を分岐
		if (moveFlag == 1)
		{
			// 壁ポリゴンの数だけ繰り返し
			for (i = 0; i < KabeNum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Kabe[i];

				// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				//if (HitCheck_Capsule_Triangle(Vector3::Vector3ToVECTOR(curPosition), Vector3::Vector3ToVECTOR(curPosition), 5.0f, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;
				if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

				// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				hitFlag = 1;

				// 壁に当たったら壁に遮られない移動成分分だけ移動する
				{
					//VECTOR SlideVec;	// プレイヤーをスライドさせるベクトル
					Vector3 slideVec;					
					Vector3 polyNormal = Vector3(Poly->Normal.x, Poly->Normal.y, Poly->Normal.z);

					// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
					slideVec = Vector3::Cross(dir, polyNormal);

					// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
					// 元の移動成分から壁方向の移動成分を抜いたベクトル
					slideVec = Vector3::Cross(polyNormal, slideVec);

					// それを移動前の座標に足したものを新たな座標とする
					curPosition = prePosition + slideVec;
				}

				// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				for (j = 0; j < KabeNum; j++)
				{
					// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Kabe[j];

					// 当たっていたらループから抜ける
					if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) break;
				}

				// j が KabeNum だった場合はどのポリゴンとも当たらなかったということなので
				// 壁に当たったフラグを倒した上でループから抜ける
				if (j == KabeNum)
				{
					hitFlag = 0;
					break;
				}
			}
		}
		else
		{
			// 移動していない場合の処理

			// 壁ポリゴンの数だけ繰り返し
			for (i = 0; i < KabeNum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Kabe[i];
				
				if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					hitFlag = 1;
					break;
				}
			}
		}

		// 壁に当たっていたら壁から押し出す処理を行う
		if (hitFlag == 1)
		{
			// 壁からの押し出し処理を試みる最大数だけ繰り返し
			for (k = 0; k < PLAYER_HIT_TRYNUM; k++)
			{
				// 壁ポリゴンの数だけ繰り返し
				for (i = 0; i < KabeNum; i++)
				{
					// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Kabe[i];

					// プレイヤーと当たっているかを判定
					//if (HitCheck_Capsule_Triangle(curPosition, VAdd(curPosition, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;
					if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

					Vector3 polyNormal = Vector3(Poly->Normal.x, Poly->Normal.y, Poly->Normal.z);

					// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					curPosition = curPosition + polyNormal * PLAYER_HIT_SLIDE_LENGTH;

					// 移動した上で壁ポリゴンと接触しているかどうかを判定
					for (j = 0; j < KabeNum; j++)
					{
						// 当たっていたらループを抜ける
						Poly = Kabe[j];
						if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
					}

					// 全てのポリゴンと当たっていなかったらここでループ終了
					if (j == KabeNum) break;
				}

				// i が KabeNum ではない場合は全部のポリゴンで押し出しを試みる前に全ての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if (i != KabeNum) break;
			}
		}
	}

	// 床ポリゴンとの当たり判定
	if (YukaNum != 0)
	{
		//// ジャンプ中且つ上昇中の場合は処理を分岐
		//if (pl.State == 2 && pl.JumpPower > 0.0f)
		//{
		//	float MinY;

		//	// 天井に頭をぶつける処理を行う

		//	// 一番低い天井にぶつける為の判定用変数を初期化
		//	MinY = 0.0f;

		//	// 当たったかどうかのフラグを当たっていないを意味する０にしておく
		//	hitFlag = 0;

		//	// 床ポリゴンの数だけ繰り返し
		//	for (i = 0; i < YukaNum; i++)
		//	{
		//		// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
		//		Poly = Yuka[i];

		//		// 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
		//		LineRes = HitCheck_Line_Triangle(curPosition, VAdd(curPosition, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		//		// 接触していなかったら何もしない
		//		if (LineRes.HitFlag == FALSE) continue;

		//		// 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
		//		if (hitFlag == 1 && MinY < LineRes.Position.y) continue;

		//		// ポリゴンに当たったフラグを立てる
		//		hitFlag = 1;

		//		// 接触したＹ座標を保存する
		//		MinY = LineRes.Position.y;
		//	}

		//	// 接触したポリゴンがあったかどうかで処理を分岐
		//	if (hitFlag == 1)
		//	{
		//		// 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
		//		curPosition.y = MinY - PLAYER_HIT_HEIGHT;

		//		// Ｙ軸方向の速度は反転
		//		pl.JumpPower = -pl.JumpPower;
		//	}
		//}
		//else
		//{
			float MaxY;

			// 下降中かジャンプ中ではない場合の処理

			// 床ポリゴンに当たったかどうかのフラグを倒しておく
			hitFlag = 0;

			// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
			MaxY = 0.0f;

			// 床ポリゴンの数だけ繰り返し
			for (int i = 0; i < YukaNum; i++)
			{
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[i];

				//// ジャンプ中かどうかで処理を分岐
				//if (pl.State == 2)
				//{
				//	// ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
				//	LineRes = HitCheck_Line_Triangle(VAdd(curPosition, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(curPosition, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				//}
				//else
				//{
					// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
					LineRes = HitCheck_Line_Triangle(Vector3::Vector3ToVECTOR(curPosition), Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT * 2, 0)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				//}


				// 当たっていなかったら何もしない
				if (LineRes.HitFlag == FALSE) continue;

				// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
				if (hitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// ポリゴンに当たったフラグを立てる
				hitFlag = 1;

				// 接触したＹ座標を保存する
				MaxY = LineRes.Position.y;
			}

			// 床ポリゴンに当たったかどうかで処理を分岐
			if (hitFlag == 1)
			{
				// 当たった場合

				// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
				curPosition.y = MaxY/* + CENTER_HEIGHT*/;

				//// Ｙ軸方向の移動速度は０に
				//pl.JumpPower = 0.0f;

				//// もしジャンプ中だった場合は着地状態にする
				//if (pl.State == 2)
				//{
				//	// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
				//	if (moveFlag)
				//	{
				//		// 移動している場合は走り状態に
				//		Player_PlayAnim(1);
				//		pl.State = 1;
				//	}
				//	else
				//	{
				//		// 移動していない場合は立ち止り状態に
				//		Player_PlayAnim(4);
				//		pl.State = 0;
				//	}

				//	// 着地時はアニメーションのブレンドは行わない
				//	pl.AnimBlendRate = 1.0f;
				//}
			}
			//else
			//{
			//	// 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は
			//	if (pl.State != 2)
			//	{
			//		// ジャンプ中にする
			//		pl.State = 2;

			//		// ちょっとだけジャンプする
			//		pl.JumpPower = PLAYER_FALL_UP_POWER;

			//		// アニメーションは落下中のものにする
			//		Player_PlayAnim(3);
			//	}
			//}
		//}
	}

	// 新しい座標を保存する
	position_ = Vector3::Lerp(position_, curPosition, 0.8f);

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(modelHandle_, Vector3::Vector3ToVECTOR(position_));

	// 検出したプレイヤーの周囲のポリゴン情報を開放する
	MV1CollResultPolyDimTerminate(HitDim);


	
}
