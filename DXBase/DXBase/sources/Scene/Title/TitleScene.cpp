#include "TitleScene.h"

static const float titleY = 10;
static const float spaceY = 400;
static const int boundCount = 5;
static const float boundPower = 30;
static const float shotSpeed = 5;
static const int MaxTexSize = 1920;
static const int SlideSpeed = 10;
static const float DefBackSpriteChangeTime = 10.f;
static const int TitleFadeInSpeed = 10;

TitleScene::TitleScene(SceneDataKeeper* keeper) :
	id(0),sinCount(0),slideSize(0){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "Title";

	defposlist[0] = static_cast<int>(titleY);
	defposlist[1] = static_cast<int>(spaceY);

	int listNum = 0;
	listBase.push_back(changeTextList);
	std::vector<std::string> list1;
	list1.push_back("タイトル");
	listBase[0] = list1;
	lastPoses[0] = Vector2(200, 200);
	setPoses[0] = Vector2(0, titleY);
	textPosList.push_back(setPoses[0]);
	changeTextList.clear();

	listBase.push_back(changeTextList);
	std::vector<std::string> list2;
	list2.push_back("〇ボタンを押してください");
	listBase[1] = list2;
	textPos = Vector2(200, 600);
	lastPoses[1] = textPos;
	setPoses[1] = Vector2(0, spaceY);
	textPosList.push_back(setPoses[1]);
	changeTextList.clear();

	currentTitleBackID.push_back(TextureID::TITLE_BACK_TEX);
	currentTitleBackID.push_back(TextureID::TITLE_BACK_TEX);

	changeTargetChecker.push_back(0);
	changeTargetChecker.push_back(0);

	baseTitleBackID[0] = TextureID::TITLE_BACK_TEX;
	baseTitleBackID[1] = TextureID::TITLE_BACK2_TEX;
	baseTitleBackID[2] = TextureID::TITLE_BACK3_TEX;
}

TitleScene::~TitleScene(){}

void TitleScene::start() {
	isEnd_ = false;

	slideSize = 0;
	alphaCou = 0;

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
		titleBackChangeTime[i] = DefBackSpriteChangeTime+((MaxTexSize/ SlideSpeed)/60*(i));

		currentTitleBackID[i] = TextureID::TITLE_BACK_TEX;

		changeBackChecker[i] = false;
	}


	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
}

void TitleScene::update() {
	Time::GetInstance().update();

	slideSize+= SlideSpeed;
	if (slideSize >= MaxTexSize) {
		slideSize = 0;
		for (int i = 0; i < 2; i++)
		{
			if (changeBackChecker[i]) {
				changeBackChecker[i] = false;
				changeTargetChecker[i]++;
				if (changeTargetChecker[i] == baseTitleBackID.size())changeTargetChecker[i] = 0;
				currentTitleBackID[i] = baseTitleBackID[changeTargetChecker[i]];
			}

		}
	}
	for (int i = 0; i < 2; i++) {
		titleBackChangeTime[i] -= Time::GetInstance().deltaTime();

		if (titleBackChangeTime[i] <= 0) {
			titleBackChangeTime[i] = DefBackSpriteChangeTime;
			changeBackChecker[i] = true;
		}
	}


	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))
	{
		isEnd_ = true;
	}

	{
		//textPosList[1].y += 10;
		//textPosList[1].y = min(max(textPosList[1].y, setPoses[1].y), lastPoses[1].y);
	}

	for (int i = 0; i < static_cast<int>(textPosList.size()); i++)
	{
		isPoint[i] ? moveText(i) : slideText(i);
	}

	if (alphaCou <= 255) {
		alphaCou += TitleFadeInSpeed;
		alphaCou = min(max(alphaCou, 0), 255);
	}

}

void TitleScene::slideText(int targettext)
{
	if (isArrive[targettext]) return;

	textPosList[targettext].y += 10;
	textPosList[targettext].y = min(max(textPosList[targettext].y, setPoses[targettext].y), lastPoses[targettext].y);

	if (textPosList[targettext].y == lastPoses[targettext].y) isPoint[targettext] = true;
}

void TitleScene::moveText(int targettext)
{
	if (isArrive[targettext]) return;


	if (!isShotArrive[targettext]) {
		boundCou[targettext]--;
		boundCou[targettext] = min(max(boundCou[targettext], 0), boundCount);

		//shotPos[targettext].y =(defposlist[targettext])-abs(((boundPower / 3)*boundCou[targettext]));
		shotPos[targettext].y = lastPoses[targettext].y-(lastPoses[targettext].y - defposlist[targettext])+((boundCount-boundCou[targettext])*50);
		isShotArrive[targettext] = true;
	}


	if (textPosList[targettext].y <= shotPos[targettext].y) {
		isShotArrive[targettext] = false;
		isPoint[targettext] = false;

	}
	else {
		//textPosList[targettext].y -= (lastPoses[targettext].y-shotPos[targettext].y)*(shotSpeed*(boundCou[targettext] + 1));
		textPosList[targettext].y -= (shotSpeed*(boundCou[targettext] + 1));
	}

	if (!isPoint[targettext] &&boundCou[targettext] <= 0) {
		isArrive[targettext] = true;
		textPosList[targettext].y = lastPoses[targettext].y;
	}
}


void TitleScene::draw() const {

	DrawGraph(MaxTexSize-slideSize,0, ResourceLoader::GetInstance().getTextureID(currentTitleBackID[0]), TRUE);
	DrawGraph(-slideSize, 0, ResourceLoader::GetInstance().getTextureID(currentTitleBackID[1]), TRUE);

	int strLen, strWidth, center, count, heightPoint;
	count = 0;
	heightPoint = 0;
	int forcount = 0;
	for (auto lists : listBase) {
		for (auto my : lists) {
			strLen = strlen(my.c_str());
			strWidth = GetDrawStringWidthToHandle(my.c_str(), strLen, FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			center = static_cast<int>(SCREEN_SIZE.x) / 2;
			
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaCou);
			if (forcount == 1 && isArrive.at(1))SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(sin(sinCount*MathHelper::Pi / 180)) * 255));

			DrawStringToHandle(center - (strWidth / 2), static_cast<int>(textPosList.at(count).y) + ((FontManager::GetInstance().GetFontSize(FontName::GamePlayFont))*heightPoint), my.c_str(), GetColor(255, 255, 255), FontManager::GetInstance().ChangeFont(FontName::GamePlayFont));
			
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			heightPoint++;
		}
		forcount++;
		count++;
		heightPoint = 0;
	}
	//if(isArrive.at(1))SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
	//DrawGraph(textPos.x + 324, textPos.y-28, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_ALPHA_TEX), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void TitleScene::end() {}

bool TitleScene::isEnd() const {
	return isEnd_;
}

Scene TitleScene::next() const {
	return Scene::MainMenu;
}
