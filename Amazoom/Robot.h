/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Robots check the queue made by the warehouse - collect products then place them on trucks
*/

#ifndef ROBOT_H
#define ROBOT_H

#include <cpen333/thread/thread_object.h>
#include <iostream>
#include <thread>
#include "OrderQueue.h"
#include "safe_printf.h"
#include "product.h"
#include "Storage.h"
#include "Order.h"
#include "LoadingBay.h"

#define ROBOT_MAX_CAPACITY 200.00 //in kg

class Robot : public cpen333::thread::thread_object {
private:
	RobotOrderQueue& queue_;

	Storage& storage_;

	std::map<int, int> Inventory_ptr_; //maps product id to inventory
	std::vector<Inventory> Inventories_;

	std::map<int, int>& Order_ptr_;
	std::vector<Order>& Orders_;
	std::mutex& order_mutex_;

	std::vector<Product> Onboard_;
	std::vector<Product> Collection_;

	double payload_; // weight of order being carried
	const int id_;

	/*LoadingBay& Delivery_bay;*/

public:
	Robot(RobotOrderQueue& queue, int id, Storage& storage, std::map<int, int>& Order_ptr, 
		std::vector<Order>& Orders, std::mutex& order_mutex,
		 std::map<int, int>& Inventory_ptr, std::vector<Inventory>& Inventories)
		: queue_(queue), id_(id), storage_(storage),
		Order_ptr_(Order_ptr), Orders_(Orders),
		Inventories_(Inventories), Inventory_ptr_(Inventory_ptr),order_mutex_(order_mutex){}
	/*Robot(RobotOrderQueue& queue, int id, Storage& storage, std::map<int, int>& Order_ptr,
		std::vector<Order>& Orders, std::mutex& order_mutex,
		LoadingBay& Deliver_bay, std::map<int, int>& Inventory_ptr, std::vector<Inventory>& Inventories)
		:Delivery_bay(Deliver_bay), queue_(queue), id_(id), storage_(storage),
		Order_ptr_(Order_ptr), Orders_(Orders),
		Inventories_(Inventories), Inventory_ptr_(Inventory_ptr), order_mutex_(order_mutex) {}*/

	int main() {

		safe_printf("Robot %d started\n", id_);

		Order order = queue_.get();

		while (1) {

			if (order.task_ == RobotTask::QUIT) {
				break;
			}
			else if (order.task_ == RobotTask::COLLECT_AND_LOAD) {
				Collection_ = order.products_;
				CollectLoad(order);
			}
			else if (order.task_ == RobotTask::UNLOAD) {
				UnloadTruck(order);
			}

			//get next order
			order = queue_.get();
			
		}

		safe_printf("Robot %d Quiting.\n", id_);

		return 0;
	}

	void UnloadTruck(Order& order) {
		safe_printf("\nRobot %d going to loading bay to pick up items \n", id_);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		//XXXXXXXXXXXXXXXXXX
		//TO DO :
		// tell the truck your unloading items
		//XXXXXXXXXXXXXXXXXXXXXXX
		safe_printf("\nRobot %d aquired items. \n", id_, order.ID_);

		for (auto& product : Collection_) {
			safe_printf("\nRobot %d going to location: \n %s", id_, product.location_.toString().c_str());
			std::this_thread::sleep_for(std::chrono::seconds(2));
			safe_printf("\nRobot %d placing %s on the shelf. \n ", id_, product.toString().c_str());
			getInventory(product.ID_).store(product.location_);
		}

	}

	void CollectLoad(Order& order) {
		safe_printf("Robot %d collecting order %d \n", id_, order.ID_);
		safe_printf("%s", order.toString().c_str());
		int count = 0;

		// Go Collect items in order
		for (auto& product : Collection_) {
			safe_printf("\nRobot %d going to location: \n %s", id_, product.location_.toString().c_str());
			std::this_thread::sleep_for(std::chrono::seconds(2));

			if (product.weight_ > ROBOT_MAX_CAPACITY) {
				safe_printf("\nRobot %d: Are you Kidding this product is too heavy to carry! Requesting Tin-Man! ", id_, product.toString().c_str());
				safe_printf("BIG T IS HERE TO HELP YOU SON!\nX   X\nX X X\nXXXXX\n  X  \n  X  \n  X  \n  X  \nXXXXX\nX   X\nX   X\nX   X\n");
				Onboard_.push_back(product);
				storage_.FreeShelf(product.location_);
			}
			else{
				safe_printf("\nRobot %d picking up: %s \n ", id_, product.toString().c_str());
				payload_ += product.weight_;
				Onboard_.push_back(product);
				storage_.FreeShelf(product.location_);
				count++;
			}
			

		}

		safe_printf("Robot %d Placed Order on Truck and updated status \n", id_);

		/*safe_printf("Robot %d Going to delivery bay %d \n", id_, Delivery_bay.baynum);
		while (!Delivery_bay.LoadOrder(payload_)){
			safe_printf("Robot %d Could not load order waiting for next truck. \n", id_);
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}*/

		UpdateOrderStatus(order.ID_);
	}

	void UpdateOrderStatus(int order_id) {
		std::lock_guard<std::mutex> mylock(order_mutex_);
		Orders_[Order_ptr_[order_id]].status = OrderStatus::OUT_FOR_DELIVERY;
	}
	
	Inventory& getInventory(int product_id) {
		return Inventories_[Inventory_ptr_[product_id]];
	}
};

#endif