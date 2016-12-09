#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
#include "../Person/Player/Player.h"
#include "../../Actor/Person/Player/PlayerBody.h"
#include "../../World/IWorld.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	stageFlag(true),
	mWorld(world)
{
	////プレイヤー変換
	//mPlayer = dynamic_cast<PlayerBody*>(world->findActor("Player").get());
	mFloor = dynamic_cast<MovelessFloor*>(world->findActor("MovelessFloor").get());
}

BackGraundManager::~BackGraundManager()
{
}

void BackGraundManager::SetBackGraund(TextureID id1, TextureID id2,bool frontGraund)
{
	BackGraundState backState;
	//サイズを追加
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id1);
	Vector2 size = backState.size;
	//手前に表示するか
	backState.frontGraundFlag = frontGraund;
	//ポジションと番号を設定
	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id1);
	indexPos.position = Vector2::Zero;
	backState.indexPos.push_back(indexPos);
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id2);
	indexPos.position = Vector2(size.x, 0.0f);
	backState.indexPos.push_back(indexPos);
	//入れる
	backStates.push_back(backState);
}

void BackGraundManager::SetTateBackGraund(TextureID id1, TextureID id2)
{
	BackGraundState backState;
	//サイズを追加
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id1);
	Vector2 size = backState.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id1);
	indexPos.position = Vector2::Zero;
	backState.indexPos.push_back(indexPos);
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id2);
	indexPos.position = Vector2(0.0f, -size.y);
	backState.indexPos.push_back(indexPos);
	//入れる
	backStates.push_back(backState);
}

void BackGraundManager::SetTateYokoBackGraund(TextureID id)
{
	//サイズ取得
	tateYokoState.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = tateYokoState.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);

	indexPos.position = Vector2(size.x, 0.0f);
	tateYokoState.indexPos.push_back(indexPos);
	indexPos.position = Vector2(-size.x, 0.0f);
	tateYokoState.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, size.y);
	tateYokoState.indexPos.push_back(indexPos);
	indexPos.position = Vector2(-size.x, size.y);
	tateYokoState.indexPos.push_back(indexPos);

}

void BackGraundManager::SetUpBackGraund(TextureID id)
{
	//サイズを追加
	upBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);

	indexPos.position = Vector2::Zero;
	upBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(0, -size.y);
	upBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, -size.y);
	upBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, 0);
	upBackStates.indexPos.push_back(indexPos);
}

void BackGraundManager::SetDownBackGraund(TextureID id)
{
	//idを追加
	downBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//サイズを追加
	downBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);
	indexPos.position = Vector2(Vector2(0, size.y));
	downBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(Vector2(0, size.y * 2));
	downBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(Vector2(size.x, size.y));
	downBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(Vector2(size.x, size.y * 2));
	downBackStates.indexPos.push_back(indexPos);


}

void BackGraundManager::AllDeleteBackGraund()
{
}

void BackGraundManager::Update(float deltatime)
{
	//要素内が何もなかったりプレイヤーがnullだったらリターン
	if (backStates.empty()) return;
	//背景階層の数を取得
	float layerNum = backStates.size();
	//地面系
	//コピーを使わないために＆を付けて参照する(for内でiの中身を弄る場合に使う)
	for (auto& i : backStates)
	{
		for (auto& j : i.indexPos)
		{
			//プレイヤーベクトル加算
			j.position += -mFloor->mVelo*(1.0f / layerNum);
			//地面テクスチャサイズ
			Vector2 size = i.size;
			//x軸のループ
			if (j.position.x <= -size.x)
				j.position.x = size.x + i.size.x + j.position.x;
			else if (j.position.x >= size.x)
				j.position.x = -size.x - i.size.x + j.position.x;
			//地上が見えているか
			if (j.position.y <= -size.y)
				stageFlag = false;
			else
				stageFlag = true;

		}
		layerNum--;
	}
	//地面テクスチャサイズ
	Vector2 size = upBackStates.size;
	//空系
	for (auto& i : upBackStates.indexPos)
	{
		//プレイヤー速度加算
		i.position += -mFloor->mVelo*(1.0f / backStates.size());
		//x軸のループ
		if (i.position.x <= -size.x)
			i.position.x = size.x + size.x + i.position.x;
		else if (i.position.x >= size.x)
			i.position.x = -size.x - size.x + i.position.x;
		//Y軸のループ
		if (i.position.y <= -size.y)
			i.position.y = size.y + size.y + i.position.y;
		else if (i.position.y >= size.y)
			i.position.y = -size.y - size.y + i.position.y;
	}
	//地下系
	for (auto& i : downBackStates.indexPos)
	{
		//プレイヤー速度加算
		i.position += -mFloor->mVelo;
		//x軸のループ
		if (i.position.x <= -size.x)
			i.position.x = size.x + size.x + i.position.x;
		else if (i.position.x >= size.x)
			i.position.x = -size.x - size.x + i.position.x;
		//Y軸のループ(地上が見えていなかった場合)
		if (!stageFlag)
		{
			if (i.position.y <= -size.y)
				i.position.y = size.y + size.y + i.position.y;
			else if (i.position.y >= size.y)
				i.position.y = -size.y - size.y + i.position.y;
		}
	}
}

void BackGraundManager::TateUpdate(float deltaTime)
{
	//要素内が何もなかったりプレイヤーがnullだったらリターン
	if (backStates.empty()) return;
	//背景階層の数を取得
	float layerNum = backStates.size();
	//地面系
	//コピーを使わないために＆を付けて参照する(for内でiの中身を弄る場合に使う)
	for (auto& i : backStates)
	{
		for (auto& j : i.indexPos)
		{
			//プレイヤーベクトル加算
			j.position += -mFloor->mVelo*(1.0f / layerNum);
			//地面テクスチャサイズ
			Vector2 size = i.size;
			//x軸のループ
			if (j.position.y <= -size.y)
				j.position.y = size.y + i.size.y + j.position.y;
			else if (j.position.y >= size.y)
				j.position.y = -size.y - i.size.y + j.position.y;
		}
		layerNum--;
	}
	//縦でのスクロールの場合横背景のx軸ループはない
	for (auto& i : tateYokoState.indexPos)
	{
		Vector2 size = tateYokoState.size;
		//プレイヤー速度加算
		i.position += -mFloor->mVelo;
		//Y軸のループ(地上が見えていなかった場合)
		if (i.position.y <= -size.y)
			i.position.y = size.y + size.y + i.position.y;
		else if (i.position.y >= size.y)
			i.position.y = -size.y - size.y + i.position.y;
	}
}

void BackGraundManager::Draw() const
{
	//空の描写
	for (auto i : upBackStates.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
	//地上の描写
	for (auto i : backStates)
	{
		for (auto j : i.indexPos)
		{
			if(!i.frontGraundFlag)
			DrawGraph(j.position.x, j.position.y, j.index, true);
		}
	}
	//地下の描写
	for (auto i : downBackStates.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
	//縦横のスクロール
	for (auto i : tateYokoState.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
}

void BackGraundManager::BackDraw() const
{
	//地上の描写
	for (auto i : backStates)
	{
		for (auto j : i.indexPos)
		{
			if (i.frontGraundFlag)
				DrawGraph(j.position.x, j.position.y, j.index, true);
		}
	}
}

void BackGraundManager::Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness, float friction, float mass)
{
	// バネの伸び具合を計算
	Vector2 stretch = (pos - resPos);
	// バネの力を計算
	Vector2 force = -stiffness * stretch;
	// 加速度を追加
	Vector2 acceleration = force / mass;
	// 移動速度を計算
	velo = friction * (velo + acceleration);

	pos = pos + velo;
}
