#include <functional>

struct Thread {
	std::function<void()> task;
	std::function<void()> callback;
};