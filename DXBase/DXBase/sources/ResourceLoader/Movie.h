#pragma once

#include <unordered_map>
#include <string>
#include"ResourceLoader.h"
class Movie
{
public:
	static Movie& GetInstance();
	///<summary>
	/// �����ǂݍ���
	///</summary>
	void Load(const MOVIE_ID& moveID, const std::string& filename);

	///<summary>
	/// ������Đ�����
	///</summary>
	void Play(const MOVIE_ID& moveID);

	///<summary>
	/// ������ꎞ��~����
	///</summary>
	void Stop(const MOVIE_ID& moveID);

	///<summary>
	/// ����̍Đ��ʒu��ύX����(/�b)
	///</summary>
	void Seek(const MOVIE_ID& moveID, float time);

	///<summary>
	/// ����̌��݂̍Đ��ʒu���󂯎��(/�b)
	///</summary>
	float IsTime(const MOVIE_ID& moveID);

	///<summary>
	/// ���悪�Đ�����Ă��邩�ۂ��󂯎��
	///</summary>
	bool IsPlay(const MOVIE_ID& moveID);

	///<summary>
	/// �Đ���Ԃ̓����\������
	///</summary>
	void Draw() const;


	void Clear();
private:

	int GetHandle(MOVIE_ID moveID);
	std::unordered_map<const MOVIE_ID, int> m_movies;

};