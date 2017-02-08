#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "../Base/IScene.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"
#include "../../Animation/Player/PlayerAnimation2D.h"

class GameOverScene : public IScene{
public:
	GameOverScene(SceneDataKeeper* keeper);
	~GameOverScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	int id;
	int targetPoint;
	int sinCount;

	std::map<int, TextureID> textIDs;
	std::map<int, Scene> nextScene;
	std::map<int, Vector2> textPoses;

	// �L�����A�j���[�V����
	PlayerAnimation2D mButtyAnim;
	PlayerAnimation2D mRettyAnim;
	Animation2D mBossAnim;
	Vector2 mBossPos;
	// �I�����̍��W
	Vector2 mCursorPos;
	float mBossScale;
	float mBossCount;
};

#endif