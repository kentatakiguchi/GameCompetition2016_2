#include "PlayerState_Attack.h"

#include "../../../../../../../../Define.h"
#include "../../../../../../../../Input/InputMgr.h"
#include "../../../../../../../../Scene/Base/SceneDataKeeper.h"

#include <algorithm>

PlayerState_Attack::PlayerState_Attack(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) : 
	PlayerState_AttackBase(butty, retty){}

