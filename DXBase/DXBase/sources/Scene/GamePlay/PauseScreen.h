#pragma once
#ifndef PAUSE_SCREEN_H_
#define PAUSE_SCREEN_H_

#include "DxLib.h"
#include"../Base/Scene.h"
#include<vector>

class PauseScreen {
public:
	PauseScreen();
	bool update(Scene& next);
	void draw() const;

private:
	std::vector<std::string> changeTextList;
	std::vector<std::vector<std::string>> listBase;
	std::vector<Vector2> textPosList;
};

#endif