#include "Movie.h"
#include <DxLib.h>
#include <sstream>
#include "../Define.h"


Movie & Movie::GetInstance() {
	static Movie instance;
	return instance;
}

// �����ǂݍ���
void Movie::Load(const MOVIE_ID& moveID , const std::string& filename)
{
	
	int handle = OpenMovieToGraph(filename.c_str());

	if (handle == -1)
		throw std::string(filename + "�Ƃ�������t�@�C���͑��݂��܂���");
	
	m_movies[moveID] = handle;
}

// ������Đ�����
void Movie::Play(const MOVIE_ID& moveID)
{
	PlayMovieToGraph(GetHandle(moveID));
}

// ������ꎞ��~����
void Movie::Stop(const MOVIE_ID& moveID)
{
	PauseMovieToGraph(GetHandle(moveID));
}

// ����̍Đ��ʒu��ύX����(/�b)
void Movie::Seek(const MOVIE_ID& moveID, float time)
{
	SeekMovieToGraph(GetHandle(moveID), static_cast<int>(time * 1000));
}

// ����̌��݂̍Đ��ʒu���󂯎��(/�b)
float Movie::IsTime(const MOVIE_ID& moveID)
{
	return TellMovieToGraph(GetHandle(moveID)) / 1000.0f;
}

// ���悪�Đ�����Ă��邩�ۂ��󂯎��
bool Movie::IsPlay(const MOVIE_ID& moveID)
{
	return GetMovieStateToGraph(GetHandle(moveID)) == 1;
}

// �Đ���Ԃ̓����\������
void Movie::Draw() const
{
	for (const auto& movie : m_movies)
	{
		DrawExtendGraph(0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y, movie.second, FALSE);
	}
}

void Movie::Clear()
{
	for (const auto& movie : m_movies)
	{
		DeleteGraph(movie.second);
	}
}
int Movie::GetHandle(MOVIE_ID moveID)
{
	return m_movies[moveID];
}