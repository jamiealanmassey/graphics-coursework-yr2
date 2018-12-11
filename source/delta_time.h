#ifndef _DELTA_TIME_H
#define _DELTA_TIME_H

#define DELTA_CACHE_SIZE 40

#include <vector>
#include <chrono>

class DeltaTime
{
private:
	DeltaTime();
	~DeltaTime();

public:
	void start();
	void tick();
	
	const float getDelta() const;
	const float getTimeFromStart() const;

	static DeltaTime& instance();

protected:
	float m_delta;
	std::vector<float> m_deltaCache;
	std::chrono::high_resolution_clock m_clock;
	std::chrono::high_resolution_clock::time_point m_timeTick;
	std::chrono::high_resolution_clock::time_point m_timeStart;
};

#define DELTA_TIME DeltaTime::instance().getDelta()
#define TOTAL_TIME DeltaTime::instance().getTimeFromStart()

#endif // _DELTA_TIME_H
