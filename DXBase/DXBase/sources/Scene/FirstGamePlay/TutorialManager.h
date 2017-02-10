#pragma once

#include "../../Math/Vector2.h"

#include <string>
#include <unordered_map>

class IWorld;

enum ContentsEnum {
	NUMBER = 0,
	POSITION = 1,
	SPEEKER = 2,
	TEXT_FIRST = 3,
	TEXT_SECOND = 4
};

class TutorialManager {
	struct Elements {
		int posX;
		std::string speaker;
		std::string text1;
		std::string text2;
	};
public:
	TutorialManager();
	~TutorialManager();
	void load_csv(const std::string& file_name);
	void init(IWorld* world);
	void update(IWorld* world, float deltaTime);
	void draw()const;
	void changeTutorial();
	void changeTurn();
	bool isTutorialEnd();
	void stepText(float deltaTime);

private:
	float timer_;
	int textIndex_;

	typedef std::unordered_map<int, std::vector<Elements>> TutorialContents;
	TutorialContents contents_;

	Vector2& buttyPos_;
	Vector2& rettyPos_;
	Vector2 drawPos_;

	float alpha_;
	int color_;
	int currentTutorial_;
	int currentTurn_;
	std::string text1_;
	std::string text2_;
	Vector2 position_;
	Vector2 cameraPos_;
};
