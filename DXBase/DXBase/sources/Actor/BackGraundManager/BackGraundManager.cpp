#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	le(0.0f)
{
	//分からないから一応
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	//プレイヤー変換
	mPlayer = dynamic_cast<TestPlayer*>(world->findActor("Player").get());
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
	//コピーを使わないために＆を付けて参照する(for内でiの中身を弄る場合に使う)
	Vector2 vec = mPlayer->GetVelo();
	le = vec.Length();
	//地面系
	for (auto& i : backStates)
	{
		for (auto& j : i.positions)
		{
			//奥に行くほど遅くする
			Vector2 vec = mPlayer->GetVelo()*(1.0f / layerNum);
			float len = vec.Length();
			//プレイヤーベクトル加算
			j += vec;
			//地面テクスチャサイズ
			Vector2 size = i.size;
			if (j.x <= -size.x)
				j.x = size.x;
			else if (j.x >= size.x)
				j.x = -size.x;
		}
		layerNum--;
	}
	//空のテクスチャサイズ
	Vector2 sizeUp = upBackStates.size;
	//空系
	for (auto& i : upBackStates.positions)
	{
		//一番奥の速度と一緒にする
		Vector2 vec = mPlayer->GetVelo()*(1.0f / backStates.size());
		//プレイヤー速度加算
		i += vec;
		if (i.x <= -sizeUp.x)
			i.x = sizeUp.x;
		else if (i.x >= sizeUp.x)
			i.x = -sizeUp.x;

		if (i.y <= -sizeUp.y)
			i.y = sizeUp.y;
		else if (i.y >= sizeUp.y)
			i.y = -sizeUp.y;
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
	int count = 0;
	for (auto i : backStates)
	{
		for (auto j : i.positions)
		{
			DrawFormatString(550, 25 + 32*count, GetColor(255, 255, 255), "Position:%f,%f", j.x,j.y);
			count++;
		}
	}
	Vector2 a = mPlayer->GetVelo();
	//DrawFormatString(550, 25 + 32, GetColor(255, 255, 255), "vec:%f,%f", a.x, a.y);
	//DrawFormatString(550, 25, GetColor(255, 255, 255), "lenght:%f", le);

}
