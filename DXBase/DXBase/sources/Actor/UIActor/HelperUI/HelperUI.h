#ifndef HELPER_UI_H_
#define HELPER_UI_H_

#include "../../Base/ActorUI.h"
#include <vector>

class HelperUI : public ActorUI {
	HelperUI(IWorld* world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	typedef std::vector<std::string> TextContainer;
	TextContainer drawTex_;
};

#endif