#include "threading/Threading.h"

Threading* Threading::_instance = nullptr;

Threading* Threading::get_instance()
{
	if (!_instance)
		_instance = new Threading();

	return _instance;
}

Threading::Threading()
{
#ifdef PICO
	queue_init(&_queue, sizeof(Thread), PICO_THREAD_QUEUE_SIZE);
#endif
}

Threading::~Threading()
{
}

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

void Threading::enqueue_thread(Thread thread)
{
#ifdef PICO
	queue_add_blocking(&_queue, &thread);
#else
	_queue.push(thread);
#endif
}