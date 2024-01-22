#include "ThreadSafeQueue.h"

template <typename T>
void ThreadSafeQueue<T>::push(const T& value)
{
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(value);
	lock.unlock();
	condition_.notify_one();
}

template <typename T>
T ThreadSafeQueue<T>::pop()
{
	std::unique_lock<std::mutex> lock(mutex_);
	condition_.wait(lock, [this] { return !queue_.empty(); });

	T value = queue_.front();
	queue_.pop();
	return value;
}

template <typename T>
bool ThreadSafeQueue<T>::empty() const
{
	std::unique_lock<std::mutex> lock(mutex_);
	return queue_.empty();
}
