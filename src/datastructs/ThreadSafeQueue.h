#pragma once
#ifndef PICO
#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue
{
	public:
	void push(const T& value);
	T pop();
	bool empty() const;

	private:
	std::queue<T> _queue;
	mutable std::mutex _mutex;
	std::condition_variable _condition;
};
#endif