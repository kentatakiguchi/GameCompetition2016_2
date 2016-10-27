#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
#include "../Person/Player/Player.h"
BackGraundManager::BackGraundManager(IWorld * world):
	stageFlag(true)
{
	//分からないから一応
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	//プレイヤー変換
	mPlayer = dynamic_cast<Player*>(world->findActor("Player").get());
}

BackGraundManager::~BackGraundManager()
{
	//分からないから一応
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
}

void BackGraundManager::SetBackGraund(TextureID id)
{
	BackGraundState backState;
	//idを追加
	backState.id = ResourceLoader::GetInstance().getTextureID(id);
	//サイズを追加
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = backState.size;
	//ポジションを二つ入れる(2枚背景を張り付けるため)
	backState.positions.push_back(Vector2::Zero);
	backState.positions.push_back(Vector2(size.x, 0.0f));
	//入れる
	backStates.push_back(backState);
}

void BackGraundManager::SetUpBackGraund(TextureID id)
{
	//idを追加
	upBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//サイズを追加
	upBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;
	//ポジションを4つ入れる(4枚背景を張り付けるため)
	upBackStates.positions.push_back(Vector2(0, 0));
	upBackStates.positions.push_back(Vector2(0, -size.y));
	upBackStates.positions.push_back(Vector2(size.x, -size.y));
	upBackStates.positions.push_back(Vector2(size.x, 0));

}

void BackGraundManager::SetDownBackGraund(TextureID id)
{
	//idを追加
	downBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//サイズを追加
	downBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;
	//ポジションを4つ入れる(4枚背景を張り付けるため)
	downBackStates.positions.push_back(Vector2(0, size.y));
	downBackStates.positions.push_back(Vector2(0, size.y*2));
	downBackStates.positions.push_back(Vector2(size.x, size.y));
	downBackStates.positions.push_back(Vector2(size.x, size.y*2));
}

void BackGraundManager::AllDeleteBackGraund()
{
	//list内をすべて削除
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	upBackStates.positions.clear();
}

void BackGraundManager::Update(float deltatime)
{
	//要素内が何もなかったりプレイヤーがnullだったらリターン
	if (backStates.empty() || mPlayer == nullptr) return;
	//背景階層の数を取得
	float layerNum = backStates.size();
	//移動するかどうかフラグ
	Vector2 moveFlag = mPlayer->GetMoveFlag();
	//地面系
	//コピーを使わないために＆を付けて参照する(for内でiの中身を弄る場合に使う)
	for (auto& i : backStates)
	{
		for (auto& j : i.positions)
		{
			//奥に行くほど遅くする
			Vector2 vec = mPlayer->GetSpringVelo()*(1.0f / layerNum);
			//移動する場合flagには1が、移動しない場合flagには0が
			vec = Vector2(vec.x*moveFlag.x, vec.y*moveFlag.y);
			//プレイヤーベクトル加算
			j += vec;
			//地面テクスチャサイズ
			Vector2 size = i.size;
			//x軸のループ
			if (j.x <= -size.x)
				j.x = size.x + i.size.x + j.x;
			else if (j.x >= size.x)
				j.x = -size.x - i.size.x + j.x;
		}
		layerNum--;
	}
	//地面テクスチャサイズ
	Vector2 size = upBackStates.size;
	//空系
	for (auto& i : upBackStates.positions)
	{
		//一番奥の速度と一緒にする
		Vector2 vec = mPlayer->GetSpringVelo()*(1.0f / backStates.size());
		//移動する場合flagには1が、移動しない場合flagには0が
		vec = Vector2(vec.x*moveFlag.x, vec.y*moveFlag.y);
		//プレイヤー速度加算
		i += vec;
		//x軸のループ
		if (i.x <= -size.x)
			i.x = size.x + size.x + i.x;
		else if (i.x >= size.x)
			i.x = -size.x - size.x + i.x;
		//Y軸のループ
		if (i.y <= -size.y)
			i.y = size.y + size.y + i.y;
		else if (i.y >= size.y)
			i.y = -size.y - size.y + i.y;
	}
	//地下系
	for (auto& i : downBackStates.positions)
	{
		//一番奥の速度と一緒にする
		Vector2 vec = mPlayer->GetSpringVelo()*(1.0f / backStates.size());
		//プレイヤー速度加算
		i += vec;
		//x軸のループ
		if (i.x <= -size.x)
			i.x = size.x + size.x + i.x;
		else if (i.x >= size.x)
			i.x = -size.x - size.x + i.x;
		//Y軸のループ
		if (i.y <= -size.y)
			i.y = size.y + size.y + i.y;
		else if (i.y >= size.y)
			i.y = -size.y - size.y + i.y;
	}
}

void BackGraundManager::Draw() const
{
	for (auto i : upBackStates.positions)
	{
		DrawGraph(i.x, i.y, upBackStates.id, true);
	}
	for (auto i : backStates)
	{
		for (auto j : i.positions)
		{
			DrawGraph(j.x, j.y, i.id, true);
		}
	}
	//for (auto i : downBackStates.positions)
	//{
	//	DrawGraph(i.x, i.y, downBackStates.id, true);
	//}
}