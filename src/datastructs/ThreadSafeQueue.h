#pragma once
#ifndef PICO
#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue
{
	public:
	void push(const T& value)
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_queue.push(value);
		lock.unlock();
		_condition.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_condition.wait(lock, [this] { return !_queue.empty(); });

		T value = _queue.front();
		_queue.pop();
		return value;
	}

	bool empty() const
	{
		std::unique_lock<std::mutex> lock(_mutex);
		return _queue.empty();
	}

	private:
	std::queue<T> _queue;
	mutable std::mutex _mutex;
	std::condition_variable _condition;
};

#endif