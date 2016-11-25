#include "Puyo_Texture_K.h"
#include "../Game/Time.h"
#include "../Math/MathHelper.h"
#include "../Input/InputMgr.h"
#include "../Math/Matrix.h"
#include "../Math/Vector3.h"
//一応正方形で考える
const int SplitSize = 16.0f;

PuyoTextureK::PuyoTextureK(TextureID tex, Vector2 pos, Vector2 scale, float rotate) :
	textureIndex(ResourceLoader::GetInstance().getTextureID(tex)),
	textureSize(ResourceLoader::GetInstance().GetTextureSize(tex)),
	mPosition(pos),
	mScale(scale),
	mRotate(rotate)
{
	loopX = textureSize.x / SplitSize;
	loopY = textureSize.y / SplitSize;
	//動かない頂点をセット
	PuyoVertexSetInit();
	//グラフィックの設定
	PuyoGraphSplit();
	//グラフィックに頂点を設定
	PuyoGraphVertex();


	time = 0.0f;

	test = Vector2(0, 0);
	tesTimer = 0.0f;
	tesNum = 100.0f;
	testVelo = 0.0f;
	testRes = 200.0f;
}

PuyoTextureK::~PuyoTextureK()
{
}

void PuyoTextureK::SetPosition(Vector2 pos, Vector2 scale, float rotate)
{
	mPosition = pos;
	mScale = scale;
	mRotate = rotate;
}
void PuyoTextureK::PuyoUpdate()
{
	//頂点のバネ系を毎フレーム更新
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			Vector2 pos = Vector2(x*SplitSize, y*SplitSize);
			//回転とスケールのマトリクスを作成
			Matrix mat;
			mat =
				Matrix::CreateTranslation(Vector3(pos.x - textureSize.x / 2, pos.y - textureSize.y / 2, 0.0f))*
				Matrix::CreateRotationZ(mRotate)*
				Matrix::CreateTranslation(Vector3(textureSize.x / 2, textureSize.y / 2, 0.0f));


			//Matrix veloMat = Matrix::CreateTranslation(Vector3(commonVertexH[x][y].velocity.x, commonVertexH[x][y].velocity.y, 0))*
			//	Matrix::CreateRotationZ(mRotate);

			//全頂点の時間を進める(振動が伝わる時間も配慮)
			commonVertexH[x][y].vibrationTimer += 1.0f*Time::GetInstance().deltaTime();
			//正規化
			commonVertexH[x][y].velocity = commonVertexH[x][y].velocity.Normalize();
			//numをClamp
			//if(!commonVertexH[x][y].PowerFlag)
			//commonVertexH[x][y].num=MathHelper::Clamp(commonVertexH[x][y].num, -commonVertexH[x][y].maxPower, commonVertexH[x][y].maxPower);
			//if (commonVertexH[x][y].vibrationTimer >= commonVertexH[x][y].vibrationTime&&commonVertexH[x][y].power!=0) {
			//	commonVertexH[x][y].num += commonVertexH[x][y].power;
			//	commonVertexH[x][y].power = 0.0f;
			//}
			commonVertexH[x][y].time += 1000.0f*Time::GetInstance().deltaTime();
			MathHelper::Spring(commonVertexH[x][y].num, commonVertexH[x][y].resNum, commonVertexH[x][y].veloNum, 0.2f, 0.5f, 1.5f);
			commonVertexH[x][y].position.x =
				(MathHelper::Sin(commonVertexH[x][y].time)*commonVertexH[x][y].num)*
				commonVertexH[x][y].velocity.x + mat.Translation().x - textureSize.x / 2;
			commonVertexH[x][y].position.y =
				(MathHelper::Sin(commonVertexH[x][y].time)*commonVertexH[x][y].num)*
				commonVertexH[x][y].velocity.y + mat.Translation().y - textureSize.y / 2;
		}
	}

	//頂点情報を毎フレーム更新
	PuyoVertexSet();
}

void PuyoTextureK::PuyoDraw()
{
	//描写
	for (int y = 0; y < loopY; y++)
	{
		for (int x = 0; x < loopX; x++)
		{
			VertexPos vp = spriteVertexH[x][y];
			DrawModiGraphF(
				vp.LeftTopPos.x, vp.LeftTopPos.y,
				vp.RightTopPos.x, vp.RightTopPos.y,
				vp.RightDownPos.x, vp.RightDownPos.y,
				vp.LeftDownPos.x, vp.LeftDownPos.y,
				spriteIndexsH[x][y], TRUE);
		}
	}

	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			DrawCircle(commonVertexH[x][y].position.x + mPosition.x, commonVertexH[x][y].position.y + mPosition.y, 2, GetColor(0, 0, 255));
		}
	}
	//DrawCircle(test.x + 100, test.y + 100, 10, GetColor(255, 255, 0));
	//DrawFormatString(500,128, GetColor(255, 255, 255), "座標:%f,%f",test.x,test.y);
}

void PuyoTextureK::PuyoGraphSplit()
{
	//分割した画像情報を代入
	for (int y = 0; y < loopY; y++)
	{
		for (int x = 0; x < loopX; x++)
		{
			//右上の座標
			Vector2 splitLeftUp;
			splitLeftUp = Vector2(x*SplitSize, y*SplitSize);
			spriteIndexsH[x][y] = DerivationGraph(splitLeftUp.x, splitLeftUp.y, SplitSize, SplitSize, textureIndex);
		}
	}
}

void PuyoTextureK::PuyoGraphVertex()
{
	//画像に頂点を打つ
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			commonVertexH[x][y].position = Vector2(x*SplitSize, y*SplitSize);
		}
	}
	PuyoVertexSet();
}

void PuyoTextureK::PuyoVertexSet()
{
	//頂点情報を分割画像にいれる
	for (int y = 0; y < loopY; y++)
	{
		for (int x = 0; x < loopX; x++)
		{
			VertexPos vertex;
			vertex.LeftTopPos = commonVertexH[x][y].position + mPosition;
			vertex.LeftDownPos = commonVertexH[x][y + 1].position + mPosition;
			vertex.RightTopPos = commonVertexH[x + 1][y].position + mPosition;
			vertex.RightDownPos = commonVertexH[x + 1][y + 1].position + mPosition;
			spriteVertexH[x][y] = vertex;
		}
	}
}
void PuyoTextureK::PuyoVertexSetInit()
{
	//画像に頂点を打つ
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			commonVertexHNoMove[x][y].position = Vector2(x*SplitSize, y*SplitSize);
		}
	}
}
void PuyoTextureK::PuyoAddPower(Vector2 pos, Vector2 velo)
{
	float Amplitude = 15.0f;
	//遠くに行くほどふり幅が小さい
	float AmplitudeVib = 1.0f;
	float count = 0;

	Vector2 sevePos = Vector2(999, 999);
	int x_ = 0;
	int y_ = 0;
	//設定された一番近い配列の場所を調べる
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			if ((commonVertexHNoMove[x][y].position - pos).Length() <= (sevePos - pos).Length())
			{
				sevePos = commonVertexHNoMove[x][y].position;
				x_ = x;
				y_ = y;
			}
		}
	}

	for (int y = 0; y <= 15; y++)
	{
		AmplitudeVib = y + 1;
		count = 0;
		for (int x = 0; x <= 15; x++)
		{
			if (count >= AmplitudeVib)
				AmplitudeVib++;
			count++;

			if ((x + x_) <= 16 && (y + y_) <= 16 &&
				(x + x_) >= 0 && (y + y_) >= 0)
			{
				commonVertexH[x + x_][y + y_].vibrationTimer = 0.0f;
				commonVertexH[x + x_][y + y_].vibrationTime = AmplitudeVib / 100.0f;
				commonVertexH[x + x_][y + y_].velocity += velo;
				commonVertexH[x + x_][y + y_].resNum = 0.0f;
				//commonVertexH[x + x_][y + y_].num += 20.0f / AmplitudeVib;
				commonVertexH[x + x_][y + y_].power = 100.0f / AmplitudeVib;
				commonVertexH[x + x_][y + y_].PowerFlag = true;
			}
			if ((x + x_) <= 16 && (y_ - y) <= 16 &&
				(x + x_) >= 0 && (y_ - y) >= 0)
			{
				commonVertexH[x + x_][y_ - y].vibrationTimer = 0.0f;
				commonVertexH[x + x_][y_ - y].vibrationTime = AmplitudeVib / 100.0f;
				commonVertexH[x + x_][y_ - y].velocity += velo;
				commonVertexH[x + x_][y_ - y].resNum = 0.0f;
				//commonVertexH[x + x_][y_ - y].num += 20.0f / AmplitudeVib;
				commonVertexH[x + x_][y_ - y].power = 100.0f / AmplitudeVib;
				commonVertexH[x + x_][y_ - y].PowerFlag = true;
			}
			if ((x_ - x) <= 16 && (y_ - y) <= 16 &&
				(x_ - x) >= 0 && (y_ - y) >= 0)
			{
				commonVertexH[x_ - x][y_ - y].vibrationTimer = 0.0f;
				commonVertexH[x_ - x][y_ - y].vibrationTime = AmplitudeVib / 100.0f;
				commonVertexH[x_ - x][y_ - y].velocity += velo;
				commonVertexH[x_ - x][y_ - y].resNum = 0.0f;
				//commonVertexH[x_ - x][y_ - y].num += 20.0f / AmplitudeVib;
				commonVertexH[x_ - x][y_ - y].power = 100.0f / AmplitudeVib;
				commonVertexH[x_ - x][y_ - y].PowerFlag = true;
			}
			if ((x_ - x) <= 16 && (y_ + y) <= 16 &&
				(x_ - x) >= 0 && (y_ + y) >= 0)
			{
				//commonVertexH[x_ - x][y_ + y].amplitude = Amplitude / AmplitudeVib;
				commonVertexH[x_ - x][y_ + y].vibrationTimer = 0.0f;
				commonVertexH[x_ - x][y_ + y].vibrationTime = AmplitudeVib / 100.0f;
				commonVertexH[x_ - x][y_ + y].velocity += velo;
				commonVertexH[x_ - x][y_ + y].resNum = 0.0f;
				//commonVertexH[x_ - x][y_ + y].num += 20.0f/AmplitudeVib;
				commonVertexH[x_ - x][y_ + y].power = 100.0f / AmplitudeVib;
				commonVertexH[x_ - x][y_ + y].PowerFlag = true;
			}
		}
	}
}






void PuyoTextureK::PuyoAddPowerDx(Vector2 pos, Vector2 velo)
{
	float Amplitude = 15.0f;
	//遠くに行くほどふり幅が小さい
	float AmplitudeVib = 1.0f;
	float count = 0;

	Vector2 sevePos = Vector2(999, 999);
	int x_ = 0;
	int y_ = 0;
	//設定された一番近い配列の場所を調べる
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			if ((commonVertexHNoMove[x][y].position - pos).Length() <= (sevePos - pos).Length())
			{
				sevePos = commonVertexHNoMove[x][y].position;
				x_ = x;
				y_ = y;
			}
		}
	}

	for (int y = 0; y < loopY / 2; y++)
	{
		AmplitudeVib = y + 1;
		count = 0;
		for (int x = 0; x < loopX / 2; x++)
		{
			if (count >= AmplitudeVib)
				AmplitudeVib++;
			count++;

			if ((x + x_) <= 17 && (y + y_) <= 17 &&
				(x + x_) >= 0 && (y + y_) >= 0)
			{
				commonVertexH[x + x_][y + y_].vibrationTimer = 0.0f;
				//commonVertexH[x + x_][y + y_].vibrationTime += AmplitudeVib / 1000.0f;
				commonVertexH[x + x_][y + y_].time = 0.0f;
				commonVertexH[x + x_][y + y_].velocity += velo;
				commonVertexH[x + x_][y + y_].resNum = 0.0f;
				commonVertexH[x + x_][y + y_].maxPower = (velo.Length() * 40);
				commonVertexH[x + x_][y + y_].num += velo.Length();
				commonVertexH[x + x_][y + y_].PowerFlag = false;
				commonVertexH[x + x_][y + y_].power = 0.0f;
			}
			if ((x + x_) <= 17 && (y_ - y) <= 17 &&
				(x + x_) >= 0 && (y_ - y) >= 0)
			{
				commonVertexH[x + x_][y_ - y].vibrationTimer = 0.0f;
				//commonVertexH[x + x_][y_ - y].vibrationTime += AmplitudeVib / 1000.0f;
				commonVertexH[x + x_][y_ - y].time = 0.0f;
				commonVertexH[x + x_][y_ - y].velocity += velo;
				commonVertexH[x + x_][y_ - y].resNum = 0.0f;
				commonVertexH[x + x_][y_ - y].maxPower = (velo.Length() * 40);
				commonVertexH[x + x_][y_ - y].num += velo.Length();
				commonVertexH[x + x_][y_ - y].PowerFlag = false;
				commonVertexH[x + x_][y_ - y].power = 0.0f;
			}
			if ((x_ - x) <= 17 && (y_ - y) <= 17 &&
				(x_ - x) >= 0 && (y_ - y) >= 0)
			{
				commonVertexH[x_ - x][y_ - y].vibrationTimer = 0.0f;
				//commonVertexH[x_ - x][y_ - y].vibrationTime += AmplitudeVib / 1000.0f;
				commonVertexH[x_ - x][y_ - y].time = 0.0f;
				commonVertexH[x_ - x][y_ - y].velocity += velo;
				commonVertexH[x_ - x][y_ - y].resNum = 0.0f;
				commonVertexH[x_ - x][y_ - y].maxPower = (velo.Length()*40.0f);
				commonVertexH[x_ - x][y_ - y].num += velo.Length();
				commonVertexH[x_ - x][y_ - y].PowerFlag = false;
				commonVertexH[x_ - x][y_ - y].power = 0.0f;
			}
			if ((x_ - x) <= 16 && (y_ + y) <= 16 &&
				(x_ - x) >= 0 && (y_ + y) >= 0)
			{
				commonVertexH[x_ - x][y_ + y].vibrationTimer = 0.0f;
				//commonVertexH[x_ - x][y_ + y].vibrationTime += AmplitudeVib / 1000.0f;
				commonVertexH[x_ - x][y_ + y].time = 0.0f;
				commonVertexH[x_ - x][y_ + y].velocity += velo;
				commonVertexH[x_ - x][y_ + y].resNum = 0.0f;
				commonVertexH[x_ - x][y_ + y].maxPower = (velo.Length()*40.0f);
				commonVertexH[x_ - x][y_ + y].num += velo.Length();
				commonVertexH[x_ - x][y_ + y].PowerFlag = false;
				commonVertexH[x_ - x][y_ + y].power = 0.0f;
			}
		}
	}
}

void PuyoTextureK::PuyoAddPowerEx(Vector2 vec, Vector2 velo,float power)
{
	int x_ = 0;
	int y_ = 0;
	Vector2 kakeru = vec*110.0f;
	{
	Vector2 texCen = Vector2(textureSize.x / 2, textureSize.y / 2);
	Vector2 vecc = kakeru + texCen;
	Vector2 sevePos = Vector2(9999, 9999);

	//設定された一番近い配列の場所を調べる
	for (int y = 0; y <= loopY; y++)
		for (int x = 0; x <= loopX; x++)
		{
			if (Vector2::Distance(commonVertexHNoMove[x][y].position, vecc) <= Vector2::Distance(sevePos, vecc))
			{
				sevePos = commonVertexHNoMove[x][y].position;
				x_ = x;
				y_ = y;
			}
		}
	}
	for (int y = -8; y <= 8; y++)
	{
		for (int x = -8; x <= 8; x++)
		{
			if(x_ + x<=loopX&& y_ + y<=loopY&&y_ + y>=0&& x_ + x>=0)
				PuyoAddPowerDxSub(x_+x, y_+y, velo, power);
		}
	}
	//DrawCircle(commonVertexH[x_][y_].position.x + mPosition.x, commonVertexH[x_][y_].position.y + mPosition.y, 5, GetColor(255, 0, 0));
	//PuyoAddPowerDxSub(x_, y_, velo, power);
	DrawFormatString(500, 128, GetColor(255, 255, 255), "velo:%f,%f", velo.x, velo.y);
}
//仕様変更版
void PuyoTextureK::PuyoAddPowerDxSub(int x_, int y_, Vector2 velo,float power)
{
	Vector2 pos = commonVertexHNoMove[x_][y_].position;
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::N))
	//{
	//	testRes -= 50.0f*Time::GetInstance().deltaTime();
	//}
	for (int y = 0; y <= loopY; y++)
	{
		for (int x = 0; x <= loopX; x++)
		{
			float dis = Vector2::Distance(pos, commonVertexHNoMove[x][y].position);
			commonVertexH[x][y].time = 0.0f;
			if (dis <= 140.0f)
			{
				dis++;
				commonVertexH[x][y].resNum = 0.0f;
				commonVertexH[x][y].num += (power*20.0f)/dis*Time::GetInstance().deltaTime();
 				commonVertexH[x][y].velocity = velo;
			}
		}
	}

}