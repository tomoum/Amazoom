/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Trucks either restock warehouse or collect outgoing orders for delivery.
*/

#ifndef TRUCKS_H
#define TRUCKS_H

#include "Storage.h"
#include "product.h"
#include "Order.h"
#include "safe_printf.h"
#include <cpen333/thread/thread_object.h>
#include "LoadingBay.h"

#define TRUCK_MAX_CAPACITY 2000.00 //kg
#define TRUCK_THRESHOLD 16.00
#define CIRCULAR_BUFF_SIZE 2

//
//class DeliveryTruck : public cpen333::thread::thread_object {
//private:
//	double& payload_;
//	bool& quit_;
//	LoadingBay& Delivery_bay;
//	const int id_;
//
//public:
//	DeliveryTruck(bool& quit, double& payload_weight, const int id, LoadingBay& Deliver_bay)
//		: quit_(quit), payload_(payload_weight), id_(id), Delivery_bay(Deliver_bay) {}
//	//LoadingBay& Deliver_bay
//	int main() {
//		safe_printf("Delivery Truck %d Arrived!\n", id_);
//		while (payload_ < TRUCK_THRESHOLD) {
//			if (quit_) {
//				return 0;
//			}
//
//		}
//		safe_printf("Delivery Truck %d Hit capacity and Departing!\n", id_);
//		Delivery_bay.TruckLeaving(id_);
//
//		return 0;
//	}
//};


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

	void add(Truck& truck) {

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
