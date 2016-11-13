#include "PauseScreen.h"
#include"../../Input/InputMgr.h"
#include"../../Renderer/FontManager.h"
#include"../../Define.h"
#include"../../ResourceLoader/ResourceLoader.h"

const static int FONT_SIZE = 64;

PauseScreen::PauseScreen()
{

	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("Tボタンでゲームに戻る");
	list1.push_back("ENTERボタンでタイトルへ");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 800));
	changeTextList.clear();

}

bool PauseScreen::update(Scene& next)
{
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) {
		next = Scene::Title;
		return true;
	}
	return false;
}

void PauseScreen::draw() const
{
	DrawGraph(0, 0,ResourceLoader::GetInstance().getTextureID(TextureID::PAUSE_BACK_TEX), TRUE);

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
