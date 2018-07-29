#ifndef TRUCKQUEUE_H
#define TRUCKQUEUE_H

#include <cpen333/thread/semaphore.h>
#include "Trucks.h"
#include <mutex>

#define CIRCULAR_BUFF_SIZE 2

/**
* Queue implementation using a circular buffer
* (i.e. a fixed-size queue)
*/

class TruckQueue {
	Truck buff_[CIRCULAR_BUFF_SIZE];
	cpen333::thread::semaphore producer_;
	cpen333::thread::semaphore consumer_;
	std::mutex pmutex_;
	std::mutex cmutex_;
	size_t pidx_;
	size_t cidx_;


public:
	/**
	* Creates a queue with provided circular buffer size
	* @param buffsize size of circular buffer
	*/
	TruckQueue() :
		buff_(),
		producer_(CIRCULAR_BUFF_SIZE), consumer_(0),
		pmutex_(), cmutex_(), pidx_(0), cidx_(0) {}

	void add( Truck& truck) {

		int pidx;
		producer_.wait();
		{
			std::lock_guard<std::mutex> mylock(pmutex_);
			pidx = pidx_;
			// update producer index
			pidx_ = (pidx_ + 1) % CIRCULAR_BUFF_SIZE;
			buff_[pidx] = truck;
		}
		consumer_.notify();

	}

	Truck get() {

		int cidx;
		Truck out;
		consumer_.wait();
		{
			std::lock_guard<std::mutex> mylock(cmutex_);
			cidx = cidx_;
			// update consumer index
			cidx_ = (cidx_ + 1) % CIRCULAR_BUFF_SIZE;
			out = buff_[cidx];
		}
		producer_.notify();

		return out;
	}

};

#endif