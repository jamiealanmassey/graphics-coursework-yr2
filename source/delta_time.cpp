#include "delta_time.h"

DeltaTime::DeltaTime()
{
	m_delta = 0.0f;
	m_deltaCache.resize(DELTA_CACHE_SIZE, 0.0f);
}

DeltaTime::~DeltaTime()
{
}

void DeltaTime::start()
{
	m_timeTick = m_clock.now();
	m_timeStart = m_clock.now();
}

void DeltaTime::tick()
{
	float delta = std::chrono::duration_cast<
				  std::chrono::duration<float, std::milli>>(m_clock.now() - m_timeTick).count();

	m_delta -= m_deltaCache[0] / (float)m_deltaCache.size();
	m_delta += delta / (float)m_deltaCache.size();

	std::copy(m_deltaCache.begin() + 1, m_deltaCache.end(), m_deltaCache.begin());
	m_deltaCache[m_deltaCache.size() - 1] = delta;
	m_timeTick = m_clock.now();
}

const float DeltaTime::getDelta() const
{
	return m_delta;
}

const float DeltaTime::getTimeFromStart() const
{
	return std::chrono::duration_cast<
		   std::chrono::duration<float, std::milli>>(m_clock.now() - m_timeStart).count();
}

DeltaTime& DeltaTime::instance()
{
	static DeltaTime instance;
	return instance;
}
