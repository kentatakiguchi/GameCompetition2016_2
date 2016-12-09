#include "CreditScene.h"
#include"../../ResourceLoader/ResourceLoader.h"


CreditScene::CreditScene(SceneDataKeeper* keeper) :
	id(0), sinCount(0),isPlay_(false) {
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "Credit";


	//int listNum = 0;
	//listBase.push_back(changeTextList);
	//std::vector<std::string> list1;
	//list1.push_back("�^�C�g��");
	//listBase[0] = list1;
	//lastPoses[0] = Vector2(200, 200);
	//setPoses[0] = Vector2(0, titleY);
	//textPosList.push_back(setPoses[0]);
	//changeTextList.clear();

	//listBase.push_back(changeTextList);
	//std::vector<std::string> list2;
	//list2.push_back("SPACE�{�^���������Ă�������");
	//listBase[1] = list2;
	//textPos = Vector2(200, 600);
	//lastPoses[1] = textPos;
	//setPoses[1] = Vector2(0, spaceY);
	//textPosList.push_back(setPoses[1]);
	//changeTextList.clear();

}

CreditScene::~CreditScene() {}

void CreditScene::start() {
	isEnd_ = false;

	isPlay_ = false;
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
}

void CreditScene::update() {
	sinCount += FlashTempo;
	sinCount = sinCount % 360;
	sinCount = min(max(sinCount, 0), 360);

	if (!isPlay_) {
		isPlay_ = true;
		PlayMovie("./resources/file/pv.avi", 1, DX_MOVIEPLAYTYPE_BCANCEL);
	}

	if (InputMgr::GetInstance().IsPushButton()) {
		isEnd_=true;
	}
	//if (GetMovieStateToGraph())
	{
		//isEnd_ = true;
	}

	{
		//textPosList[1].y += 10;
		//textPosList[1].y = min(max(textPosList[1].y, setPoses[1].y), lastPoses[1].y);
	}

}

void CreditScene::draw() const {
}

void CreditScene::end() {}

bool CreditScene::isEnd() const {
	return isEnd_;
}

Scene CreditScene::next() const {
	return Scene::Title;
}