#include <functional>

struct Thread {
	std::function<void()> task;
};