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

	// ���f���̓ǂݍ���
	modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::PLAYER));
	animation_ = Animation(modelHandle_);
	
	//������Ԃ𐳖ʂɐݒ�
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

	//���[�V�����J��
	changeMotion(deltaTime);
}

void Player::onDraw() const{
	// �v���C���[���f���̕`��
	MV1DrawModel(modelHandle_);
	body_.translate(position_ + Vector3(0, CENTER_HEIGHT, 0)).draw(); // �f�o�b�O�\��

	DrawFormatString(25, 25, GetColor(255, 255, 255), "���W : x->%d, z->%d", (int)position_.x, (int)position_.z);
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

const int PLAYER_MAX_HITCOLL = 2048;		// ��������R���W�����|���S���̍ő吔
const int PLAYER_HIT_TRYNUM = 1000;			// �ǉ����o�������̍ő厎�s��
const float PLAYER_HIT_SLIDE_LENGTH = 10.0f;	// ��x�̕ǉ����o�������ŃX���C�h�����鋗��
const float SLOPE_LIMIT = 0.5f;

void Player::field() {
	int i, j, k;						// �ėp�J�E���^�ϐ�
	int moveFlag;						// ���������Ɉړ��������ǂ����̃t���O( �O:�ړ����Ă��Ȃ�  �P:�ړ����� )
	int hitFlag;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
	MV1_COLL_RESULT_POLY_DIM HitDim;	// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	int KabeNum;						// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int YukaNum;						// ���|���S���Ɣ��f���ꂽ�|���S���̐�
	MV1_COLL_RESULT_POLY *Kabe[PLAYER_MAX_HITCOLL];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY *Yuka[PLAYER_MAX_HITCOLL];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY *Poly;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
	HITRESULT_LINE LineRes;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
	
	// �ړ��O�̍��W��ۑ�
	prePosition = curPosition;
	// �ړ���̍��W���Z�o
	curPosition = position_;

	auto field = world_;
	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ( ���o����͈͈͂ړ��������l������ )
	HitDim = MV1CollCheck_Sphere(world_->fieldHandle(), -1, Vector3::Vector3ToVECTOR(position_ + Vector3(0, CENTER_HEIGHT,0)), 5.0f);
	//HitDim = MV1CollCheck_Sphere(stg.ModelHandle, -1, pl.Position, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));

	Vector3 dir = curPosition - prePosition;

	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (std::abs(dir.x)  > 0.01f || std::abs(dir.z) > 0.01f)moveFlag = 1;
	else moveFlag = 0;

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f����
	{
		// �ǃ|���S���Ə��|���S���̐�������������
		KabeNum = 0;
		YukaNum = 0;

		// ���o���ꂽ�|���S���̐������J��Ԃ�
		for (i = 0; i < HitDim.HitNum; i++)
		{
			Vector3 hitDimNor = Vector3(HitDim.Dim[i].Normal.x, HitDim.Dim[i].Normal.y, HitDim.Dim[i].Normal.z);

			//�ǂ̏ꍇ
			if (Vector3::Dot(hitDimNor, Vector3::Up) < SLOPE_LIMIT) {
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (KabeNum < PLAYER_MAX_HITCOLL)
				{
					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					Kabe[KabeNum++] = &HitDim.Dim[i];
				}
			}
			//���̏ꍇ
			else{
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (YukaNum < PLAYER_MAX_HITCOLL)
				{
					// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
					Yuka[YukaNum++] = &HitDim.Dim[i];
				}
			}
		}
	}

	// �ǃ|���S���Ƃ̓����蔻�菈��
	if (KabeNum != 0)
	{
		// �ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		hitFlag = 0;

		// �ړ��������ǂ����ŏ����𕪊�
		if (moveFlag == 1)
		{
			// �ǃ|���S���̐������J��Ԃ�
			for (i = 0; i < KabeNum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Kabe[i];

				// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				//if (HitCheck_Capsule_Triangle(Vector3::Vector3ToVECTOR(curPosition), Vector3::Vector3ToVECTOR(curPosition), 5.0f, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;
				if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

				// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				hitFlag = 1;

				// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
				{
					//VECTOR SlideVec;	// �v���C���[���X���C�h������x�N�g��
					Vector3 slideVec;					
					Vector3 polyNormal = Vector3(Poly->Normal.x, Poly->Normal.y, Poly->Normal.z);

					// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
					slideVec = Vector3::Cross(dir, polyNormal);

					// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
					// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
					slideVec = Vector3::Cross(polyNormal, slideVec);

					// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
					curPosition = prePosition + slideVec;
				}

				// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				for (j = 0; j < KabeNum; j++)
				{
					// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Kabe[j];

					// �������Ă����烋�[�v���甲����
					if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) break;
				}

				// j �� KabeNum �������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
				// �ǂɓ��������t���O��|������Ń��[�v���甲����
				if (j == KabeNum)
				{
					hitFlag = 0;
					break;
				}
			}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�̏���

			// �ǃ|���S���̐������J��Ԃ�
			for (i = 0; i < KabeNum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Kabe[i];
				
				if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					hitFlag = 1;
					break;
				}
			}
		}

		// �ǂɓ������Ă�����ǂ��牟���o���������s��
		if (hitFlag == 1)
		{
			// �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (k = 0; k < PLAYER_HIT_TRYNUM; k++)
			{
				// �ǃ|���S���̐������J��Ԃ�
				for (i = 0; i < KabeNum; i++)
				{
					// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Kabe[i];

					// �v���C���[�Ɠ������Ă��邩�𔻒�
					//if (HitCheck_Capsule_Triangle(curPosition, VAdd(curPosition, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;
					if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

					Vector3 polyNormal = Vector3(Poly->Normal.x, Poly->Normal.y, Poly->Normal.z);

					// �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					curPosition = curPosition + polyNormal * PLAYER_HIT_SLIDE_LENGTH;

					// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for (j = 0; j < KabeNum; j++)
					{
						// �������Ă����烋�[�v�𔲂���
						Poly = Kabe[j];
						if (HitCheck_Sphere_Triangle(Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT, 0)), body_.component_.radius_, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
					}

					// �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
					if (j == KabeNum) break;
				}

				// i �� KabeNum �ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɑS�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if (i != KabeNum) break;
			}
		}
	}

	// ���|���S���Ƃ̓����蔻��
	if (YukaNum != 0)
	{
		//// �W�����v�����㏸���̏ꍇ�͏����𕪊�
		//if (pl.State == 2 && pl.JumpPower > 0.0f)
		//{
		//	float MinY;

		//	// �V��ɓ����Ԃ��鏈�����s��

		//	// ��ԒႢ�V��ɂԂ���ׂ̔���p�ϐ���������
		//	MinY = 0.0f;

		//	// �����������ǂ����̃t���O�𓖂����Ă��Ȃ����Ӗ�����O�ɂ��Ă���
		//	hitFlag = 0;

		//	// ���|���S���̐������J��Ԃ�
		//	for (i = 0; i < YukaNum; i++)
		//	{
		//		// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
		//		Poly = Yuka[i];

		//		// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
		//		LineRes = HitCheck_Line_Triangle(curPosition, VAdd(curPosition, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

		//		// �ڐG���Ă��Ȃ������牽�����Ȃ�
		//		if (LineRes.HitFlag == FALSE) continue;

		//		// ���Ƀ|���S���ɓ������Ă��āA�����܂Ō��o�����V��|���S����荂���ꍇ�͉������Ȃ�
		//		if (hitFlag == 1 && MinY < LineRes.Position.y) continue;

		//		// �|���S���ɓ��������t���O�𗧂Ă�
		//		hitFlag = 1;

		//		// �ڐG�����x���W��ۑ�����
		//		MinY = LineRes.Position.y;
		//	}

		//	// �ڐG�����|���S�������������ǂ����ŏ����𕪊�
		//	if (hitFlag == 1)
		//	{
		//		// �ڐG�����ꍇ�̓v���C���[�̂x���W��ڐG���W�����ɍX�V
		//		curPosition.y = MinY - PLAYER_HIT_HEIGHT;

		//		// �x�������̑��x�͔��]
		//		pl.JumpPower = -pl.JumpPower;
		//	}
		//}
		//else
		//{
			float MaxY;

			// ���~�����W�����v���ł͂Ȃ��ꍇ�̏���

			// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
			hitFlag = 0;

			// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
			MaxY = 0.0f;

			// ���|���S���̐������J��Ԃ�
			for (int i = 0; i < YukaNum; i++)
			{
				// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
				Poly = Yuka[i];

				//// �W�����v�����ǂ����ŏ����𕪊�
				//if (pl.State == 2)
				//{
				//	// �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
				//	LineRes = HitCheck_Line_Triangle(VAdd(curPosition, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(curPosition, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				//}
				//else
				//{
					// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
					LineRes = HitCheck_Line_Triangle(Vector3::Vector3ToVECTOR(curPosition), Vector3::Vector3ToVECTOR(curPosition + Vector3(0, CENTER_HEIGHT * 2, 0)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				//}


				// �������Ă��Ȃ������牽�����Ȃ�
				if (LineRes.HitFlag == FALSE) continue;

				// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
				if (hitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// �|���S���ɓ��������t���O�𗧂Ă�
				hitFlag = 1;

				// �ڐG�����x���W��ۑ�����
				MaxY = LineRes.Position.y;
			}

			// ���|���S���ɓ����������ǂ����ŏ����𕪊�
			if (hitFlag == 1)
			{
				// ���������ꍇ

				// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
				curPosition.y = MaxY/* + CENTER_HEIGHT*/;

				//// �x�������̈ړ����x�͂O��
				//pl.JumpPower = 0.0f;

				//// �����W�����v���������ꍇ�͒��n��Ԃɂ���
				//if (pl.State == 2)
				//{
				//	// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
				//	if (moveFlag)
				//	{
				//		// �ړ����Ă���ꍇ�͑����Ԃ�
				//		Player_PlayAnim(1);
				//		pl.State = 1;
				//	}
				//	else
				//	{
				//		// �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
				//		Player_PlayAnim(4);
				//		pl.State = 0;
				//	}

				//	// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
				//	pl.AnimBlendRate = 1.0f;
				//}
			}
			//else
			//{
			//	// ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ��
			//	if (pl.State != 2)
			//	{
			//		// �W�����v���ɂ���
			//		pl.State = 2;

			//		// ������Ƃ����W�����v����
			//		pl.JumpPower = PLAYER_FALL_UP_POWER;

			//		// �A�j���[�V�����͗������̂��̂ɂ���
			//		Player_PlayAnim(3);
			//	}
			//}
		//}
	}

	// �V�������W��ۑ�����
	position_ = Vector3::Lerp(position_, curPosition, 0.8f);

	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(modelHandle_, Vector3::Vector3ToVECTOR(position_));

	// ���o�����v���C���[�̎��͂̃|���S�������J������
	MV1CollResultPolyDimTerminate(HitDim);


	
}
