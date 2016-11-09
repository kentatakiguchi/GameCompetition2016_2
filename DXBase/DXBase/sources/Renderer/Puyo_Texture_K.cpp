#include "Puyo_Texture_K.h"
#include "../Game/Time.h"
#include "../Math/MathHelper.h"
#include "../Input/InputMgr.h"
#include "../Math/Matrix.h"
#include "../Math/Vector3.h"
//�ꉞ�����`�ōl����

const int SplitSize = 8.0f;
PuyoTextureK::PuyoTextureK(TextureID tex, Vector2 pos, Vector2 scale, float rotate) :
	textureIndex(ResourceLoader::GetInstance().getTextureID(tex)),
	textureSize(ResourceLoader::GetInstance().GetTextureSize(tex)),
	mPosition(pos),
	mScale(scale),
	mRotate(rotate)
{
	loopX = textureSize.x / SplitSize;
	loopY = textureSize.y / SplitSize;
	PuyoGraphSplit();
	PuyoGraphVertex();
	//�o�l�萔
	spring_constant_ = 15.0f;
	//�����萔
	attenuation_constant_ = 0.8f;
	//����
	mass_ = 0.3f;
	//�p�U����
	angular_freq_ = std::sqrtf(spring_constant_ / mass_);
	p_ = attenuation_constant_ / 2 / mass_;
	e_ = 2.7f;

	time = 0.0f;
}

PuyoTextureK::~PuyoTextureK()
{
}

void PuyoTextureK::SetPosition(Vector2 pos, Vector2 scale, float rotate)
{
	mPosition = pos;
	mScale = scale;
	mRotate = rotate;
}

void PuyoTextureK::PuyoUpdate()
{
	//���_�̃o�l�n�𖈃t���[���X�V
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			Vector2 pos = Vector2(x*SplitSize, y*SplitSize);
			//��]�ƃX�P�[���̃}�g���N�X���쐬
			Matrix mat;
			mat =
				Matrix::CreateTranslation(Vector3(pos.x, pos.y, 0.0f))*
				Matrix::CreateScale(Vector3(mScale.x, mScale.y, 0.0f))*
				Matrix::CreateRotationZ(mRotate);
			//�S���_�̎��Ԃ�i�߂�(�U�����`��鎞�Ԃ��z��)
			commonVertexH[x][y].vibrationTimer += 1.0f*Time::GetInstance().deltaTime();
			if(commonVertexH[x][y].vibrationTimer>= commonVertexH[x][y].vibrationTime)
			commonVertexH[x][y].time += 1.0f*Time::GetInstance().deltaTime();
			//�o�l���l�������_�̍��W����
			commonVertexH[x][y].position.x = mat.Translation().x + (commonVertexH[x][y].amplitude *
				std::pow(e_, -p_ * commonVertexH[x][y].time) *
				std::sin(angular_freq_ * commonVertexH[x][y].time + phase_.x))*commonVertexH[x][y].velocity.x;
			commonVertexH[x][y].position.y = mat.Translation().y + (commonVertexH[x][y].amplitude *
				std::pow(e_, -p_ * commonVertexH[x][y].time) *
				std::sin(angular_freq_ * commonVertexH[x][y].time + phase_.x))*commonVertexH[x][y].velocity.y;
		}
	}
	time += Time::GetInstance().deltaTime();
	test.x += (20 *
		std::pow(e_, -p_ * time) *
		std::sin(angular_freq_ * time + phase_.x));
	//���_���𖈃t���[���X�V
	PuyoVertexSet();
	//timer += Time::GetInstance().deltaTime();
	//float omega0= 5.0f;
	//float K = 1.0f;
	//float f = 100.0f;
	//float omega = 10.0f;/*std::sqrtf(spring_constant_ / mass_);*/

	//float A = f / (std::powf(omega0, 2) -
	//	std::powf(omega, 2) + std::powf(2 * omega*K, 2));

	//float aa = std::powf(6, 2);

	//float tan = (2 * omega*K) / (std::powf(omega0, 2)) 
	//	- std::powf(omega, 2);

	//float del = std::atanf(tan);

	//test.x = A*std::cosf(omega*timer - del);

	//time_ += 5.0f*Time::GetInstance().deltaTime();

	//position_.x = 200 + amplitude_ * std::pow(e_ ,-p_ * time_) * std::sin(angular_freq_ * time_ + phase_.x);
	//position_.y = 200 + amplitude_ * std::pow(e_, -p_ * time_) * std::sin(angular_freq_ * time_ + phase_.y);
}

void PuyoTextureK::PuyoDraw()
{
	//�`��
	for (int y = 0; y < loopY; y++)
	{
		for (int x = 0; x < loopX; x++)
		{
			VertexPos vp = spriteVertexH[x][y];
			DrawModiGraphF(
				vp.LeftTopPos.x, vp.LeftTopPos.y,
				vp.RightTopPos.x, vp.RightTopPos.y,
				vp.RightDownPos.x, vp.RightDownPos.y,
				vp.LeftDownPos.x, vp.LeftDownPos.y,
				spriteIndexsH[x][y],TRUE);
		}
	}

	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			DrawCircle(commonVertexH[x][y].position.x + mPosition.x, commonVertexH[x][y].position.y + mPosition.y, 1, GetColor(255, 255, 255));
		}
	}
	//DrawCircle(test.x, test.y, 10, GetColor(255, 255, 0));
	//DrawFormatString(500,500, GetColor(255, 255, 255), "���W:%f,%f",test.x,test.y);
}

void PuyoTextureK::PuyoGraphSplit()
{
	//���������摜������
	for (int y = 0; y < loopY; y++)
	{
		for (int x = 0; x < loopX; x++)
		{
			//�E��̍��W
			Vector2 splitLeftUp;
			splitLeftUp = Vector2(x*SplitSize, y*SplitSize);
			spriteIndexsH[x][y] = DerivationGraph(splitLeftUp.x, splitLeftUp.y, SplitSize, SplitSize, textureIndex);
		}
	}
}

void PuyoTextureK::PuyoGraphVertex()
{
	//�摜�ɒ��_��ł�
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			commonVertexH[x][y].position = Vector2(x*SplitSize, y*SplitSize);
		}
	}
	PuyoVertexSet();
}

void PuyoTextureK::PuyoVertexSet()
{
	//���_���𕪊��摜�ɂ����
	for (int y = 0; y < loopY; y++)
	{
		for (int x = 0; x < loopX; x++)
		{
			VertexPos vertex;
			vertex.LeftTopPos = commonVertexH[x][y].position + mPosition;
			vertex.LeftDownPos = commonVertexH[x][y + 1].position + mPosition;
			vertex.RightTopPos = commonVertexH[x + 1][y].position + mPosition;
			vertex.RightDownPos = commonVertexH[x + 1][y + 1].position + mPosition;
			spriteVertexH[x][y] = vertex;
		}
	}
}

void PuyoTextureK::PuyoAddPower(int x_, int y_,Vector2 velocity)
{
	float Amplitude = 15.0f;
	//�����ɍs���قǂӂ蕝��������
	float AmplitudeVib = 1.0f;
	float count = 0;

	for (int y = 0; y <= 6; y++)
	{
		AmplitudeVib = y + 1;
		count = 0;
		for (int x = 0; x <= 6; x++)
		{
			if (count >= AmplitudeVib)
				AmplitudeVib++;
			count++;

			if ((x + x_) <= 16 && (y + y_) <= 16 &&
				(x + x_) >= 0 && (y + y_) >= 0)
			{
				commonVertexH[x + x_][y + y_].amplitude = Amplitude / AmplitudeVib;
				commonVertexH[x + x_][y + y_].time = 0.0f;
				commonVertexH[x + x_][y + y_].vibrationTimer = 0.0f;
				commonVertexH[x + x_][y + y_].vibrationTime += AmplitudeVib / 100.0f;
				commonVertexH[x + x_][y + y_].velocity = velocity;
			}
			if ((x + x_) <= 16 && (y_ - y) <= 16 &&
				(x + x_) >= 0 && (y_ - y) >= 0)
			{
				commonVertexH[x + x_][y_ - y].amplitude = Amplitude / AmplitudeVib;
				commonVertexH[x + x_][y_ - y].time = 0.0f;
				commonVertexH[x + x_][y_ - y].vibrationTimer = 0.0f;
				commonVertexH[x + x_][y_ - y].vibrationTime+= AmplitudeVib / 100.0f;
				commonVertexH[x + x_][y_ - y].velocity = velocity;
			}
			if ((x_ - x) <= 16 && (y_ - y) <= 16 &&
				(x_ - x) >= 0 && (y_ - y) >= 0)
			{
				commonVertexH[x_ - x][y_ - y].amplitude = Amplitude / AmplitudeVib;
				commonVertexH[x_ - x][y_ - y].time = 0.0f;
				commonVertexH[x_ - x][y_ - y].vibrationTimer = 0.0f;
				commonVertexH[x_ - x][y_ - y].vibrationTime += AmplitudeVib / 100.0f;
				commonVertexH[x_ - x][y_ - y].velocity = velocity;
			}
			if ((x_ - x) <= 16 && (y_ + y) <= 16 &&
				(x_ - x) >= 0 && (y_ + y) >= 0)
			{
				commonVertexH[x_ - x][y_ + y].amplitude = Amplitude / AmplitudeVib;
				commonVertexH[x_ - x][y_ + y].time = 0.0f;
				commonVertexH[x_ - x][y_ + y].vibrationTimer= 0.0f;
				commonVertexH[x_ - x][y_ + y].vibrationTime += AmplitudeVib / 100.0f;
				commonVertexH[x_ - x][y_ + y].velocity = velocity;
			}
		}
	}



	////�������܂�
	//for (int y = 0; y <= 5; y++)
	//{
	//	//�͂���������Ƃ����1�{�̗͂�����邽��+1
	//	AmplitudeVib = y + 1;
	//	//��Ɠ���
	//	count = 1;
	//	for (int x = 0; x <= 5; x++)
	//	{
	//		if (count > y + 1)
	//			AmplitudeVib++;
	//		count++;
	//		//�z�����������������
	//		if ((x_ + x) >= 0 && (x_ + x) <= 17 &&
	//			(y_ + y) >= 0 && (y_ + y) <= 17)
	//		{
	//			//�͂���������Ƃ��납��͂Ȃ��Ɨ͂��キ�Ȃ�
	//			commonVertexH[x_ + x][y_ + y].amplitude = Amplitude / AmplitudeVib;
	//			commonVertexH[x_ + x][y_ + y].time = 0.0f;
	//		}
	//		if ((x_ - x) >= 0 && (x_ - x) <= 17 &&
	//			(y_ - y) >= 0 && (y_ - y) <= 17 )
	//		{
	//			commonVertexH[x_ - x][y_ - y].amplitude = Amplitude / AmplitudeVib;
	//			commonVertexH[x_ - x][y_ - y].time = 0.0f;
	//		}
	//		if ((x_ + x) >= 0 && (x_ - x) <= 17 &&
	//			(y_ + y) >= 0 && (y_ - y) <= 17)
	//		{
	//			commonVertexH[x_ + x][y_ - y].amplitude = Amplitude / AmplitudeVib;
	//			commonVertexH[x_ + x][y_ - y].time = 0.0f;
	//		}
	//		if ((x_ - x) >= 0 && (x_ + x) <= 17 &&
	//			(y_ - y) >= 0 && (y_ + y) <= 17)
	//		{
	//			commonVertexH[x_ - x][y_ + y].amplitude = Amplitude / AmplitudeVib;
	//			commonVertexH[x_ - x][y_ + y].time = 0.0f;
	//		}
	//	}
	//}
}
