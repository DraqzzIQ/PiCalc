#pragma once
#ifdef PICO
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"
#else
#include "datastructs/ThreadSafeQueue.h"
#include <thread>
#endif
#include "threading/Thread.h"
#include <functional>

/// <summary>
/// provides a queue on which tasks can be executed on a second core / thread
/// </summary>
class Threading
{
	public:
	/// <summary>
	/// returns instance of singleton WindowManager
	/// </summary>
	static Threading* get_instance();
	void run();
	void enqueue_thread(Thread thread);

	private:
#ifdef PICO
	queue_t _queue;
#else
	ThreadSafeQueue<Thread> _queue;
#endif
	/// <summary>
	/// private constructor to prevent instantiation
	/// </summary>
	Threading();
	/// <summary>
	/// private deconstructor to prevent deletion
	/// </summary>
	~Threading();
	/// <summary>
	/// private copy constructor and assignmnt operator to prevent copying
	/// </summary>
	/// <summary>
	/// private copy constructor and assignmnt operator to prevent copying
	/// </summary>
	Threading(const Threading&);
	Threading& operator=(const Threading&);
	/// <summary>
	/// the instance
	/// </summary>
	static Threading* _instance;
};