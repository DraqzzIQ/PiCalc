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


class Threading
{
	public:
	void enqueue_thread(Thread thread);

	private:
#ifdef PICO
	queue_t _queue;
#else
	ThreadSafeQueue<Thread> _queue;
#endif
};