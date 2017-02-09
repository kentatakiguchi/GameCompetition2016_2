#pragma once
#include <string>
#include "../ResourceLoader/ResourceID.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
class NumberTexture {
public:
	// �R���X�g���N�^
	NumberTexture(TextureID texture, int width, int height);
	// �`��
	void draw2(const Vector2& position, int num, int digit, Vector3 color, float scale = 1, char fill = '0') const;
	// �`��
	void draw(const Vector2& position, int num, Vector3 color, float scale = 1) const;
	// �`��
	void draw(const Vector2& position, const std::string& num, Vector3 color = Vector3(255, 255, 255), float scale = 1) const;

private:
	// �e�N�X�`��
	TextureID mTexture;
	// ��
	int		mWidth;
	// ����
	int		mHeight;
};