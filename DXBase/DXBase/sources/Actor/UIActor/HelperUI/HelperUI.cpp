#include "HelperUI.h"
#include "../../../ResourceLoader/ResourceLoader.h"

HelperUI::HelperUI(IWorld * world, const Vector2 & position) :
	 ActorUI(world, position),
	textNum_(0),
	isTextDraw_(true)
{
	drawTexes_.clear();
	// auto a = ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_GAUGE_OUT_TEX);
	// �e�N�X�`���n���h�����i�[
	drawTexes_.push_back(
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX));
	/*drawTexes_.push_back(
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX));
	drawTexes_.push_back(
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX));*/
}

HelperUI::~HelperUI()
{
	drawTexes_.clear();
}

void HelperUI::onUpdate(float deltaTime)
{
	// �͈͊O�̖h�~����
	auto size = drawTexes_.size();
	if (textNum_ > size - 1 && textNum_ < 0)
		textNum_ = 0;
}

void HelperUI::onDraw() const
{
	// �L�����N�^�[�̕`��
	DrawGraph((int)position_.x, (int)position_.y,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_NEEDLE_TEX), true);
	// �����̕`��
	if (!isTextDraw_)return;
	auto pos = Vector2::Right * 100.0f + position_;
	DrawGraph((int)pos.x, (int)pos.y,
		drawTexes_[textNum_], true);
}

void HelperUI::setTextNumver(const int number)
{
	textNum_ = number;
}

// ������`�悷�邩��Ԃ��܂�
void HelperUI::setIsTextDraw(const bool isDraw)
{
	isTextDraw_ = isDraw;
}
