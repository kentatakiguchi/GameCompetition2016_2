#include "ClearScreen.h"
#include"../../Input/InputMgr.h"
#include"../../Renderer/FontManager.h"
#include"../../Define.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include"../../Game/Time.h"

const static int FONT_SIZE = 64;

ClearScreen::ClearScreen(SceneDataKeeper* keeper):keeper_(keeper)
{
	Count_ = 300;
	ints = 0;
	anmer_ = StageClearTextAnm();
	
	numberTexes_.push_back(TextureID::NUMBER_ZERO_TEX);
	numberTexes_.push_back(TextureID::NUMBER_ONE_TEX);
	numberTexes_.push_back(TextureID::NUMBER_TWO_TEX);
	numberTexes_.push_back(TextureID::NUMBER_THREE_TEX);
	numberTexes_.push_back(TextureID::NUMBER_FOUR_TEX);
	numberTexes_.push_back(TextureID::NUMBER_FIVE_TEX);
	numberTexes_.push_back(TextureID::NUMBER_SIX_TEX);
	numberTexes_.push_back(TextureID::NUMBER_SEVEN_TEX);
	numberTexes_.push_back(TextureID::NUMBER_EIGHT_TEX);
	numberTexes_.push_back(TextureID::NUMBER_NINE_TEX);

	int center = static_cast<int>(SCREEN_SIZE.x) / 2;
	
	textPositions["stageclear"] = Vector2(center, -40);
	textPositions["getStar"] = Vector2(80, 100);
	textPositions["getStarStar"] = Vector2(520, 100);
	textPositions["getStarStarCount"] = Vector2(700, 100);
	textPositions["maxDash"] = Vector2(80, 200);
	textPositions["maxDashMult"] = Vector2(550, 200);
	textPositions["maxDashMultCount"] = Vector2(700, 200);
	textPositions["WalkBlockCount"] = Vector2(1000, 200);
	textPositions["WalkBlockCountMult"] = Vector2(1450, 200);
	textPositions["WalkBlockCountMultcount"] = Vector2(1600, 200);
	textPositions["5Dash"] = Vector2(100, 290);
	textPositions["5DashMult"] = Vector2(550, 290);
	textPositions["5DashMultCount"] = Vector2(700, 290);
	textPositions["YellowStar"] = Vector2(1000, 300);
	textPositions["YellowStarMult"] = Vector2(1450, 300);
	textPositions["YellowStarMultCount"] = Vector2(1600, 300);
	textPositions["4Dash"] = Vector2(100, 380);
	textPositions["4DashMult"] = Vector2(550, 380);
	textPositions["4DashMultCount"] = Vector2(700, 380);
	//textPositions["PurpleStar"] = Vector2(1000, 400);
	//textPositions["PurpleStarMult"] = Vector2(1450, 400);
	//textPositions["PurpleStarMultCount"] = Vector2(1600, 400);
	textPositions["3Dash"] = Vector2(100, 470);
	textPositions["3DashMult"] = Vector2(550, 470);
	textPositions["3DashMultCount"] = Vector2(700, 470);
	textPositions["StickWall"] = Vector2(1000, 470);
	textPositions["StickWallMult"] = Vector2(1450, 470);
	textPositions["StickWallMultCount"] = Vector2(1600, 470);
	textPositions["2Dash"] = Vector2(100, 560);
	textPositions["2DashMult"] = Vector2(550, 560);
	textPositions["2DashMultCount"] = Vector2(700, 560);
	textPositions["EnemyBonus"] = Vector2(1000, 610);
	textPositions["EnemyBonusMult"] = Vector2(1050, 720);
	textPositions["EnemyBonusMultCount"] = Vector2(1200, 720);
	textPositions["DamageCount"] = Vector2(80, 650);
	textPositions["DamageCountMinus"] = Vector2(550, 650);
	textPositions["DamageCountMinusCount"] = Vector2(700, 650);
	textPositions["ChargeTime"] = Vector2(80, 740);
	textPositions["ChargeTimeMinus"] = Vector2(550, 740);
	textPositions["ChargeTimeMinusCount"] = Vector2(700, 740);
	textPositions["Total"] = Vector2(center - 114 / 2, 850);
	textPositions["TotalMult"] = Vector2(1350, 850);
	textPositions["TotalMultCount"] = Vector2(1520, 850);
	textPositions["TotalGetStar"] = Vector2(550, 950);
	textPositions["TotalGetStarCount"] = Vector2(700, 950);

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
		//keeper_->addResultJump(keeper_->getJumpCount());
		//keeper_->addResultDamage(keeper_->getDamageCount());
		return true;
	}
	return false;
}

void ClearScreen::draw() const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(ints));
	DrawGraph(0, 0, ResourceLoader::GetInstance().getTextureID(TextureID::PAUSE_BACK_TEX), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int center, count, heightPoint, multAddCount;
	multAddCount = 0;
	//int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	int forcount = 0;
	center = static_cast<int>(SCREEN_SIZE.x) / 2;

	//anmer_.draw_e(Vector2(static_cast<float>(center), 0), Vector2::Zero, 1);
	anmer_.draw_e(textPositions.at("stageclear"));

	DrawGraph(textPositions.at("getStar").x, textPositions.at("getStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_GETSTAR_TEX), TRUE);
	DrawGraph(textPositions.at("getStarStar").x, textPositions.at("getStarStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
	int drawNum = keeper_->GetItemCount();
	int baseNum = keeper_->GetItemCount();
	drawNumber(drawNum, baseNum,
		textPositions.at("getStarStarCount").x, textPositions.at("getStarStarCount").y);
	DrawGraph(textPositions.at("maxDash").x, textPositions.at("maxDash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MAXCOMBO_TEX), TRUE);
	DrawGraph(textPositions.at("maxDashMult").x, textPositions.at("maxDashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->maxComboGet();
	baseNum = keeper_->maxComboGet();
	multAddCount += keeper_->maxComboGet();
	drawNumber(drawNum, baseNum,
		textPositions.at("maxDashMultCount").x, textPositions.at("maxDashMultCount").y);
	DrawGraph(textPositions.at("WalkBlockCount").x, textPositions.at("WalkBlockCount").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_WALK_BLOCK_COUNT_TEX), TRUE);
	DrawGraph(textPositions.at("WalkBlockCountMult").x, textPositions.at("WalkBlockCountMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getMoveDistance() / CHIPSIZE;
	baseNum = keeper_->getMoveDistance() / CHIPSIZE;
	multAddCount += (keeper_->getMoveDistance() / CHIPSIZE);
	drawNumber(drawNum, baseNum,
		textPositions.at("WalkBlockCountMultcount").x, textPositions.at("WalkBlockCountMultcount").y);
	DrawGraph(textPositions.at("5Dash").x, textPositions.at("5Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO5_TEX), TRUE);
	DrawGraph(textPositions.at("5DashMult").x, textPositions.at("5DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getComboCount(5);
	baseNum = keeper_->getComboCount(5);
	multAddCount += keeper_->getComboCount(5);
	drawNumber(drawNum, baseNum,
		textPositions.at("5DashMultCount").x, textPositions.at("5DashMultCount").y);
	DrawGraph(textPositions.at("YellowStar").x, textPositions.at("YellowStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_STAR_COUNT_TEX), TRUE);
	DrawGraph(textPositions.at("YellowStarMult").x, textPositions.at("YellowStarMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getPlusStar()/keeper_->GetMaxItemCount();
	baseNum = keeper_->getPlusStar() / keeper_->GetMaxItemCount();
	multAddCount += keeper_->getPlusStar() / keeper_->GetMaxItemCount();
	drawNumber(drawNum, baseNum,
		textPositions.at("YellowStarMultCount").x, textPositions.at("YellowStarMultCount").y);
	DrawGraph(textPositions.at("4Dash").x, textPositions.at("4Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO4_TEX), TRUE);
	DrawGraph(textPositions.at("4DashMult").x, textPositions.at("4DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getComboCount(4);
	baseNum = keeper_->getComboCount(4);
	multAddCount += keeper_->getComboCount(4);
	drawNumber(drawNum, baseNum,
		textPositions.at("4DashMultCount").x, textPositions.at("4DashMultCount").y);
	//DrawGraph(textPositions.at("PurpleStar").x, textPositions.at("PurpleStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MINUS_STAR_COUNT_TEX), TRUE);
	//DrawGraph(textPositions.at("PurpleStarMult").x, textPositions.at("PurpleStarMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	//drawNum = keeper_->getMinusStar();
	//baseNum = keeper_->getMinusStar();
	//multAddCount+= keeper_->getMinusStar();
	//drawNumber(drawNum, baseNum,
	//	textPositions.at("PurpleStarMultCount").x, textPositions.at("PurpleStarMultCount").y);
	DrawGraph(textPositions.at("3Dash").x, textPositions.at("3Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO3_TEX), TRUE);
	DrawGraph(textPositions.at("3DashMult").x, textPositions.at("3DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getComboCount(3);
	baseNum = keeper_->getComboCount(3);
	multAddCount += keeper_->getComboCount(3);
	drawNumber(drawNum, baseNum,
		textPositions.at("3DashMultCount").x, textPositions.at("3DashMultCount").y);
	DrawGraph(textPositions.at("StickWall").x, textPositions.at("StickWall").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_STICK_COUNT_TEX), TRUE);
	DrawGraph(textPositions.at("StickWallMult").x, textPositions.at("StickWallMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getHoldCount();
	baseNum = keeper_->getHoldCount();
	multAddCount += keeper_->getHoldCount();
	drawNumber(drawNum, baseNum,
		textPositions.at("StickWallMultCount").x, textPositions.at("StickWallMultCount").y);
	DrawGraph(textPositions.at("2Dash").x, textPositions.at("2Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO2_TEX), TRUE);
	DrawGraph(textPositions.at("2DashMult").x, textPositions.at("2DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = keeper_->getComboCount(2);
	baseNum = keeper_->getComboCount(2);
	multAddCount += keeper_->getComboCount(2);
	drawNumber(drawNum, baseNum,
		textPositions.at("2DashMultCount").x, textPositions.at("2DashMultCount").y);

	if (keeper_->getEnemyCount() == 0) {
		DrawGraph(textPositions.at("EnemyBonus").x, textPositions.at("EnemyBonus").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_NoENEMY_DEATH_TEX), TRUE);
		DrawGraph(textPositions.at("EnemyBonusMult").x, textPositions.at("EnemyBonusMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = 100;
		baseNum = 100;
		multAddCount += 100;
		drawNumber(drawNum, baseNum,
			textPositions.at("EnemyBonusMultCount").x, textPositions.at("EnemyBonusMultCount").y);
	}
	DrawGraph(textPositions.at("DamageCount").x, textPositions.at("DamageCount").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_DAMAGE_COUNT_TEX), TRUE);
	DrawGraph(textPositions.at("DamageCountMinus").x, textPositions.at("DamageCountMinus").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MINUS_MULT_TEX), TRUE);
	drawNum = keeper_->getDamageCount();
	baseNum = keeper_->getDamageCount();
	multAddCount -= keeper_->getDamageCount();
	drawNumber(drawNum, baseNum,
		textPositions.at("DamageCountMinusCount").x, textPositions.at("DamageCountMinusCount").y);
	DrawGraph(textPositions.at("ChargeTime").x, textPositions.at("ChargeTime").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_CHARGETIME_TEX), TRUE);
	DrawGraph(textPositions.at("ChargeTimeMinus").x, textPositions.at("ChargeTimeMinus").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MINUS_MULT_TEX), TRUE);
	drawNum = keeper_->getChargeTime();
	baseNum = keeper_->getChargeTime();
	multAddCount -= keeper_->getChargeTime();
	drawNumber(drawNum, baseNum,
		textPositions.at("ChargeTimeMinusCount").x, textPositions.at("ChargeTimeMinusCount").y);
	DrawGraph(textPositions.at("Total").x, textPositions.at("Total").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_TOTAL_TEX), TRUE);
	DrawGraph(textPositions.at("TotalMult").x, textPositions.at("TotalMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	drawNum = multAddCount;
	baseNum = multAddCount;
	drawNumber(drawNum, baseNum,
		textPositions.at("TotalMultCount").x, textPositions.at("TotalMultCount").y);
	DrawGraph(textPositions.at("TotalGetStar").x, textPositions.at("TotalGetStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
	drawNum = multAddCount*keeper_->GetItemCount();
	baseNum = multAddCount*keeper_->GetItemCount();
	drawNumber(drawNum, baseNum,
		textPositions.at("TotalGetStarCount").x, textPositions.at("TotalGetStarCount").y,11);


	//int posCount = 0;
	//std::vector<int> drawNumberList;

	//drawNumber(drawNum, baseNum,
	//	(SCREEN_SIZE.x / 2), 750);
	
	//for (int i = 0;;) {

	//	if (baseNum < 10) {
	//		drawNumberList.push_back(baseNum);
	//		//DrawGraph((SCREEN_SIZE.x - CountPos)
	//		//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[baseNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[baseNum]), TRUE);
	//		break;
	//	}

	//	drawNum = (int)(baseNum*0.1);
	//	drawNum = drawNum * 10;
	//	int textNum = baseNum - drawNum;

	//	drawNumberList.push_back(textNum);
	//	//DrawGraph((SCREEN_SIZE.x - CountPos) 
	//	//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[textNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[textNum]), TRUE);

	//	baseNum = (int)(baseNum*0.1);
	//	posCount++;
	//	//DrawFormatString(SCREEN_SIZE.x - 100, 50, GetColor(0, 0, 0), "%d", );
	//}
	//int drawPosCount = drawNumberList.size() - 1;
	//for (int i = 0; i < (int)drawNumberList.size(); i++) {

	//	DrawGraph((int)((SCREEN_SIZE.x - CountPos)
	//		+ ResourceLoader::GetInstance().GetTextureSize(numberTexes_[drawNumberList[i]]).x*drawPosCount), 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[drawNumberList[i]]), TRUE);

	//	drawPosCount--;
	//}


	//drawNum = keeper_->getJumpCount();
	//baseNum = keeper_->getJumpCount();
	//posCount = 0;
	//drawNumberList.clear();

	//for (int i = 0;;) {

	//	if (baseNum < 10) {
	//		drawNumberList.push_back(baseNum);
	//		//DrawGraph((SCREEN_SIZE.x - CountPos)
	//		//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[baseNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[baseNum]), TRUE);
	//		break;
	//	}

	//	drawNum = (int)(baseNum*0.1);
	//	drawNum = drawNum * 10;
	//	int textNum = baseNum - drawNum;

	//	drawNumberList.push_back(textNum);
	//	//DrawGraph((SCREEN_SIZE.x - CountPos) 
	//	//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[textNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[textNum]), TRUE);

	//	baseNum = (int)(baseNum*0.1);
	//	posCount++;
	//	//DrawFormatString(SCREEN_SIZE.x - 100, 50, GetColor(0, 0, 0), "%d", );
	//}
	//drawPosCount = drawNumberList.size() - 1;
	//for (int i = 0; i < (int)drawNumberList.size(); i++) {

	//	DrawGraph((int)((SCREEN_SIZE.x / 2)
	//		+ ResourceLoader::GetInstance().GetTextureSize(numberTexes_[drawNumberList[i]]).x*drawPosCount), 600, ResourceLoader::GetInstance().getTextureID(numberTexes_[drawNumberList[i]]), TRUE);

	//	drawPosCount--;
	//}

	//drawNum = keeper_->getDamageCount();
	//baseNum = keeper_->getDamageCount();
	//posCount = 0;
	//drawNumberList.clear();

	//for (int i = 0;;) {

	//	if (baseNum < 10) {
	//		drawNumberList.push_back(baseNum);
	//		//DrawGraph((SCREEN_SIZE.x - CountPos)
	//		//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[baseNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[baseNum]), TRUE);
	//		break;
	//	}

	//	drawNum = (int)(baseNum*0.1);
	//	drawNum = drawNum * 10;
	//	int textNum = baseNum - drawNum;

	//	drawNumberList.push_back(textNum);
	//	//DrawGraph((SCREEN_SIZE.x - CountPos) 
	//	//	- ResourceLoader::GetInstance().GetTextureSize(numberTexes_[textNum]).x*posCount, 50, ResourceLoader::GetInstance().getTextureID(numberTexes_[textNum]), TRUE);

	//	baseNum = (int)(baseNum*0.1);
	//	posCount++;
	//	//DrawFormatString(SCREEN_SIZE.x - 100, 50, GetColor(0, 0, 0), "%d", );
	//}
	//drawPosCount = drawNumberList.size() - 1;
	//for (int i = 0; i < (int)drawNumberList.size(); i++) {

	//	DrawGraph((int)((SCREEN_SIZE.x / 2)
	//		+ ResourceLoader::GetInstance().GetTextureSize(numberTexes_[drawNumberList[i]]).x*drawPosCount), 750, ResourceLoader::GetInstance().getTextureID(numberTexes_[drawNumberList[i]]), TRUE);

	//	drawPosCount--;
	//}

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
