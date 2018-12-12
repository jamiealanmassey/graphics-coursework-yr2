#ifndef _DELTA_TIME_H
#define _DELTA_TIME_H

#define DELTA_CACHE_SIZE 40

#include <vector>
#include <chrono>

/**
 * \brief Defines DeltaTime to smooth animation over all machines
 * \details Almost a direct implementation of my own class for another project (https://github.com/jamiealanmassey/liquid-engine/blob/master/source/utilities/DeltaTime.h)
 * \version 1.1
 * \author Jamie Massey
 * \date 11.12.2018
 */
class DeltaTime
{
private:
	/** DeltaTime Constructor **/
	DeltaTime();

	/** DeltaTime Destructor **/
	~DeltaTime();

public:
	/** Starts the DeltaTime by storing m_clock.now() **/
	void start();

	/** \brief Simulates a tick of the DeltaTime (in milliseconds)
	  *
	  * Will simulate a tick of DeltaTime by taing the current time using the
	  * m_clock variable and taking away the last tick time. Then if the last X
	  * amount of frames as defined by DELTA_CACHE_SIZE have become far between
	  * a correction will be attempted by averaging the delta over the cache.
	  */
	void tick();
	
	/** \returns Gets the current delta time **/
	const float getDelta() const;

	/** \returns Time since the DeltaTime was started **/
	const float getTimeFromStart() const;

	/** \returns Singleton instance of this object **/
	static DeltaTime& instance();

protected:
	float										   m_delta;		 ///< Current delta between this and the last frame in ms
	std::vector<float>							   m_deltaCache; ///< Cache storing the last DELTA_CACHE_SIZE number of frames
	std::chrono::high_resolution_clock			   m_clock;		 ///< Clock to access time functions
	std::chrono::high_resolution_clock::time_point m_timeTick;	 ///< Timestamp of the last frame
	std::chrono::high_resolution_clock::time_point m_timeStart;	 ///< Timestamp of when DeltaTime.start() was called
};

#define DELTA_TIME_SECONDS DeltaTime::instance().getDelta() / 1000.0f
#define TOTAL_TIME_SECONDS DeltaTime::instance().getTimeFromStart() / 1000.0f

#endif // _DELTA_TIME_H
