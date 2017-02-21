#pragma once

#include "DxLib.h"
#include"../Base/Scene.h"
#include<vector>
#include<map>
#include"../StageClear/StageClearTextAnm.h"
#include"../../ResourceLoader/ResourceLoader.h"
#include"../Base/SceneDataKeeper.h"

class ClearScreen {
public:
	ClearScreen() {}
	ClearScreen(SceneDataKeeper* keeper);
	~ClearScreen() {
		ChangeVolumeSoundMem(255, ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_SHOW));
		StopSoundMem(ResourceLoader::GetInstance().getSoundID(SoundID::SE_RESULT_ROLL));
	}
	void start(const std::string& name);
	bool update(std::string name, Scene& next);
	void draw() const;
	//bool isCounT() const{
	//	return Count_ <= 0;
	//};	
	//�󂯎�����l�̌�����Ԃ� baseNum:���������߂����l
	int countDigits(int baseNum) const{
		if (baseNum == 0)return 1;

		int mathNum = abs(baseNum);
		int ans = (int)log10(mathNum) + 1;
		return ans;
	}

	//�󂯎�����l�̂����A�w�肳�ꂽ���ԍ��̒l�݂̂�`�悷��(posx,y�́A���ꂼ��l���S���`�悳���ꍇ�̍��[�Ƃ���)
	int drawTagertNumber(int targetNum, int targetDigit, int posx, int posy, int NumTexType = 1) const{
		int baseNum = targetNum;
		int drawNum = targetNum;

		int posCount = 0;
		std::vector<int> drawNumberList;

		//drawNumberList�́A[0]��1�̈�
		for (;;) {

			//�v�Z�l��10������������_�ŁA�Ō�̒l(�ł�������)��drawNumberList�ɑ������
			if (baseNum < 10) {
				drawNumberList.push_back(baseNum);
				break;
			}
			//1�̈ʂ��珇��drawNumberList�ɑ�����Ă���
			drawNum = (int)(baseNum*0.1);
			drawNum = drawNum * 10;
			int textNum = baseNum - drawNum;
			drawNumberList.push_back(textNum);
			baseNum = (int)(baseNum*0.1);
			posCount++;
		}

		//drawNumberList��size�͌����A���[�̕`��ʒu�͍��W�ʂ�̂��߁Asize����-1���鎖�ŁAposx,y����Ƃ����E�[�܂ł̌������Z�o����
		int drawPosCount = drawNumberList.size() - 1;

		//�E�[�̕`��ʒu���v�Z����(posx���AdrawPosCount���E�ɂ��炷)
		//int drawx = posx + ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][drawNumberList[0]]).x*(drawPosCount);
		int drawx = posx - ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][drawNumberList[0]]).x;

		for (int i = 0; i < drawNumberList.size(); i++) {
			//drawx����A�`�悳���Ώۂ̌������փY����(drawNumberList��0���E�[�̒l�Ȃ���)
			if (i == targetDigit)DrawGraph(drawx - ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][drawNumberList[i]]).x*i, posy, ResourceLoader::GetInstance().getTextureID(numberTexes_[NumTexType][drawNumberList[i]]), TRUE);	
		}
		//������Ԃ�
		int ret = drawNumberList.size();
		return ret;

	}
	//1�Ŕ��A0�Ő�
	int drawNumber(int targetNum,int posx,int posy,int NumTexType=1,int maxSize=3,float drawSize=1.f) const{
		int drawNum = targetNum;
		int baseNum = targetNum;
		int posCount = 0;
		std::vector<int> drawNumberList;

		for (int i = 0;i<maxSize;i++) {

			if (baseNum < 10) {
				drawNumberList.push_back(baseNum);
				break;
			}

			drawNum = (int)(baseNum*0.1);
			drawNum = drawNum * 10;
			int textNum = baseNum - drawNum;
			drawNumberList.push_back(textNum);
			baseNum = (int)(baseNum*0.1);
			posCount++;
		}

		int drawx = posx +ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][drawNumberList[0]]).x*(maxSize-1);

		for (int i = 0; i < maxSize; i++) {
			//drawNumberList�̌�����maxSize��������Ă����ꍇ�A�����ȏ��loop���J�b�g����
			if (i>=drawNumberList.size()) {
				continue;
			}
			DrawRotaGraph2(drawx -(ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][drawNumberList[i]]).x*i*drawSize),posy,0,0,drawSize,0, ResourceLoader::GetInstance().getTextureID(numberTexes_[NumTexType][drawNumberList[i]]), TRUE);
		}
		int ret = drawNumberList.size();
		return ret;
	}
	//�w��pos�ɁAmaxSize�������̃X���b�g����ׂĕ`�悷��
	void LoopNumber(int posx,int posy,int useLoopType, int NumTexType = 1,int maxSize=3,float drawSize=1.f) const{
		int LoopCount = useLoopType;
		int drawx = posx + ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][0]).x*(maxSize - 1);
		
		for (int i = 0; i < maxSize; i++) {
			DrawRotaGraph2(drawx - (ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][NumberForLoop_[LoopCount]]).x*i*drawSize), posy,0,0,drawSize,0, ResourceLoader::GetInstance().getTextureID(numberTexes_[NumTexType][NumberForLoop_[LoopCount]]), TRUE);
			LoopCount++;
			if (LoopCount > 9) {
				LoopCount=0;
			}
		}
	}
	//�w��pos����AnumPos���Ԗڂ̈ʒu�ɃX���b�g��`�悷��
	void LoopPointNumber(int posx, int posy, int& useLoopType, int numPos, int NumTexType = 1,float drawSize=1.f) const {
		DrawRotaGraph2(posx + (ResourceLoader::GetInstance().GetTextureSize(numberTexes_[NumTexType][NumberForLoop_[useLoopType]]).x*numPos*drawSize), posy,0,0,drawSize,0, ResourceLoader::GetInstance().getTextureID(numberTexes_[NumTexType][NumberForLoop_[useLoopType]]), TRUE);
		useLoopType++;
		if (useLoopType > 9) {
			useLoopType = 0;
		}
	}
private:
	std::vector<std::string> changeTextList;
	std::vector<std::vector<std::string>> listBase;
	std::vector<Vector2> textPosList;
	std::map<int, TextureID> textIDs;

	std::map<std::string, Vector2> textPositions;

	std::vector<std::vector<TextureID>> numberTexes_;
	
	std::map<std::string,TextureID> stageTexes_;
	std::string stageName_;
	StageClearTextAnm anmer_;
	SceneDataKeeper* keeper_;
	//int Count_;
	int ints;
	int sinCount;
	bool isCircleDraw_;
	float drawNumberController_;

	std::vector<int> NumberForLoop_;

	std::map<std::string, bool> isDraw_;
	std::map<std::string, bool> isBaseDraw_;
	std::vector<std::string> nameList;
	std::vector<std::string> nameBaseList;
	int usingIntCount;
	int usingBaseIntCount;

	bool isFirst_;
	bool isSoundFirst_;
	bool buttonLock_;
	int buttonLockCount_;

	bool isMaxDraw_;
	bool isRankDraw_;
	std::vector<bool> isStarDraw_;
	int baseLastDraw_;
	int drawLastDraw_;

	bool isRankSoundCheckFirst_;
	int rankSoundCheckCount_;

	std::vector<int> FullStarCountVec;

	float lastScoreTime;
	int isLastScoreDCou;
	float lastScoreAnsTime;
	int isLastScoreAnsDCou;

	std::vector<bool> numberDrawMaster_;

	float useCount;
	bool isMyssFirst_;

	bool isMusLastFirst_;

	bool isEnterDraw_;
	float isEnterDrawNum_;

	int myd;

	bool isAlreadyStart_;

};