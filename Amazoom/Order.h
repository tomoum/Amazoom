/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Provides the defintion of the different orders depending on whos using it(Robot, warehouse, User)
*/

#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include <vector>

enum OrderStatus {
	READY_FOR_COLLECTION,
	ROBOT_COLLECTING_ORDER,
	COLLECTION_COMPLETE,
	OUT_FOR_DELIVERY,
	UNKNOWN
};

enum RobotTask {
	COLLECT_AND_LOAD,
	UNLOAD,
	QUIT, // terminate thread
};

struct OrderReport {
	bool verified;
	Product product;
	int quantity;

	OrderReport() {
		verified = true;
	}
};

struct Order {
	int ID_;
    int task_;
    int bay_;
	std::vector<Product> products_;
	OrderStatus status;

	Order(){}

	//Order(const Order &other) {
	//	ID_ = other.ID_;
	//	task_ = other.task_;
	//	bay_ = other.bay_;
	//	order_weight = other.order_weight;
	//	status = other.status;
	//	products_ = other.products_;
	//}

	Order& operator=(Order other)
	{
		ID_ = other.ID_;
		task_ = other.task_;
		bay_ = other.bay_;
		status = other.status;
		products_ = other.products_;
		return *this;
	}
	//Order(Product prod, int quantity): {}

	std::string toString() {

		std::string out = "\n*********Order ID: ";
		out.append(std::to_string(ID_) + "**********\n");
		out.append("\nProducts:") ;
		for (std::vector<Product>::iterator p = products_.begin(); p != products_.end(); ++p) {
			out.append("\n" + p->toString());
			out.append("\nQuantity: ");
			out.append(p->qString());
		}
		out.append("\n************************************\n");
		return out;
	}

	// overloaded stream operator for printing
	//    std::cout << product
	friend std::ostream& operator<<(std::ostream& os, Order& s) {
		os << s.toString();
		return os;
	}

};

#endif