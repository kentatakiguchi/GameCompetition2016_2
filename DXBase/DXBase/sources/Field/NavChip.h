//#pragma once
//
//#include"MapChip.h"
//#include"../Define.h"
//
//class NavChip :public  MapChip {
//public:
//	//ãÛÇÃMapChipÇê∂ê¨
//	NavChip() {}
//	//navigationÉ`ÉbÉvÇÃê∂ê¨
//	NavChip(IWorld* world, Vector2& position);
//	NavChip(std::shared_ptr<NavChip> chip, IWorld* world, Vector2& position);
//	NavChip(NavChip& chip, IWorld* world, Vector2& position);
//	void set(Vector2& pos);
//	NavChip& operator = (std::shared_ptr<NavChip> other) {
//		return NavChip(other, world_, Vector2(0, 0));
//	};
//
//private:
//	virtual void onUpdate(float deltaTime);
//	virtual void onDraw() const override;
//	virtual void onCollide(Actor& other);
//};
