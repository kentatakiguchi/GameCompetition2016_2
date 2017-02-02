#include "ClearScreen.h"
#include"../../Input/InputMgr.h"
#include"../../Renderer/FontManager.h"
#include"../../Define.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include"../../Game/Time.h"

const static int FONT_SIZE = 64;

ClearScreen::ClearScreen()
{
	Count_ = 120;
	ints = 0;
	anmer_ = StageClearTextAnm();
}

bool ClearScreen::update(std::string name, Scene& next)
{
	anmer_.update_e(Time::GetInstance().deltaTime());
	Count_--;
	ints += 10;
	if (Count_<=0) {
		next = Scene::StageClear;
		//if (name == "stage04")next = Scene::BossStage01;
		//else next = Scene::GamePlay;
		
		return true;
	}
	return false;
}

void ClearScreen::draw() const
{	

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(ints));
	DrawGraph(0, 0, ResourceLoader::GetInstance().getTextureID(TextureID::PAUSE_BACK_TEX), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int center, count, heightPoint;
	//int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	int forcount = 0;
	center = static_cast<int>(SCREEN_SIZE.x) / 2;

	anmer_.draw_e(Vector2(static_cast<float>(center), 200), Vector2::Zero, 1.5);

	//DrawGraph(center - 320, static_cast<int>(textPosList.at(count).y), ResourceLoader::GetInstance().getTextureID(textIDs.at(1)), TRUE);
	//DrawGraph(center - 320, static_cast<int>(textPosList.at(count).y + 160), ResourceLoader::GetInstance().getTextureID(textIDs.at(2)), TRUE);

	//for (auto lists : listBase) {
	//	for (auto my : lists) {
	//		if (count == 0)break;

	//		strLen = strlen(my.c_str());
	//		strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));

	//		//if (forcount == targetPoint && forcount != 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(sin(sinCount*MathHelper::Pi / 180)) * 255));
	//		//DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));


	//		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//		heightPoint++;
	//	}
	//	forcount++;
	//	count++;
	//	heightPoint = 0;
	//}


	//int strLen, strWidth, center, count, heightPoint;
	//count = 0;
	//heightPoint = 0;
	//for (auto lists : listBase) {
	//	for (auto my : lists) {
	//		strLen = strlen(my.c_str());
	//		strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
	//		center = static_cast<int>(SCREEN_SIZE.x) / 2;
	//		//DrawStringToHandle(center - (strWidth / 2), static_cast<int>(textPosList.at(count).y) + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
	//		
	//		DrawGraph(center - 320, static_cast<int>(textPosList.at(count).y), ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);

	//		heightPoint++;
	//	}
	//	count++;
	//	heightPoint = 0;
	//}
}
