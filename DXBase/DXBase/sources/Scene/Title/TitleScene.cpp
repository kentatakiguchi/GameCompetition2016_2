#include "TitleScene.h"
#include"../../ResourceLoader/ResourceLoader.h"

static const float titleY = 10;
static const float spaceY = 400;
static const int boundCount = 5;
static const float boundPower = 30;
static const float shotSpeed = 5;
TitleScene::TitleScene(SceneDataKeeper* keeper) :
	id(0),sinCount(0){
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "Title";

	defposlist[0] = titleY;
	defposlist[1] = spaceY;

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
	list2.push_back("SPACEボタンを押してください");
	listBase[1] = list2;
	textPos = Vector2(200, 600);
	lastPoses[1] = textPos;
	setPoses[1] = Vector2(0, spaceY);
	textPosList.push_back(setPoses[1]);
	changeTextList.clear();

}

TitleScene::~TitleScene(){}

void TitleScene::start() {
	isEnd_ = false;

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
}

void TitleScene::update() {
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

	for (int i = 0; i < textPosList.size(); i++)
	{
		isPoint[i] ? moveText(i) : slideText(i);
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
	if(isArrive.at(1))SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(sin(sinCount*MathHelper::Pi / 180)) * 255);
	DrawGraph(textPos.x + 100, textPos.y, ResourceLoader::GetInstance().getTextureID(TextureID::TEXT_ALPHA_TEX), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void TitleScene::end() {}

bool TitleScene::isEnd() const {
	return isEnd_;
}

Scene TitleScene::next() const {
	return Scene::MainMenu;
}
