#include "Threading.h"


void Threading::run()
{
	while (true) {
		Thread thread;
#ifdef PICO
		queue_remove_blocking(&_queue, &thread);
#else
		thread = _queue.pop();
#endif

		thread.task();
        
	}
}

void Threading::enqueue_thread(Thread thread);
{
#ifdef PICO
	queue_add_blocking(&_queue, &thread);
#else
	_queue.push(thread);
#endif
}