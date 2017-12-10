
#ifndef DYNAMICORDERQUEUE_H
#define DYNAMICORDERQUEUE_H

#include <deque>
#include <condition_variable>
#include <mutex>
#include "Order.h"

class RobotOrderQueue {
	std::deque<Order> buff_;
	std::mutex mutex_;
	std::condition_variable cv_;

public:

	RobotOrderQueue() :
		buff_(), mutex_(), cv_() {}

	void add(const Order& order) {
		{
			std::unique_lock<decltype(mutex_)> lock{ mutex_ };
			buff_.push_back(order);
		}
		cv_.notify_one();

	}

	Order get() {
		
		std::unique_lock<decltype(mutex_)> lock{ mutex_ };
		cv_.wait(lock, [&]() { return !buff_.empty(); });
		// get first item in queue
		Order out = buff_.front();
		buff_.pop_front();
		
		cv_.notify_one();

		return out;
	}
};

#endif

