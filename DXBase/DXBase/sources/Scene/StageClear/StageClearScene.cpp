#include "StageClearScene.h"

StageClearScene::StageClearScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "StageClear";

	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("�X�e�[�W�N���A");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("SPACE�{�^���Ŏ��X�e�[�W��");
	listBase[1] = list2;
	textPosList.push_back(Vector2(200, 500));
	changeTextList.clear();

}

StageClearScene::~StageClearScene() {

}

void StageClearScene::start() {
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	// �O���t�B�b�N�̃��[�h
	id = LoadGraph("./resources/Player.png");
}

void StageClearScene::update() {
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))	isEnd_ = true;
}

void StageClearScene::draw() const {

	int strLen, strWidth, center, count,heightPoint;
	count = 0;
	heightPoint=0;
	for (auto lists : listBase) {
		for (auto my : lists) {
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = SCREEN_SIZE.x / 2;
			DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			heightPoint++;
		}
		count++;
		heightPoint = 0;
	}


	//int strLen, strWidth, center;
	//for (int i = 0; i < changeTextList.size(); i++) {
	//	strLen = strlen(changeTextList[i].c_str());
	//	strWidth = GetDrawStringWidthToHandle(changeTextList[i].c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
	//	center = SCREEN_SIZE.x / 2;
	//	DrawStringToHandle(center - (strWidth / 2), 550 + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*i), changeTextList[i].c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
	//}

}

void StageClearScene::end() {

}

bool StageClearScene::isEnd() const {
	return isEnd_;
}

Scene StageClearScene::next() const {
	return Scene::GamePlay;
}
