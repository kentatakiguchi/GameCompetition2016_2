#include "Camera.h"
#include "../../World/IWorld.h"
#include "../../Input/InputMgr.h"
#include"../Body/CollisionBase.h"

#define CAMERA_PLAYER_TARGET_HEIGHT		400.0f		// �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩

// �R���X�g���N�^
Camera::Camera(IWorld* world) :
	Actor(world, "Camera", { 0.0f,  0.0f }, CollisionBase()) {
	// �J�����̌�����������
	rotation_ *= Matrix::CreateFromAxisAngle(Vector3::Up, 90);
	rotation_ *= Matrix::CreateFromAxisAngle(getPose().Right(), 20);
	rotation_.NormalizeRotationMatrix();
}

// �X�V
void Camera::onUpdate(float deltaTime) {
	//(void)deltaTime;
	//// �v���[��������
	//auto player = world_->findActor("Player");
	//// �v���[�������Ȃ�
	//if (player == nullptr) return;

	//float yaw = 0.0f;
	//float pitch = 0.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::A))yaw = 1.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::D))yaw = -1.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::W))pitch =  1.0f;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::S))pitch = -1.0f;

	//// �v���[���̍��W���擾
	//target_ = player->getPosition() + Vector3(0.0f, 20.0f, 0.0f);

	//rotation_ *= Matrix::CreateFromAxisAngle(Vector3::Up, yaw);
	//rotation_ *= Matrix::CreateFromAxisAngle(getPose().Right(), pitch);
	//rotation_.NormalizeRotationMatrix();
	//Vector3 prePos = position_;
	//position_ = Vector3::Forward * 50;
	//position_ = position_ * rotation_ + target_;
	//position_ = Vector3::Lerp(position_, prePos, 0.8f);

	//const Vector3 local_position(0.0f, 1000.0f, 1000.0f);
	//const Matrix local_matrix = Matrix::CreateWorld(local_position, -local_position, Vector3::Up);
	//const Matrix world_matrix = local_matrix * Matrix::CreateRotationY(angle_) * player->getPose();
	//rotation_ = world_matrix.RotationMatrix();
	//position_ = world_matrix.Translation();
}

// �`��
void Camera::onDraw() const {
	//SetCameraNearFar(2.0f, 50000.0f);
	////�J�����̏������C�u�����̃J�����ɔ��f������
	//SetCameraPositionAndTarget_UpVecY(Vector3::Vector3ToVECTOR(position_), Vector3::Vector3ToVECTOR(target_));
	//const Vector3 eye = getPose().Translation();
	//const Vector3 at = eye + getPose().Forward();
	//const Vector3 up = getPose().Up();
	//SetCameraPositionAndTargetAndUpVec(Vector3::Vector3ToVECTOR(eye), Vector3::Vector3ToVECTOR(at), Vector3::Vector3ToVECTOR(up));
}

