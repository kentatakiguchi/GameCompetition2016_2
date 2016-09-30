#ifndef _ISCENE_H_
#define _ISCENE_H_

#include "DxLib.h"

#include "Scene.h"

#include "../../Game/Time.h"

//シーン抽象インターフェース
class IScene{
public:
	//仮想デストラクタ
	virtual ~IScene(){}
	//初期化
	virtual void start() = 0;
	//更新
	virtual void update() = 0;
	//描画
	virtual void draw() const = 0;
	//終了フラグ
	virtual bool isEnd() const = 0;
	//次のシーン
	virtual Scene next() const = 0;
	//終了
	virtual void end() = 0;
public:
	bool isEnd_;
};

#endif