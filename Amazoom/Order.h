#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include <vector>

enum OrderStatus {
	PENDING_VERIFICATION,
	READY_FOR_COLLECTION,
	COLLECTION_COMPLETE,
	OUT_FOR_DELIVERY,
	UNKNOWN
};

enum RobotTask {
	COLLECT_AND_LOAD,
	UNLOAD,
	QUIT, // terminate thread
};

struct Order {
	const int task_;
	const int ID_;
	const int bay_;
	double weight;
	std::vector<Product> products_;
	OrderStatus status;

	Order(const int order_id, const int task, const int bay ) 
		:ID_(order_id), task_(task), bay_(bay) {}

	void add(Product product) {
		products_.push_back(product);
		weight += product.weight_;
	}
};


#endif