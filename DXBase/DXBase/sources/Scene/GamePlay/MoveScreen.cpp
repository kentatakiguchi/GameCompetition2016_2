#include "MoveScreen.h"
#include"../../Renderer/FontManager.h"
#include"../../Define.h"

MoveScreen::MoveScreen()
{
	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("�L�����ړ��FWASD�L�[ / �����L�[");
	list1.push_back("�z���FL_Shift / R_Shift");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("ENTER�{�^���Ń��U���g��");
	list2.push_back("A�{�^���ŃX�e�[�W�N���A");
	list2.push_back("T�{�^���Ń|�[�Y");
	listBase[1] = list2;
	textPosList.push_back(Vector2(200, 500));
	changeTextList.clear();

}

bool MoveScreen::update(std::string name,Scene & next)
{
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN))
	{
		next = Scene::GameOver;
		return true;
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::A))
	{
		if (name != "stage03")
		{
			next = Scene::StageClear;
		}
		else
		{
			next = Scene::GameClear;
		}
		return true;
	}
	return false;
}

void MoveScreen::draw() const
{
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
