#include "TutorialManager.h"

#include "../../World/World.h"

#include "../../FileReader/CsvReader.h"

#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Input/InputMgr.h"
#include "../../Define.h"

#include <algorithm>

TutorialManager::TutorialManager() :
	timer_(0),
	textIndex_(0),
	currentTutorial_(0),
	currentTurn_(0),
	alpha_(255),
	color_(GetColor(255, 255, 255)),
	text1_(""),
	text2_(""),
	buttyPos_(Vector2(0, 0)),
	rettyPos_(Vector2(0, 0)){}

TutorialManager::~TutorialManager(){}

void TutorialManager::load_csv(const std::string& file_name){
	CsvReader reader;
	reader.load(file_name);

	for (int rowN = 0; rowN < reader.rows() - 1; rowN++){
		Elements elements;
		elements.posX = reader.geti(rowN, POSITION);
		elements.speaker = reader.get(rowN, SPEEKER);
		elements.text1 = reader.get(rowN, TEXT_FIRST);
		if (reader.columns(rowN) - 1 >= TEXT_SECOND) {
			elements.text2 = reader.get(rowN, TEXT_SECOND);
		}
		contents_[reader.geti(rowN, NUMBER)].push_back(elements);
	}
}

void TutorialManager::init(IWorld* world){
}

void TutorialManager::update(IWorld* world, float deltaTime){

	auto butty = world->findActor("PlayerBody1");
	auto retty = world->findActor("PlayerBody2");

	if (butty == nullptr || retty == nullptr)return;

	
	if (butty->getPosition().x > contents_[std::min<int>(currentTutorial_ + 1, contents_.size())][0].posX * CHIPSIZE &&
		retty->getPosition().x > contents_[std::min<int>(currentTutorial_ + 1, contents_.size())][0].posX * CHIPSIZE) {

		if (currentTutorial_ != contents_.size()) {
			changeTutorial();
			world->PlayerNotMove(true);
		}
	}

	if (contents_[currentTutorial_][currentTurn_].text1.size() <= text1_.size() && 
		contents_[currentTutorial_][currentTurn_].text2.size() <= text2_.size() && 
		timer_ >= 5.0f) {
		if (currentTurn_ >= contents_[currentTutorial_].size() - 1) {
			world->PlayerNotMove(false);
		}
		else {
			changeTurn();
		}
	}

	stepText(deltaTime);

	//if (isTutorialEnd() && timer_ >= 5.0f) {
	//	world->is_clear();
	//}



	if (contents_[currentTutorial_][currentTurn_].speaker == "b") {
		drawPos_ = butty->getPosition() * world->GetInv() - Vector2(-100, 300);
		color_ = GetColor(0, 0, 255);
	}
	else if (contents_[currentTutorial_][currentTurn_].speaker == "r") {
		drawPos_ = retty->getPosition() * world->GetInv() - Vector2(-100, 300);
		color_ = GetColor(255, 0, 0);
	}
}

void TutorialManager::draw() const{
	int size = 100;
	SetFontSize(64);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//MathHelper::Lerp(0.0f, 255.0f, alpha_));
	DrawRotaGraph(drawPos_.x, drawPos_.y, 2.0f/*MathHelper::Lerp(0.0f, 2.0f, alpha_)*/, 0.0f, ResourceLoader::GetInstance().getTextureID(TextureID::HUKIDASI_TEX), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0.0f);

	DrawFormatString(drawPos_.x - 350, drawPos_.y - 100, color_, text1_.c_str());
	DrawFormatString(drawPos_.x - 350, drawPos_.y - 100 + size, color_, text2_.c_str());
}

void TutorialManager::changeTutorial(){
	currentTurn_ = 0;
	textIndex_ = 0;
	text1_ = "";
	text2_ = "";
	currentTutorial_ = std::min<int>(currentTutorial_ + 1, contents_.size());
}

void TutorialManager::changeTurn(){
	text1_ = "";
	text2_ = "";
	textIndex_ = 0;
	currentTurn_ = std::min<int>(currentTurn_ + 1, contents_[currentTutorial_].size() - 1);
}

bool TutorialManager::isTutorialEnd(){
	bool tuto = contents_.size() == currentTutorial_;
	bool turn = contents_[currentTutorial_].size() - 1 == currentTurn_;

	return tuto && turn && timer_ >= 5.0f;
}

void TutorialManager::stepText(float deltaTime){
	timer_ += deltaTime * 10;



	if (contents_[currentTutorial_][currentTurn_].text1.size() <= text1_.size() &&
		contents_[currentTutorial_][currentTurn_].text2.size() <= text2_.size()) return;
		
	if (timer_ > 1.0f) {
		if (contents_[currentTutorial_][currentTurn_].text1.size() > text1_.size()) {
			if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE) ||
				InputMgr::GetInstance().IsKeyDown(KeyCode::W)) {
				textIndex_ = contents_[currentTutorial_][currentTurn_].text1.size() / 2;
			}
			
			text1_ = contents_[currentTutorial_][currentTurn_].text1.substr(0, textIndex_ * 2);
		}
		else {
			if (text2_.size() == 0) {
				textIndex_ = 1;
			}
			if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_CIRCLE) ||
				InputMgr::GetInstance().IsKeyDown(KeyCode::W)) {
				textIndex_ = contents_[currentTutorial_][currentTurn_].text2.size() / 2;
			}
			text2_ = contents_[currentTutorial_][currentTurn_].text2.substr(0, textIndex_ * 2);
		}
		textIndex_++;
		timer_ = 0.0f;
	}
}
