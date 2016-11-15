#pragma once

class Time {
public:
	Time();
	static Time &GetInstance();
	void update();
	float deltaTime();
	float refreshRate();
	float correctionTime();
private:
	float m_LastFrame;
	float m_LastTime;
	float m_RealtimeSinceStartup;
	float m_FrameCount;
	float m_DeltaTime;
};