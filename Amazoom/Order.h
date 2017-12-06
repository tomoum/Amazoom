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
	IDLE
};

class Order {
private:
	const int task_;
	const int ID_;
	std::vector<Product> products_;
	int bay;
public:

	Order(const int order_id, const int task) :ID_(order_id), task_(task) {}

	void add(Product product) {
		products_.push_back(product);
	}

	std::vector<Product> retrieve() {
		return products_;
	}

};


#endif