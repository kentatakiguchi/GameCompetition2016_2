#include "GameOverScene.h"

GameOverScene::GameOverScene(SceneDataKeeper* keeper) :
	id(0) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "GameOver";

	nextScene[1] = GamePlay;
	nextScene[2] = MainMenu;
	nextScene[3] = BossStage01;
	
	textIDs[0] = TextureID::TEXT_GAMEOVER_TEX;
	textIDs[1] = TextureID::TEXT_RETRY_TEX;
	textIDs[2] = TextureID::TEXT_MENUBACK_TEX;


	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("ステージクリア");
	listBase[0] = list1;
	textPosList.push_back(Vector2(200, 200));
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("次のステージへ");
	listBase[1] = list2;
	textPoses[1] = Vector2(500, 600);
	textPoses[3] = Vector2(500, 600);
	textPosList.push_back(textPoses[1]);
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list3;
	list3.push_back("メニューに戻る");
	listBase[2] = list3;
	textPoses[2] = Vector2(500, 700);
	textPosList.push_back(textPoses[2]);
	changeTextList.clear();

}

GameOverScene::~GameOverScene(){

}

void GameOverScene::start() {
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// グラフィックのロード
	targetPoint = 1;
	sinCount = 0;

	if (keeper_->getSceneName() == "stage01") keeper_->setSceneName("stage04");
	else if (keeper_->getSceneName() == "stage02") keeper_->setSceneName("stage01");
	else if (keeper_->getSceneName() == "stage03") keeper_->setSceneName("stage02");
	else if (keeper_->getSceneName() == "stage04") keeper_->setSceneName("stage03");

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_GAMEOVER), DX_PLAYTYPE_BACK);

	mButtyAnim = PlayerAnimation2D("PlayerBody1");
	mRettyAnim = PlayerAnimation2D("PlayerBody2", ActionType::Left);
	mButtyAnim.change(PlayerAnimID::DEATH);
	mRettyAnim.change(PlayerAnimID::DEATH);

	//mCursorPos = Vector2(500, 500);
	mCursorPos = Vector2(SCREEN_SIZE.x / 2 - 128, 500);
}

void GameOverScene::update() {
	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);

	if (isEnd_)return;

	if (targetPoint != 3)
	{
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_UP)) {
			targetPoint--;
			sinCount = 0;
			PlaySound("./resources/sounds/menuse/menu_cursor.mp3", DX_PLAYTYPE_BACK);
		}
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_DOWN)) {
			targetPoint++;
			sinCount = 0;
			PlaySound("./resources/sounds/menuse/menu_cursor.mp3", DX_PLAYTYPE_BACK);
		}
		targetPoint = min(max(targetPoint, 1), 2);


		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))
		{
			isEnd_ = true;
			PlaySound("./resources/sounds/menuse/menu_decision.mp3", DX_PLAYTYPE_BACK);
			if (targetPoint == 1 && keeper_->getSceneName() == "bossStage01")targetPoint = 3;
		}
	}

	//if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))	
	//{

	//	nextScene_ = Scene::GamePlay;

	//	isEnd_ = true;

	//}
	//if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))
	//{
	//	nextScene_ = Scene::MainMenu;
	//	isEnd_ = true;
	//	//ゴールポイントについた時点でシーンを遷移
	//}

	if (mButtyAnim.end_anim()) mButtyAnim.change(PlayerAnimID::DEATH, 0.0f);
	if (mRettyAnim.end_anim()) mRettyAnim.change(PlayerAnimID::DEATH, 0.0f);

	mButtyAnim.update(Time::GetInstance().deltaTime());
	mRettyAnim.update(Time::GetInstance().deltaTime());

	mCursorPos = Vector2::Lerp(mCursorPos, textPoses.at(targetPoint), 0.5f);
}

void GameOverScene::draw() const {
	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	int forcount = 0;
	for (auto lists : listBase) {
		for (auto my : lists) {
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = static_cast<int>(SCREEN_SIZE.x) / 2;
			//DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			if (forcount == targetPoint && forcount != 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(sin(sinCount*MathHelper::Pi / 180)) * 255));

			if (count == targetPoint) {
				DrawRotaGraph2(center, textPosList.at(count).y, ResourceLoader::GetInstance().GetTextureSize(textIDs.at(count)).x / 2, 0, 1.5, 0, ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);
			}
			else if (count>targetPoint) {
				DrawGraph(center - ResourceLoader::GetInstance().GetTextureSize(textIDs.at(count)).x / 2, static_cast<int>(textPosList.at(count).y + ResourceLoader::GetInstance().GetTextureSize(textIDs.at(count)).y / 2), ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);
			}
			else {
				DrawGraph(center - ResourceLoader::GetInstance().GetTextureSize(textIDs.at(count)).x / 2, static_cast<int>(textPosList.at(count).y), ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);
			}

			//DrawGraph(center - 320, static_cast<int>(textPosList.at(count).y), ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			heightPoint++;
		}
		forcount++;
		count++;
		heightPoint = 0;
	}

	//mButtyAnim.draw(mCursorPos, Vector2::Zero, 0.5f);
	//mRettyAnim.draw(mCursorPos + Vector2::Right * 780, Vector2::Zero, 0.5f);
	mButtyAnim.draw(mCursorPos + Vector2::Left * 200, Vector2::Zero, 0.5f);
	mRettyAnim.draw(mCursorPos + Vector2::Right * 1000, Vector2::Zero, 0.5f);

}

void GameOverScene::end() {
	StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_GAMEOVER));

}

bool GameOverScene::isEnd() const {
	return isEnd_;
}

Scene GameOverScene::next() const {
	return nextScene.at(targetPoint);
}
