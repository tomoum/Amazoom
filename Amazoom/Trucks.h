#ifndef TRUCKS_H
#define TRUCKS_H

#include "Storage.h"
#include "product.h"
#include "Order.h"

#define TRUCK_MAX_CAPACITY 2000.00 //kg
#define TRUCK_THRESHOLD 

class Truck {
private:
	std::vector<Order> orders_;
	std::vector<Product> stock_;
	double payload_weight;
	TruckType type_;

public:
	Truck(TruckType type_in) :type_(type_in) {}
	Truck() :type_(Unknown) {}

	TruckType getType(){
		return type_;
	}

	void setType(TruckType type_in) {
		type_ = type_in;
	}
	
	bool addOrder(Order& order) {
		if (type_ != Delivery)
			return false;

		if ((order.weight + payload_weight) < TRUCK_MAX_CAPACITY) {
			payload_weight += order.weight;
			orders_.push_back(order);
			return true;
		}

		return false;
	}

};


enum TruckType {
	Delivery,
	Stock,
	Unknown
};


#endif
