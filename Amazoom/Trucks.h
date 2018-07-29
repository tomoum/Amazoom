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


#endif
