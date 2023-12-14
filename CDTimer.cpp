#include "stdafx.h"
#include "CDTimer.h"


bool CDTimer::IsTimeOver()
{
	return(CDTimer_ < 0);
}

void CDTimer::ResetTimer()
{
	CDTimer_ = TIMER_INIT_TIME_;
	StartTimer();
}

void CDTimer::StartTimer()
{
	isTimerRun_ = true;
}

void CDTimer::STopTimer()
{
	isTimerRun_ = false;
}

void CDTimer::Update()
{
	if (isTimerRun_)
		CDTimer_ = CDTimer_ - Scene::DeltaTime();
}
