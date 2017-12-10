/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Provides all information about a particular product having the same ID as the product ID
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"
#include "Storage.h"
#include <mutex>

class Inventory {
private:
	std::mutex mutex; 
	std::vector<ShelfLocation> stored;
	std::vector<ShelfLocation> reserved;
    int ID_;

public:
	Inventory(int id): ID_(id) {
	}

	Inventory(const Inventory &p2) { ID_ = p2.ID_; }

	void store(ShelfLocation location) {
		std::lock_guard<std::mutex> mylock(mutex);
		stored.push_back(location);
	}

	void store(std::vector<ShelfLocation>& locations) {
		std::lock_guard<std::mutex> mylock(mutex);
		stored.insert(
			stored.end(),
			std::make_move_iterator(locations.begin()),
			std::make_move_iterator(locations.end())
		);
	}

	/**
	* Tries to reserve a quantity from the stored vector
	* if it cant reserve them all it wont reserve any
	*
	* @param quantity number of products to be reserved
	* @return number of items that could be reserved if this number matches quantity input then
	*         all items have been reserved other wise none of them are reserved.
	*/
	int Reserve(size_t quantity) {
		std::lock_guard<std::mutex> mylock(mutex);

		if (stored.size() < quantity) {
			return stored.size();
		}

		for (size_t i = 0; i < quantity; i++)
		{
			reserved.push_back(stored.back());
			stored.pop_back();
		}

		return quantity;
	}

	/**
	* Tries to unreserve a quantity from the reserved vector
	* if it cant unreserve them all it wont unreserve any
	*
	* @param quantity number of products to be reserved
	* @return number of items that could be unreserved if this number matches quantity input then
	*         all items have been unreserved other wise none of them are.
	*/
	int UnReserve(size_t quantity) {
		std::lock_guard<std::mutex> mylock(mutex);

		if (reserved.size() < quantity) {
			return reserved.size();
		}

		for (size_t i = 0; i < quantity; i++)
		{
			stored.push_back(reserved.back());
			reserved.pop_back();
		}

		return quantity;
	}

	ShelfLocation aquire() {
		ShelfLocation out;
		if (!reserved.empty()) {
			std::lock_guard<std::mutex> mylock(mutex);
			out = reserved.back();
			reserved.pop_back();
		}
		return out;
	}

	int numReserved() {
		std::lock_guard<std::mutex> mylock(mutex);
		return reserved.size();
	}

	int numStored() {
		std::lock_guard<std::mutex> mylock(mutex);
		return stored.size();
	}

	int getID(){
		return ID_;
	}

	std::string toString() const {
		std::string out = std::to_string(ID_);
		return out;
	}

	// overloaded stream operator for printing
	//    std::cout << product
	friend std::ostream& operator<<(std::ostream& os, const Inventory& s) {
		os << s.toString();
		return os;
	}

};

#endif
