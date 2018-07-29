#ifndef DOCKINGBAY_H
#define DOCKINGBAY_H

#include "Trucks.h"
#include <cpen333/thread/thread_object.h>
#include "Storage.h"
#include "product.h"
#include "Order.h"
#include "safe_printf.h"


#define TRUCK_MAX_CAPACITY 2000.00 //kg
#define TRUCK_THRESHOLD 16.00

#define NUM_BAYS 2
#define RAND_STOCK 3 // number of max random stock items per product
#define BAY1 0
#define BAY2 1
//
//struct LoadingBay {
//	std::mutex mutex;
//	double payload_weight;
//	bool Truck_available;
//	int baynum;
//
//	LoadingBay() {
//		payload_weight = 0;
//		Truck_available = false;
//	}
//
//	void dockTruck() {
//		std::lock_guard<std::mutex> mylock(mutex);
//		Truck_available = true;
//	}
//
//	void TruckLeaving(int id) {
//		std::lock_guard<std::mutex> mylock(mutex);
//		safe_printf("\nTruck %d Left bay %d. \n", id, baynum);
//		Truck_available = false;
//	}
//
//	bool LoadOrder(double weight) {
//		if (!Truck_available) {
//			return false;
//		}
//
//		if ((weight + payload_weight) < TRUCK_MAX_CAPACITY) {
//			std::lock_guard<std::mutex> mylock(mutex);
//			payload_weight += weight;
//			return true;
//		}
//
//		return false;
//	}
//};
//
//class TruckHandler : public cpen333::thread::thread_object {
//private:
//	DeliveryTruck* Delivery_truck;
//	LoadingBay& Delivery_bay;
//	bool& quit_;
//	int numtrucks;
//	std::vector<Product> Products_;
//
//public:
//	
//	TruckHandler(std::vector<Product> Products, bool& quit, LoadingBay& Deliver_bay):
//		Products_(Products), quit_(quit), Delivery_bay(Deliver_bay) {}
//	
//	~TruckHandler() {
//		
//			delete Delivery_truck;
//			Delivery_truck = nullptr;
//		
//
//	}
//
//	//Generates a vector of random number of each product
//	std::vector<Product> GenerateStock() {
//		srand(time(NULL));
//		int rand_num = rand() % 1;
//		std::vector<Product> out;
//
//		for (auto product : Products_) {
//			rand_num = rand() % RAND_STOCK;
//
//			for (int i = 0; i < rand_num; i++)
//			{
//				out.push_back(product);
//			}
//		}
//
//		return out;
//	}
//
//	int main() {
//		safe_printf("\Truck Handler Started. \n ");
//		numtrucks = 0;
//		Delivery_bay.baynum = 1; //intialize bay
//
//		//creat first truck
//		Delivery_truck = new DeliveryTruck(quit_, Delivery_bay.payload_weight, numtrucks, Delivery_bay); // link the bay weight to this truck
//		Delivery_truck->start();
//		//Dock it to the bay
//		Delivery_bay.dockTruck();
//		safe_printf("\Truck Handler: Docking Delivery Truck %d at bay %d \n ", numtrucks, 1);
//
//		while (1) {
//
//			if (quit_) {
//				Delivery_truck->join();
//				safe_printf("\nTruck Handler Quiting..\n ");
//				break;
//			}
//
//			if (!Delivery_bay.Truck_available) {
//				//create new random truck
//				safe_printf("\nTruck Handler Quiting..\n ");
//			}
//		}
//		// end main
//		return 0;
//	}
//
//};

#endif


