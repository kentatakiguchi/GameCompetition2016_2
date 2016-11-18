#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
#include "../Person/Player/Player.h"
#include "../../Actor/Person/Player/PlayerBody.h"
#include "../../World/IWorld.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	stageFlag(true),
	mWorld(world)
{
	//分からないから一応
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	////プレイヤー変換
	//mPlayer = dynamic_cast<PlayerBody*>(world->findActor("Player").get());
	mFloor = dynamic_cast<MovelessFloor*>(world->findActor("MovelessFloor").get());
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
	downBackStates.positions.push_back(Vector2(0, size.y * 2));
	downBackStates.positions.push_back(Vector2(size.x, size.y));
	downBackStates.positions.push_back(Vector2(size.x, size.y * 2));
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
	if (backStates.empty()) return;
	//背景階層の数を取得
	float layerNum = backStates.size();
	//地面系
	//コピーを使わないために＆を付けて参照する(for内でiの中身を弄る場合に使う)
	for (auto& i : backStates)
	{
		for (auto& j : i.positions)
		{
			//プレイヤーベクトル加算
			j += -mFloor->mVelo*(1.0f / layerNum);
			//地面テクスチャサイズ
			Vector2 size = i.size;
			//x軸のループ
			if (j.x <= -size.x)
				j.x = size.x + i.size.x + j.x;
			else if (j.x >= size.x)
				j.x = -size.x - i.size.x + j.x;
			//地上が見えているか
			if (j.y <= -size.y)
				stageFlag = false;
			else
				stageFlag = true;

		}
		layerNum--;
	}
	//地面テクスチャサイズ
	Vector2 size = upBackStates.size;
	//空系
	for (auto& i : upBackStates.positions)
	{
		//プレイヤー速度加算
		i += -mFloor->mVelo*(1.0f / backStates.size());
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
		//プレイヤー速度加算
		i += -mFloor->mVelo;
		//x軸のループ
		if (i.x <= -size.x)
			i.x = size.x + size.x + i.x;
		else if (i.x >= size.x)
			i.x = -size.x - size.x + i.x;
		//Y軸のループ(地上が見えていなかった場合)
		if (!stageFlag)
		{
			if (i.y <= -size.y)
				i.y = size.y + size.y + i.y;
			else if (i.y >= size.y)
				i.y = -size.y - size.y + i.y;
		}
	}
}

void BackGraundManager::Draw() const
{
	//空の描写
	for (auto i : upBackStates.positions)
	{
		DrawGraph(i.x, i.y, upBackStates.id, true);
	}
	//地上の描写
	for (auto i : backStates)
	{
		for (auto j : i.positions)
		{
			DrawGraph(j.x, j.y, i.id, true);
		}
	}
	//地下の描写
	for (auto i : downBackStates.positions)
	{
		DrawGraph(i.x, i.y, downBackStates.id, true);
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
