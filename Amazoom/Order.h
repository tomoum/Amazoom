#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include <vector>

enum OrderStatus {
	READY_FOR_COLLECTION,
	OUT_FOR_DELIVERY,
	UNKNOWN
};

class Order {
private:
	int status;
	std::vector<Product> items;
public:
	const int ID;

	Order(const int id) :ID(id) {}

	void add(Product product) {
		items.push_back(product);
	}

	std::vector<Product> retrieve() {
		return items;
	}

};



#endif