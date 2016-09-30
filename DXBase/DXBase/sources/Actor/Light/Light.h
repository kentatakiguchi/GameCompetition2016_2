#ifndef LIGHT_H_
#define LIGHT_H_

#include "../Base/Actor.h"

class Light : public Actor {
public:
	// �R���X�g���N�^
	Light(IWorld* world, const Vector3& position);
private:
	// �`��
	virtual void onDraw() const override;
};

#endif

