#include "timer.h"

using namespace lz;

Timer::Timer()
{
	reset();
}

Timer::~Timer()
{
}

void Timer::reset()
{
	m_start = t_high_res_clock::now();
}
