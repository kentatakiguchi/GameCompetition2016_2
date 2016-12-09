#include "MainMenuScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

static const float shotSpeed = 5;
static const int boundCount = 5;
static const int TitleMainFadeInSpeed = 15;
static const int SelectPointerFadeInSpeed = 15;

MainMenuScene::MainMenuScene(SceneDataKeeper* keeper) :
	id(0),sinCount(0),targetPoint(1) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "MainMenu";

	alphadefSpeeds[0] = TitleMainFadeInSpeed;
	alphadefSpeeds[1] = SelectPointerFadeInSpeed;

	defposlist[0] = 0;
	defposlist[1] = 340;
	defposlist[2] = 420;
	defposlist[3] = 500;

	nextScene[1] = GamePlay;
	nextScene[2] = Credit;
	nextScene[3] = GameEnd;

	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("タイトル");
	listBase[0] = list1;
	
	lastPoses[0] = Vector2(200, 200);
	setPoses[0] = Vector2(0, defposlist[0]);

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
	setPoses[1] = Vector2(0, defposlist[1]);

	listBase.push_back(changeTextList);
	std::vector<std::string> list3;
	list3.push_back("クレジット");
	listBase[2] = list3;
	textPoses[2] = Vector2(200, 600);
	textPosList.push_back(textPoses[2]);
	changeTextList.clear();

	lastPoses[2] = Vector2(200,600);
	setPoses[2] = Vector2(0, defposlist[2]);

	listBase.push_back(changeTextList);
	std::vector<std::string> list4;
	list4.push_back("ゲーム終了");
	listBase[3] = list4;
	textPoses[3] = Vector2(200, 700);
	textPosList.push_back(textPoses[3]);
	changeTextList.clear();

	lastPoses[3] = Vector2(200,700);
	setPoses[3] = Vector2(0, defposlist[3]);



}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::start() {
	isEnd_ = false;

	alphaCou[0] = 0;
	alphaCou[1] = 0;

	targetPoint = 1;

	for (int i = 0; i < textPosList.size(); i++) {
		textPosList[i] = setPoses[i];
		shotPos[i] = Vector2::Zero;
		isPoint[i] = false;
		isArrive[i] = false;
		isShotArrive[i] = false;
		boundCou[i] = boundCount;

	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	//for (int i = 0; i < 3; i++) {
	//	textPosList[i + 1].y = textPoses[i + 1].y;
	//}

}

void MainMenuScene::update() {


	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);


	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_UP)) {
		targetPoint--;
		sinCount = 0;
	}
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_DOWN)) {
		targetPoint++;
		sinCount = 0;
	}
	targetPoint = min(max(targetPoint, 1), 3);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))
	{
		keeper_->setSceneName("stage04");
		isEnd_ = true;
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
	for (int i = 0; i < 4; i++)
	{
		isPoint[i] ? moveText(i) : slideText(i);
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
	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	int forcount = 0;
	for (auto lists : listBase) {
		for (auto my : lists) {
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = SCREEN_SIZE.x / 2;
			if (alphaCou[0]<=255)SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaCou[0]);
			if (forcount == targetPoint&&isArrive.at(0))SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
			//if (!isArrive.at(0) && forcount != 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
			DrawStringToHandle(center - (strWidth / 2), textPosList.at(count).y + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
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

	DrawGraph(textPoses.at(targetPoint).x, textPoses.at(targetPoint).y, ResourceLoader::GetInstance().getTextureID(TextureID::SELECT_TARGET_TEX), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
	//DrawGraph(textPoses.at(targetPoint).x+100, textPoses.at(targetPoint).y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_ALPHA_TEX), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void MainMenuScene::end() {}

bool MainMenuScene::isEnd() const {
	return isEnd_;
}

Scene MainMenuScene::next() const {
	return nextScene.at(targetPoint);
}
