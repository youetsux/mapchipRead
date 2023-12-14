#pragma once

const double DEF_TIMER_INTERVAL{ 5 };

class CDTimer
{
	double TIMER_INIT_TIME_;
public:
	CDTimer() :TIMER_INIT_TIME_(DEF_TIMER_INTERVAL), CDTimer_(TIMER_INIT_TIME_), isTimerRun_(true) {}
	CDTimer(double _initTime) :TIMER_INIT_TIME_(_initTime), CDTimer_(TIMER_INIT_TIME_), isTimerRun_(true) {}
	double CDTimer_;
	bool IsTimeOver();
	void ResetTimer();
	void StartTimer();
	void STopTimer();
	bool isTimerRun_;
	void Update();
};

