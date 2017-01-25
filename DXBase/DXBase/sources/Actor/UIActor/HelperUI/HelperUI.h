#ifndef HELPER_UI_H_
#define HELPER_UI_H_

#include "../../Base/ActorUI.h"
#include <vector>

class HelperUI : public ActorUI {
public:
	HelperUI(IWorld* world, const Vector2& position);
	~HelperUI();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

public:
	// �\������e�L�X�g�̔ԍ���ݒ肵�܂�
	void setTextNumver(const int number);
	// ������`�悷�邩��Ԃ��܂�
	void setIsTextDraw(const bool isDraw);

private:
	int textNum_;		// �`�悷�镶���ԍ�
	bool isTextDraw_;	// ������`�悷�邩 
	// �����R���e�i
	typedef std::vector<int> TextContainer;
	TextContainer drawTexes_;
};

#endif