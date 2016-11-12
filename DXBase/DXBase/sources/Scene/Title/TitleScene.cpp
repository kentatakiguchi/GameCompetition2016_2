#include "TitleScene.h"

TitleScene::TitleScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "Title";


	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("タイトル");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("SPACEボタンでゲームスタート");
	listBase[1] = list2;
	textPosList.push_back(Vector2(200, 500));
	changeTextList.clear();

}

TitleScene::~TitleScene(){}

void TitleScene::start() {
	isEnd_ = false;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
}

void TitleScene::update() {
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))
	{
		keeper_->setSceneName("stage03");
		isEnd_ = true;
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::A))
	{
		//ステージ１へ
		keeper_->setSceneName("stage03");
		isEnd_ = true;
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::S))
	{
		//ステージ１へ
		keeper_->setSceneName("stage01");
		isEnd_ = true;
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::D))
	{
		//ステージ１へ
		keeper_->setSceneName("stage02");
		isEnd_ = true;
	}
}

void TitleScene::draw() const {
	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
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

}

void TitleScene::end() {}

bool TitleScene::isEnd() const {
	return isEnd_;
}

Scene TitleScene::next() const {
	return Scene::GamePlay;
}
