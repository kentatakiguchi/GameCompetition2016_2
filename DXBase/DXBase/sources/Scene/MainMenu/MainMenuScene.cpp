#include "MainMenuScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

static const float shotSpeed = 5;
static const int boundCount = 5;
static const int TitleMainFadeInSpeed = 15;
static const int SelectPointerFadeInSpeed = 15;
static const int DefAlphaSlideCount = 100;
static const float titleY = 10;
static const float spaceY = 400;
static const float boundPower = 30;
static const int MaxTexSize = 1920;
static const int SlideSpeed = 7;
static const float DefBackSpriteChangeTime = 10.f;
static const int TitleFadeInSpeed = 10;
static const int alphaspeed = 5;

MainMenuScene::MainMenuScene(SceneDataKeeper* keeper) :
	id(0),sinCount(0),targetPoint(1) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "MainMenu";

	alphadefSpeeds[0] = TitleMainFadeInSpeed;
	alphadefSpeeds[1] = SelectPointerFadeInSpeed;

	textIDs[0] = TextureID::TEXT_TITLE_TEX;
	textIDs[1] = TextureID::TEXT_GAMESTART_TEX;
	textIDs[2] = TextureID::TEXT_CREDIT_TEX;
	textIDs[3] = TextureID::TEXT_TUTORIAL_TEX;
	textIDs[4] = TextureID::TEXT_GAMEEND_TEX;
	textIDs[5] = TextureID::TEXT_MARU_TEX;

	defposlist[0] = 0;
	defposlist[1] = 340;
	defposlist[2] = 420;
	defposlist[3] = 500;
	defposlist[4] = 620;
	defposlist[5] = 450;

	nextScene[1] = GamePlay;
	nextScene[2] = Credit;
	nextScene[3] = Tutoreal;
	nextScene[4] = GameEnd;



	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("タイトル");
	listBase[0] = list1;
	
	lastPoses[0] = Vector2(200, 200);
	setPoses[0] = Vector2(0, static_cast<float>(defposlist[0]));

	textPosList.push_back(Vector2(200,200));
	changeTextList.clear();


	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("ゲームスタート");
	listBase[1] = list2;
	textPoses[1] = Vector2(200, 500);
	textPosList.push_back(textPoses[1]);
	changeTextList.clear();

	lastPoses[1] = Vector2(200,500);
	setPoses[1] = Vector2(0, static_cast<float>(defposlist[1]));

	listBase.push_back(changeTextList);
	std::vector<std::string> list3;
	list3.push_back("クレジット");
	listBase[2] = list3;
	textPoses[2] = Vector2(200, 600);
	textPosList.push_back(textPoses[2]);
	changeTextList.clear();

	lastPoses[2] = Vector2(200,600);
	setPoses[2] = Vector2(0, static_cast<float>(defposlist[2]));

	listBase.push_back(changeTextList);
	std::vector<std::string> list4;
	list4.push_back("チュートリアル");
	listBase[3] = list4;
	textPoses[3] = Vector2(200, 700);
	textPosList.push_back(textPoses[3]);
	changeTextList.clear();

	lastPoses[3] = Vector2(200, 700);
	setPoses[3] = Vector2(0, static_cast<float>(defposlist[3]));

	listBase.push_back(changeTextList);
	std::vector<std::string> list5;
	list5.push_back("ゲーム終了");
	listBase[4] = list5;
	textPoses[4] = Vector2(200, 800);
	textPosList.push_back(textPoses[4]);
	changeTextList.clear();

	lastPoses[4] = Vector2(200, 800);
	setPoses[4] = Vector2(0, static_cast<float>(defposlist[4]));



	currentTitleBackID.push_back(TextureID::TITLE_BACK_TEX);
	currentTitleBackID.push_back(TextureID::TITLE_BACK_TEX);

	changeTargetChecker.push_back(0);
	changeTargetChecker.push_back(0);
	
	baseTitleBackID[0] = TextureID::TITLE_BACK_TEX;
	baseTitleBackID[1] = TextureID::TITLE_BACK2_TEX;
	baseTitleBackID[2] = TextureID::TITLE_BACK_TEX;

	listBase.push_back(changeTextList);
	std::vector<std::string>  list6;
	list6.push_back("〇ボタンを押してください");
	listBase[5] = list6;
	textPoses[5] = Vector2(200, 600);
	lastPoses[5] = textPoses[5];
	setPoses[5] = Vector2(0, spaceY);
	textPosList.push_back(setPoses[5]);
	changeTextList.clear();

}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::start() {
	isEnd_ = false;
	isTitle_ = true;
	isDrawAlphaBack_ = false;

	alphaCou[0] = 0;
	alphaCou[1] = 0;

	titleBackAlpha_ = 0;

	targetPoint = 1;

	sinCount = 0;

	for (int i = 0; i < static_cast<int>(textPosList.size()); i++) {
		textPosList[i] = setPoses[i];
		shotPos[i] = Vector2::Zero;
		isPoint[i] = false;
		isArrive[i] = false;
		isShotArrive[i] = false;
		boundCou[i] = boundCount;

	}
	for (int i = 0; i < 2; i++) {
		titleBackStageNum[i] = 1;
		//0が1枚目、1が2枚目で、1枚につきMaxTexSize移動フレーム分の時間をスライドの変更時間に追加する
		titleBackChangeTime[i] = DefBackSpriteChangeTime + ((MaxTexSize / SlideSpeed) / 60 * (i));

		currentTitleBackID[i] = TextureID::TITLE_BACK_TEX;

		changeBackChecker[i] = false;
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	//for (int i = 0; i < 3; i++) {
	//	textPosList[i + 1].y = textPoses[i + 1].y;
	//}

	PlaySoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_MENU), DX_PLAYTYPE_LOOP);
	//PlaySoundFile("./resources/file/game_menuBGM.mp3", DX_PLAYTYPE_LOOP);
}

void MainMenuScene::update() {

	Vector2 alphasize= ResourceLoader::GetInstance().GetTextureSize(TextureID::TITLE_BACK_ALPHA_TEX);

	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);

	if (isDrawAlphaBack_) {
		alphaSlideCount_--;
		if (alphaSlideCount_ <= 0) {
			titleBackAlpha_ = 0;
			isDrawAlphaBack_ = false;
		}
		if (alphaSlideCount_ <= DefAlphaSlideCount / 2) {
				titleBackAlpha_-= alphaspeed;
		}
		else {
			titleBackAlpha_+= alphaspeed;
		}
	}

	slideSize += SlideSpeed;

	if (slideSize >= MaxTexSize) {
		slideSize = 0;
	}
			if (changeBackChecker[0]) {
				changeBackChecker[0] = false;

				alphaSlideCount_=DefAlphaSlideCount;
				titleBackAlpha_ = 0;
				isDrawAlphaBack_ = true;
		
	}
	for (int i = 0; i < 2; i++) {
		titleBackChangeTime[i] -= Time::GetInstance().deltaTime();

		if (titleBackChangeTime[i] <= 0) {
			titleBackChangeTime[i] = DefBackSpriteChangeTime;
			changeBackChecker[i] = true;
		}
	}

	if (!isTitle_)
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
		targetPoint = min(max(targetPoint, 1), 4);

		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE))
		{
			keeper_->setSceneName("stage04");
			isEnd_ = true;

			PlaySound("./resources/sounds/menuse/menu_decision.mp3", DX_PLAYTYPE_BACK);

		}
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::A))
		{
			//ステージ1へ
			keeper_->setSceneName("stage04");
			isEnd_ = true;
		}
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::S))
		{
			//ステージ2へ
			keeper_->setSceneName("stage01");
			isEnd_ = true;
		}
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::D))
		{
			//ステージ3へ
			keeper_->setSceneName("stage02");
			isEnd_ = true;
		}
		if (InputMgr::GetInstance().IsKeyDown(KeyCode::D))
		{
			//ステージ4へ
			keeper_->setSceneName("stage03");
			isEnd_ = true;
		}

		if (alphaCou[1] <= 255 && isArrive.at(0)) {
			alphaCou[1] += alphadefSpeeds[1];
			alphaCou[1] = min(max(alphaCou[1], 0), 255);
		}
		if (alphaCou[0] <= 255) {
			alphaCou[0] += alphadefSpeeds[0];
			alphaCou[0] = min(max(alphaCou[0], 0), 255);
		}

	}
	else {
		if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE)) {
			isTitle_ = false;
			PlaySound("./resources/sounds/menuse/menu_decision.mp3", DX_PLAYTYPE_BACK);
		}
	}
	for (int i = 0; i < 5; i++)
	{

		isPoint[i] ? moveText(i) : slideText(i);
	}
	isPoint[5] ? moveText(5) : slideText(5);


}
void MainMenuScene::slideText(int targettext)
{
	if (isArrive[targettext]) return;

	textPosList[targettext].y += 10;
	textPosList[targettext].y = min(max(textPosList[targettext].y, setPoses[targettext].y), lastPoses[targettext].y);

	if (textPosList[targettext].y == lastPoses[targettext].y) isPoint[targettext] = true;
}

void MainMenuScene::moveText(int targettext)
{
	if (isArrive[targettext]) return;


	if (!isShotArrive[targettext]) {
		boundCou[targettext]--;
		boundCou[targettext] = min(max(boundCou[targettext], 0), boundCount);

		//shotPos[targettext].y =(defposlist[targettext])-abs(((boundPower / 3)*boundCou[targettext]));
		shotPos[targettext].y = lastPoses[targettext].y - (lastPoses[targettext].y - defposlist[targettext]) + ((boundCount - boundCou[targettext]) * 50);
		isShotArrive[targettext] = true;
	}


	if (textPosList[targettext].y <= shotPos[targettext].y) {
		isShotArrive[targettext] = false;
		isPoint[targettext] = false;

	}
	else {
		textPosList[targettext].y -= (shotSpeed*(boundCou[targettext] + 1));
	}

	if (!isPoint[targettext] && boundCou[targettext] <= 0) {
		isArrive[targettext] = true;
		textPosList[targettext].y = lastPoses[targettext].y;
	}
}

void MainMenuScene::draw() const {

	DrawGraph(MaxTexSize - slideSize, 0, ResourceLoader::GetInstance().getTextureID(currentTitleBackID[0]), TRUE);
	DrawGraph(-slideSize, 0, ResourceLoader::GetInstance().getTextureID(currentTitleBackID[1]), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleBackAlpha_);
	if (isDrawAlphaBack_)DrawGraph(0, 0, ResourceLoader::GetInstance().getTextureID(TextureID::TITLE_BACK_ALPHA_TEX), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	int forcount = 0;


	for (auto lists : listBase) {
		for (auto my : lists) {
			if (isTitle_) {
				if (count > 0 && count < 5) {
					continue;
				}
			}
			else if (!isTitle_&& count >= 5)break;
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = static_cast<int>(SCREEN_SIZE.x) / 2;
			if (forcount == targetPoint&&isArrive.at(0))SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(sin(sinCount*MathHelper::Pi / 180)) * 255));
			
			if (count == 0) {
				int psizex = 80;
				int psizey = 50;
				DrawExtendGraph(center - (748+psizex / 2), textPosList.at(count).y, center + (748+psizex / 2), textPosList.at(count).y + 155+psizey, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_TITLE_TEX), TRUE);
			}
			else {
				DrawGraph(center - 320, static_cast<int>(textPosList.at(count).y), ResourceLoader::GetInstance().getTextureID(textIDs.at(count)), TRUE);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			heightPoint++;
		}
		forcount++;
		count++;
		heightPoint = 0;
	}
	if (alphaCou[1]<255) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaCou[1]);
	}

	DrawGraph(static_cast<int>(textPoses.at(targetPoint).x), static_cast<int>(textPoses.at(targetPoint).y), ResourceLoader::GetInstance().getTextureID(TextureID::SELECT_TARGET_TEX), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void MainMenuScene::end() { StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::BGM_MENU)); }

bool MainMenuScene::isEnd() const {
	return isEnd_;
}

Scene MainMenuScene::next() const {
	return nextScene.at(targetPoint);
}
