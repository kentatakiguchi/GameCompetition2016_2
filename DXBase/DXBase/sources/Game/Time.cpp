#include "Time.h"

#include <DxLib.h>

Time::Time() :
	m_LastFrame(0), m_LastTime(0), m_RealtimeSinceStartup(0), m_FrameCount(0), m_DeltaTime(0) {
}

Time & Time::GetInstance() {
	static Time instance;
	return instance;
}

void Time::update(){
	m_FrameCount++;
	m_RealtimeSinceStartup = m_FrameCount / 60;

	float currentFrame = m_FrameCount;
	if (currentFrame != m_LastFrame) {
		float currentTime = m_RealtimeSinceStartup;
		m_DeltaTime = currentTime - m_LastTime;
		m_LastTime = currentTime;
		m_LastFrame = currentFrame;
	}
}

float Time::deltaTime(){
	return m_DeltaTime;
}

float Time::refreshRate(){
	return static_cast<float>(GetRefreshRate());
}

float Time::correctionTime(){
	return m_DeltaTime * static_cast<float>(GetRefreshRate());
}

