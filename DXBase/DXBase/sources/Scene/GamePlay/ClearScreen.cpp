#include "ClearScreen.h"
#include"../../Input/InputMgr.h"
#include"../../Renderer/FontManager.h"
#include"../../Define.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include"../../Game/Time.h"

const static int FONT_SIZE = 64;
static const int LeftSpaceSize = 90;
static const int RightSpaceSize = 100;
static const int RankPosx = 200;
static const int RankPosy = 900;
static const int StarPosx = 800;
static const int StarPosy = 1000;
static const int StarPos2_Rx = 850;
static const int StarPos2_Ry = 980;
static const int StarPos_Rx = 750;
static const int StarPos_Ry = 980;
static const int StarPos_Lx = 800;
static const int StarPos_Ly = 950;
static const int StarPos2_Lx = 750;
static const int StarPos2_Ly = 1000;
static const int StarPos3_Lx = 850;
static const int StarPos3_Ly = 1000;
ClearScreen::ClearScreen(SceneDataKeeper* keeper):keeper_(keeper), drawNumberController_(0), isMaxDraw_(false),baseLastDraw_(0),drawLastDraw_(0),isMusic_(false)
{
	ints = 0;
	usingIntCount = 0;
	usingBaseIntCount = 2;
	anmer_ = StageClearTextAnm();
	
	numberTexes_.resize(2);

	numberTexes_[0].push_back(TextureID::NUMBER_ZERO_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_ONE_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_TWO_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_THREE_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_FOUR_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_FIVE_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_SIX_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_SEVEN_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_EIGHT_TEX);
	numberTexes_[0].push_back(TextureID::NUMBER_NINE_TEX);

	numberTexes_[1].push_back(TextureID::NUMBER_R_ZERO_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_ONE_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_TWO_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_THREE_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_FOUR_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_FIVE_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_SIX_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_SEVEN_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_EIGHT_TEX);
	numberTexes_[1].push_back(TextureID::NUMBER_R_NINE_TEX);

	int center = static_cast<int>(SCREEN_SIZE.x) / 2;
	
	int leftDefPosCount = 0;
	int rightDefPosCount = 0;
	int basePos = 240;
	textPositions["stageclear"] = Vector2(center, -5);
	textPositions["getStar"] = Vector2(80, 140);
	textPositions["getStarStar"] = Vector2(520, 140);
	textPositions["getStarStarCount"] = Vector2(700, 140);
	textPositions["maxDash"] = Vector2(80, basePos+leftDefPosCount*LeftSpaceSize);
	textPositions["maxDashMult"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["maxDashMultCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	leftDefPosCount++;

	textPositions["WalkBlockCount"] = Vector2(1000, basePos);
	textPositions["WalkBlockCountMult"] = Vector2(1550, basePos);
	textPositions["WalkBlockCountMultcount"] = Vector2(1650, basePos);
	textPositions["5Dash"] = Vector2(100, basePos+leftDefPosCount*LeftSpaceSize);
	textPositions["5DashMult"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["5DashMultCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	rightDefPosCount++;
	leftDefPosCount++;

	textPositions["YellowStar"] = Vector2(1000, basePos+rightDefPosCount*RightSpaceSize);
	textPositions["YellowStarMult"] = Vector2(1550, basePos + rightDefPosCount*RightSpaceSize);
	textPositions["YellowStarMultCount"] = Vector2(1650, basePos + rightDefPosCount*RightSpaceSize);
	textPositions["4Dash"] = Vector2(100, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["4DashMult"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["4DashMultCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	rightDefPosCount++;
	leftDefPosCount++;

	//textPositions["PurpleStar"] = Vector2(1000, basePos+rightDefPosCount*RightSpaceSize);
	//textPositions["PurpleStarMult"] = Vector2(1450, basePos+rightDefPosCount*RightSpaceSize);
	//textPositions["PurpleStarMultCount"] = Vector2(1600, basePos+rightDefPosCount*RightSpaceSize);
	textPositions["3Dash"] = Vector2(100, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["3DashMult"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["3DashMultCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	//rightDefPosCount++;
	leftDefPosCount++;

	textPositions["StickWall"] = Vector2(1000, basePos + rightDefPosCount*RightSpaceSize);
	textPositions["StickWallMult"] = Vector2(1550, basePos + rightDefPosCount*RightSpaceSize);
	textPositions["StickWallMultCount"] = Vector2(1650, basePos + rightDefPosCount*RightSpaceSize);
	textPositions["2Dash"] = Vector2(100, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["2DashMult"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["2DashMultCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	rightDefPosCount++;
	leftDefPosCount++;

	textPositions["EnemyBonus"] = Vector2(1000, basePos + rightDefPosCount*RightSpaceSize);
	rightDefPosCount++;

	textPositions["EnemyBonusMult"] = Vector2(1000, basePos + rightDefPosCount*RightSpaceSize+50);
	textPositions["EnemyBonusMultCount"] = Vector2(1100, basePos + rightDefPosCount*RightSpaceSize+50);
	textPositions["DamageCount"] = Vector2(80, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["DamageCountMinus"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["DamageCountMinusCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	rightDefPosCount++;
	leftDefPosCount++;

	textPositions["ChargeTime"] = Vector2(80, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["ChargeTimeMinus"] = Vector2(600, basePos + leftDefPosCount*LeftSpaceSize);
	textPositions["ChargeTimeMinusCount"] = Vector2(700, basePos + leftDefPosCount*LeftSpaceSize);
	leftDefPosCount++;

	textPositions["Total"] = Vector2(center - 114 / 2, 850);
	textPositions["TotalMult"] = Vector2(1350, 850);
	textPositions["TotalMultCount"] = Vector2(1520, 850);
	textPositions["TotalGetStar"] = Vector2(SCREEN_SIZE.x-ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x, 950);
	textPositions["TotalGetStarCount"] = Vector2(SCREEN_SIZE.x, 950);
	//textPositions["TotalGetStarCount"] = Vector2(SCREEN_SIZE.x - ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x*11, 950);

	isDraw_["stageclear"] = false;
	isDraw_["getStar"] = false;
	isDraw_["getStarStar"] = false;
	isDraw_["getStarStarCount"] = false;
	isDraw_["maxDash"] = false;
	isDraw_["maxDashMult"] = false;
	isDraw_["maxDashMultCount"] = false;
	isDraw_["WalkBlockCount"] = false;
	isDraw_["WalkBlockCountMult"] = false;
	isDraw_["WalkBlockCountMultcount"] = false;
	isDraw_["5Dash"] = false;
	isDraw_["5DashMult"] = false;
	isDraw_["5DashMultCount"] = false;
	isDraw_["YellowStar"] = false;
	isDraw_["YellowStarMult"] = false;
	isDraw_["YellowStarMultCount"] = false;
	isDraw_["4Dash"] = false;
	isDraw_["4DashMult"] = false;
	isDraw_["4DashMultCount"] = false;
	//isDraw_["PurpleStar"] = false;
	//isDraw_["PurpleStarMult"] = false;
	//isDraw_["PurpleStarMultCount"] = false;
	isDraw_["3Dash"] = false;
	isDraw_["3DashMult"] = false;
	isDraw_["3DashMultCount"] = false;
	isDraw_["StickWall"] = false;
	isDraw_["StickWallMult"] = false;
	isDraw_["StickWallMultCount"] = false;
	isDraw_["2Dash"] = false;
	isDraw_["2DashMult"] = false;
	isDraw_["2DashMultCount"] = false;
	isDraw_["EnemyBonus"] = false;
	isDraw_["EnemyBonusMult"] = false;
	isDraw_["EnemyBonusMultCount"] = false;
	isDraw_["DamageCount"] = false;
	isDraw_["DamageCountMinus"] = false;
	isDraw_["DamageCountMinusCount"] = false;
	isDraw_["ChargeTime"] = false;
	isDraw_["ChargeTimeMinus"] = false;
	isDraw_["ChargeTimeMinusCount"] = false;
	isDraw_["Total"] = false;
	isDraw_["TotalMult"] = false;
	isDraw_["TotalMultCount"] = false;
	isDraw_["TotalGetStar"] = false;
	isDraw_["TotalGetStarCount"] = false;
	
	isBaseDraw_["stageclear"] = false;
	isBaseDraw_["getStar"] = false;
	isBaseDraw_["maxDash"] = false;
	isBaseDraw_["WalkBlockCount"] = false;
	isBaseDraw_["5Dash"] = false;
	isBaseDraw_["YellowStar"] = false;
	isBaseDraw_["4Dash"] = false;
	//isDraw_["PurpleStar"] = false;
	isBaseDraw_["3Dash"] = false;
	isBaseDraw_["StickWall"] = false;
	isBaseDraw_["2Dash"] = false;
	isBaseDraw_["EnemyBonus"] = false;
	isBaseDraw_["DamageCount"] = false;
	isBaseDraw_["ChargeTime"] = false;
	isBaseDraw_["Total"] = false;
	isBaseDraw_["TotalGetStar"] = false;

	NumberForLoop_.push_back(0);
	NumberForLoop_.push_back(1);
	NumberForLoop_.push_back(2);
	NumberForLoop_.push_back(3);
	NumberForLoop_.push_back(4);
	NumberForLoop_.push_back(5);
	NumberForLoop_.push_back(6);
	NumberForLoop_.push_back(7);
	NumberForLoop_.push_back(8);
	NumberForLoop_.push_back(9);

	//nameList.push_back("stageclear");
	//nameList.push_back("getStar");
	//nameList.push_back("getStarStar");
	//nameList.push_back("getStarStarCount");
	//nameList.push_back("maxDash");
	//nameList.push_back("maxDashMult");
	//nameList.push_back("maxDashMultCount");
	//nameList.push_back("WalkBlockCount");
	//nameList.push_back("WalkBlockCountMult");
	//nameList.push_back("WalkBlockCountMultcount");
	//nameList.push_back("5Dash");
	//nameList.push_back("5DashMult");
	//nameList.push_back("5DashMultCount");
	//nameList.push_back("YellowStar");
	//nameList.push_back("YellowStarMult");
	//nameList.push_back("YellowStarMultCount");
	//nameList.push_back("4Dash");
	//nameList.push_back("4DashMult");
	//nameList.push_back("4DashMultCount");
	////nameList.push_back("PurpleStar");
	////nameList.push_back("PurpleStarMult");
	////nameList.push_back("PurpleStarMultCount");
	//nameList.push_back("3Dash");
	//nameList.push_back("3DashMult");
	//nameList.push_back("3DashMultCount");
	//nameList.push_back("StickWall");
	//nameList.push_back("StickWallMult");
	//nameList.push_back("StickWallMultCount");
	//nameList.push_back("2Dash");
	//nameList.push_back("2DashMult");
	//nameList.push_back("2DashMultCount");
	//nameList.push_back("EnemyBonus");
	//nameList.push_back("EnemyBonusMult");
	//nameList.push_back("EnemyBonusMultCount");
	//nameList.push_back("DamageCount");
	//nameList.push_back("DamageCountMinus");
	//nameList.push_back("DamageCountMinusCount");
	//nameList.push_back("ChargeTime");
	//nameList.push_back("ChargeTimeMinus");
	//nameList.push_back("ChargeTimeMinusCount");
	//nameList.push_back("Total");
	//nameList.push_back("TotalMult");
	//nameList.push_back("TotalMultCount");
	//nameList.push_back("TotalGetStar");
	//nameList.push_back("TotalGetStarCount");
	
	nameList.push_back("getStarStarCount");
	nameList.push_back("maxDashMultCount");
	nameList.push_back("5DashMultCount");
	nameList.push_back("4DashMultCount");
	nameList.push_back("3DashMultCount");
	nameList.push_back("2DashMultCount");
	nameList.push_back("DamageCountMinusCount");
	nameList.push_back("ChargeTimeMinusCount");
	nameList.push_back("WalkBlockCountMultcount");
	nameList.push_back("YellowStarMultCount");
	//nameList.push_back("PurpleStarMultCount");
	nameList.push_back("StickWallMultCount");
	nameList.push_back("EnemyBonusMultCount");
	nameList.push_back("TotalMultCount");
	nameList.push_back("TotalGetStarCount");

	nameBaseList.push_back("stageclear");
	nameBaseList.push_back("getStar");
	nameBaseList.push_back("maxDash");
	nameBaseList.push_back("5Dash");
	nameBaseList.push_back("4Dash");
	nameBaseList.push_back("3Dash");
	nameBaseList.push_back("2Dash");
	nameBaseList.push_back("DamageCount");
	nameBaseList.push_back("ChargeTime");
	nameBaseList.push_back("WalkBlockCount");
	nameBaseList.push_back("YellowStar");
	//nameBaseList.push_back("PurpleStar");
	nameBaseList.push_back("StickWall");
	nameBaseList.push_back("EnemyBonus");
	nameBaseList.push_back("Total");
	nameBaseList.push_back("TotalGetStar");


	isBaseDraw_[nameList[0]] = true;
	isBaseDraw_[nameList[1]] = true;

	Count_ = nameBaseList.size()+300.f;
	isFirst_ = true;

	buttonLock_=true;
	buttonLockCount_=60;
	isStarDraw_.resize(3);
	for (int i = 0; i < isStarDraw_.size(); i++) {
		isStarDraw_[i] = false;
	}
	isRankDraw_ = false;

	isSoundFirst_ = true;
	isRankSoundCheckFirst_ = true;
	rankSoundCheckCount_ = 0;
}

bool ClearScreen::update(std::string name, Scene& next)
{
	rankSoundCheckCount_--;
	if (rankSoundCheckCount_ <= 0) {
		isRankSoundCheckFirst_ = false;
	}
	if (!isMusic_) {
		ChangeNextPlayVolumeSoundMem(150,ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL));
		PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL), DX_PLAYTYPE_LOOP);
		isMusic_ = true;
	}
	buttonLockCount_ -= Time::GetInstance().deltaTime();
	if (isMaxDraw_) {
		drawNumberController_ += 0.016f;
		//if (drawNumberController_ > 0.3f&&!isRankDraw_) {
			//PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOW), DX_PLAYTYPE_BACK);
			//isRankDraw_ = true;
		//}
		//if (drawNumberController_ > 0.5&&!isStarDraw_[0]) {
			//PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOW), DX_PLAYTYPE_BACK);
			//isStarDraw_[0] = true;
		//}
		//if (drawNumberController_ > 0.7&&!isStarDraw_[1]) {
			//PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOW), DX_PLAYTYPE_BACK);
			//isStarDraw_[1] = true;
		//}
		if (drawNumberController_ > 1.8&&!isStarDraw_[2]) {
			isRankDraw_ = true;
			isStarDraw_[0] = true;
			isStarDraw_[1] = true;
			isStarDraw_[2] = true;
			rankSoundCheckCount_ = 1;
			isRankSoundCheckFirst_ = true;
		}
	}
	if (buttonLockCount_ <= 0)buttonLock_ = false;

	if (InputMgr::GetInstance().IsPushButton()&&isFirst_&&!buttonLock_) {
		isFirst_ = false;
		Count_ = 120;
		for (auto i : isBaseDraw_) {
			isBaseDraw_[i.first] = true;
		}
		for (auto i : isDraw_) {
			isDraw_[i.first] = true;
		}
		for (int i = 0; i < isStarDraw_.size(); i++) {
			isStarDraw_[i] = true;
		}
		isRankDraw_ = true;
		if(isSoundFirst_)PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOWMAX), DX_PLAYTYPE_BACK);
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL));
		ChangeVolumeSoundMem(0, ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOW));
		isSoundFirst_ = false;

	}
	drawNumberController_ += 0.016f;

	if (drawNumberController_>0.2f&&!isMaxDraw_) {
		isBaseDraw_[nameBaseList[usingBaseIntCount]] = true;
		isDraw_[nameList[usingIntCount]]=true;
		PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOW),DX_PLAYTYPE_BACK);
		usingIntCount++;
		usingBaseIntCount++;
		if (usingIntCount >= nameList.size()) {
			usingIntCount = nameList.size() - 1;
			isMaxDraw_ = true;
			StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL));
			isSoundFirst_ = false;
		}
		if (usingBaseIntCount >= nameBaseList.size())usingBaseIntCount = nameBaseList.size() - 1;
		drawNumberController_ = 0;
	}
	for (int i = 0; i < NumberForLoop_.size(); i++) {
		NumberForLoop_[i]++;
		if (NumberForLoop_[i] > 9) {
			NumberForLoop_[i] = 0;
		}
	}

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
	int setLoopNum = 0;

	//anmer_.draw_e(Vector2(static_cast<float>(center), 0), Vector2::Zero, 1);
	anmer_.draw_e(textPositions.at("stageclear"));

	DrawGraph(textPositions.at("getStar").x, textPositions.at("getStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_GETSTAR_TEX), TRUE);
	DrawGraph(textPositions.at("getStarStar").x, textPositions.at("getStarStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
	int drawNum = keeper_->GetItemCount();
	int baseNum = keeper_->GetItemCount();
	if (isDraw_.at("getStarStarCount")) {
		drawNumber(drawNum, baseNum,
			textPositions.at("getStarStarCount").x, textPositions.at("getStarStarCount").y, 0);
	}
	else {
		LoopNumber(textPositions.at("getStarStarCount").x, textPositions.at("getStarStarCount").y, setLoopNum, 0);
		setLoopNum++;
		if (setLoopNum > 9) {
			setLoopNum = 0;
		}
	}
	if (isBaseDraw_.at("maxDash")) {
		DrawGraph(textPositions.at("maxDash").x, textPositions.at("maxDash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MAXCOMBO_TEX), TRUE);
		DrawGraph(textPositions.at("maxDashMult").x, textPositions.at("maxDashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->maxComboGet();
		baseNum = keeper_->maxComboGet();
		multAddCount += keeper_->maxComboGet();
		if (isDraw_.at("maxDashMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("maxDashMultCount").x, textPositions.at("maxDashMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("maxDashMultCount").x, textPositions.at("maxDashMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("WalkBlockCount")) {
		DrawGraph(textPositions.at("WalkBlockCount").x, textPositions.at("WalkBlockCount").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_WALK_BLOCK_COUNT_TEX), TRUE);
		DrawGraph(textPositions.at("WalkBlockCountMult").x, textPositions.at("WalkBlockCountMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->getMoveDistance() / CHIPSIZE;
		baseNum = keeper_->getMoveDistance() / CHIPSIZE;
		multAddCount += (keeper_->getMoveDistance() / CHIPSIZE);
		if (isDraw_.at("WalkBlockCountMultcount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("WalkBlockCountMultcount").x, textPositions.at("WalkBlockCountMultcount").y);
		}
		else {
			LoopNumber(textPositions.at("WalkBlockCountMultcount").x, textPositions.at("WalkBlockCountMultcount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}
	if (isBaseDraw_.at("5Dash")) {
		DrawGraph(textPositions.at("5Dash").x, textPositions.at("5Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO5_TEX), TRUE);
		DrawGraph(textPositions.at("5DashMult").x, textPositions.at("5DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->getComboCount(5);
		baseNum = keeper_->getComboCount(5);
		multAddCount += keeper_->getComboCount(5);
		if (isDraw_.at("5DashMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("5DashMultCount").x, textPositions.at("5DashMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("5DashMultCount").x, textPositions.at("5DashMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("YellowStar")) {
		DrawGraph(textPositions.at("YellowStar").x, textPositions.at("YellowStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_STAR_COUNT_TEX), TRUE);
		DrawGraph(textPositions.at("YellowStarMult").x, textPositions.at("YellowStarMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		if (keeper_->GetMaxItemCount() != 0) {
			drawNum = (float)keeper_->getPlusStar() / keeper_->GetMaxItemCount() * 10;
			baseNum = (float)keeper_->getPlusStar() / keeper_->GetMaxItemCount() * 10;
			multAddCount += (float)keeper_->getPlusStar() / keeper_->GetMaxItemCount() * 10;
		}
		else {
			drawNum = 0;
			baseNum = 0;
		}
		if (isDraw_.at("YellowStarMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("YellowStarMultCount").x, textPositions.at("YellowStarMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("YellowStarMultCount").x, textPositions.at("YellowStarMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("4Dash")) {
		DrawGraph(textPositions.at("4Dash").x, textPositions.at("4Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO4_TEX), TRUE);
		DrawGraph(textPositions.at("4DashMult").x, textPositions.at("4DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->getComboCount(4);
		baseNum = keeper_->getComboCount(4);
		multAddCount += keeper_->getComboCount(4);
		if (isDraw_.at("4DashMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("4DashMultCount").x, textPositions.at("4DashMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("4DashMultCount").x, textPositions.at("4DashMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	//DrawGraph(textPositions.at("PurpleStar").x, textPositions.at("PurpleStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MINUS_STAR_COUNT_TEX), TRUE);
	//DrawGraph(textPositions.at("PurpleStarMult").x, textPositions.at("PurpleStarMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
	//drawNum = keeper_->getMinusStar();
	//baseNum = keeper_->getMinusStar();
	//multAddCount+= keeper_->getMinusStar();
	//drawNumber(drawNum, baseNum,
	//	textPositions.at("PurpleStarMultCount").x, textPositions.at("PurpleStarMultCount").y);
	if (isBaseDraw_.at("3Dash")) {
		DrawGraph(textPositions.at("3Dash").x, textPositions.at("3Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO3_TEX), TRUE);
		DrawGraph(textPositions.at("3DashMult").x, textPositions.at("3DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->getComboCount(3);
		baseNum = keeper_->getComboCount(3);
		multAddCount += keeper_->getComboCount(3);
		if (isDraw_.at("3DashMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("3DashMultCount").x, textPositions.at("3DashMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("3DashMultCount").x, textPositions.at("3DashMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("StickWall")) {
		DrawGraph(textPositions.at("StickWall").x, textPositions.at("StickWall").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_STICK_COUNT_TEX), TRUE);
		DrawGraph(textPositions.at("StickWallMult").x, textPositions.at("StickWallMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->getHoldCount();
		baseNum = keeper_->getHoldCount();
		multAddCount += keeper_->getHoldCount();
		if (isDraw_.at("StickWallMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("StickWallMultCount").x, textPositions.at("StickWallMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("StickWallMultCount").x, textPositions.at("StickWallMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}

	}
	if (isBaseDraw_.at("2Dash")) {
		DrawGraph(textPositions.at("2Dash").x, textPositions.at("2Dash").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_COMBO2_TEX), TRUE);
		DrawGraph(textPositions.at("2DashMult").x, textPositions.at("2DashMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = keeper_->getComboCount(2);
		baseNum = keeper_->getComboCount(2);
		multAddCount += keeper_->getComboCount(2);
		if (isDraw_.at("2DashMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("2DashMultCount").x, textPositions.at("2DashMultCount").y);
		}
		else {
			LoopNumber(textPositions.at("2DashMultCount").x, textPositions.at("2DashMultCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (keeper_->getEnemyCount() == 0) {
		if (isBaseDraw_.at("EnemyBonus")) {
			DrawGraph(textPositions.at("EnemyBonus").x, textPositions.at("EnemyBonus").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_NoENEMY_DEATH_TEX), TRUE);
			DrawGraph(textPositions.at("EnemyBonusMult").x, textPositions.at("EnemyBonusMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
			drawNum = 100;
			baseNum = 100;
			multAddCount += 100;
			if (isDraw_.at("EnemyBonusMultCount")) {
				drawNumber(drawNum, baseNum,
					textPositions.at("EnemyBonusMultCount").x, textPositions.at("EnemyBonusMultCount").y);
			}
			else {
				LoopNumber(textPositions.at("EnemyBonusMultCount").x, textPositions.at("EnemyBonusMultCount").y, setLoopNum);
				setLoopNum++;
				if (setLoopNum > 9) {
					setLoopNum = 0;
				}
			}
		}
	}
	if (isBaseDraw_.at("DamageCount")) {
		DrawGraph(textPositions.at("DamageCount").x, textPositions.at("DamageCount").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_DAMAGE_COUNT_TEX), TRUE);
		DrawGraph(textPositions.at("DamageCountMinus").x, textPositions.at("DamageCountMinus").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MINUS_MULT_TEX), TRUE);
		drawNum = keeper_->getDamageCount();
		baseNum = keeper_->getDamageCount();
		multAddCount -= keeper_->getDamageCount();
		if (isDraw_.at("DamageCountMinusCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("DamageCountMinusCount").x, textPositions.at("DamageCountMinusCount").y);
		}
		else {
			LoopNumber(textPositions.at("DamageCountMinusCount").x, textPositions.at("DamageCountMinusCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("ChargeTime")) {
		DrawGraph(textPositions.at("ChargeTime").x, textPositions.at("ChargeTime").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_CHARGETIME_TEX), TRUE);
		DrawGraph(textPositions.at("ChargeTimeMinus").x, textPositions.at("ChargeTimeMinus").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MINUS_MULT_TEX), TRUE);
		drawNum = keeper_->getChargeTime();
		baseNum = keeper_->getChargeTime();
		multAddCount -= keeper_->getChargeTime();
		if (isDraw_.at("ChargeTimeMinusCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("ChargeTimeMinusCount").x, textPositions.at("ChargeTimeMinusCount").y);
		}
		else {
			LoopNumber(textPositions.at("ChargeTimeMinusCount").x, textPositions.at("ChargeTimeMinusCount").y, setLoopNum);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("Total")) {
		DrawGraph(textPositions.at("Total").x, textPositions.at("Total").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_TOTAL_TEX), TRUE);
		DrawGraph(textPositions.at("TotalMult").x, textPositions.at("TotalMult").y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_MULTIPLY_TEX), TRUE);
		drawNum = multAddCount;
		baseNum = multAddCount;
		if (isDraw_.at("TotalMultCount")) {
			drawNumber(drawNum, baseNum,
				textPositions.at("TotalMultCount").x, textPositions.at("TotalMultCount").y, 0);
		}
		else {
			LoopNumber(textPositions.at("TotalMultCount").x, textPositions.at("TotalMultCount").y, setLoopNum, 0);
			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}

	if (isBaseDraw_.at("TotalGetStar")) {
		drawNum = multAddCount*keeper_->GetItemCount();
		baseNum = multAddCount*keeper_->GetItemCount();
		if (isDraw_.at("TotalGetStarCount")) {
			int drawPNum = drawNumber(drawNum, baseNum,
				textPositions.at("TotalGetStarCount").x - (ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x * 11), textPositions.at("TotalGetStarCount").y, 0, 11);
			DrawGraph(textPositions.at("TotalGetStar").x - (ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x * drawPNum), textPositions.at("TotalGetStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}
		else {
			LoopNumber(textPositions.at("TotalGetStarCount").x - (ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x * 11), textPositions.at("TotalGetStarCount").y, setLoopNum, 0, 11);

			//DrawGraph(textPositions.at("TotalGetStar").x-(ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX).x*11), textPositions.at("TotalGetStar").y, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);

			setLoopNum++;
			if (setLoopNum > 9) {
				setLoopNum = 0;
			}
		}
	}
	if (baseNum < 100000) {
		if (isRankDraw_) {
			if (isRankSoundCheckFirst_)PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_RANKC), DX_PLAYTYPE_BACK);
			DrawGraph(RankPosx, RankPosy, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_RANK_C_TEX), TRUE);
		}
		if (isStarDraw_[0]) {
			Vector2 cent = ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX);
			DrawRotaGraph2(StarPosx, StarPosy, cent.x, cent.y, 1, 0, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}
	}
	else if (baseNum < 500000) {
		if (isRankDraw_) {
			if (isRankSoundCheckFirst_)PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_RANKB), DX_PLAYTYPE_BACK);
			DrawGraph(RankPosx, RankPosy, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_RANK_B_TEX), TRUE);
		}
		if (isStarDraw_[0]) {
			Vector2 cent = ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX);
			DrawRotaGraph2(StarPos_Rx, StarPos_Ry, cent.x, cent.y, 0.7, 0, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}
		if (isStarDraw_[1]) {
			Vector2 cent = ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX);
			DrawRotaGraph2(StarPos2_Rx, StarPos2_Ry, cent.x, cent.y, 0.7, 0, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}
	}
	else {
		if (isRankDraw_) {
			if (isRankSoundCheckFirst_)PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_RANKA), DX_PLAYTYPE_BACK);
			DrawGraph(RankPosx, RankPosy, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_RANK_A_TEX), TRUE);
		}
		if (isStarDraw_[0]) {
			Vector2 cent = ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX);
			DrawRotaGraph2(StarPos_Lx, StarPos_Ly, cent.x, cent.y, 0.5, 0, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}
		if (isStarDraw_[1]) {
			Vector2 cent = ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX);
			DrawRotaGraph2(StarPos2_Lx, StarPos2_Ly, cent.x, cent.y, 0.5, 0, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}
		if (isStarDraw_[2]) {
			Vector2 cent = ResourceLoader::GetInstance().GetTextureSize(TextureID::ITEM_TEX);
			DrawRotaGraph2(StarPos3_Lx, StarPos3_Ly, cent.x, cent.y, 0.5, 0, ResourceLoader::GetInstance().getTextureID(TextureID::ITEM_TEX), TRUE);
		}

		//	}

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
}