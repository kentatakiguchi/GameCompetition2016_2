#pragma once

#include <memory>

class Player;
using PlayerPtr = std::shared_ptr<Player>;

class PlayerBody;
using PlayerBodyPtr = std::shared_ptr<PlayerBody>;

class PlayerConnector;
using PlayerCntrPtr = std::shared_ptr<PlayerConnector>;

class PlayerBodyCollider;
using PlayerBodyCollPtr = std::shared_ptr<PlayerBodyCollider>;

struct PlayerStruct {
public:
	PlayerStruct() : /*player_(nullptr),*/ retty_(nullptr), butty_(nullptr), cntr_(nullptr) {}
	PlayerStruct(/*const PlayerPtr& player,*/ const PlayerBodyPtr& butty, const PlayerBodyPtr& retty, const PlayerCntrPtr& cntr) : /*player_(player),*/ retty_(retty), butty_(butty), cntr_(cntr) {}
	//void set_player(const PlayerPtr& player) { player_ = player; }
	void set_retty(const PlayerBodyPtr& retty) { retty_ = retty; }
	void set_butty(const PlayerBodyPtr& butty) { butty_ = butty; }
	void set_cntr(const PlayerCntrPtr& cntr) { cntr_ = cntr; }
	//PlayerPtr& player() { return player_; }
	PlayerBodyPtr& retty() { return retty_; }
	PlayerBodyPtr& butty() { return butty_; }
	PlayerCntrPtr& cntr() { return cntr_; }

	//// �R�s�[�֎~
	//PlayerStruct(const PlayerStruct& other) = delete;
	//PlayerStruct& operator = (const PlayerStruct& other) = delete;
private:
	//// �v���C���[�|�C���^
	//PlayerPtr player_;
	// main�ƂȂ镔��
	PlayerBodyPtr retty_;
	// sub �ƂȂ镔��
	PlayerBodyPtr butty_;
	// �R�l�N�^�[
	PlayerCntrPtr cntr_;
};

