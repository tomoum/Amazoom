/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Provides all information about a particular product having the same ID as the product ID
*/


#pragma once
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
	const int ID;

public:
	Inventory( const int product_id) :ID(product_id) {}

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
	* Tries to reserve a quantity from the stored vector to reserved 
	* if it fails returns them back to stored
	*
	* @param quantity number of products to be reserved
	* @return number of items that could be reserved if this number matches quantity input then
	*         all items have been reserved other wise none of them are reserved.
	*/
	int reserve(int quantity) {
		std::lock_guard<std::mutex> mylock(mutex);

		if (stored.size() < quantity) {
			return false;
		}

		for (size_t i = 0; i < quantity; i++)
		{
			reserved.push_back(stored.back());
			stored.pop_back();
		}
		return true;
	}

	ShelfLocation aquire() {
		std::lock_guard<std::mutex> mylock(mutex);
		ShelfLocation out = reserved.back();
		stored.pop_back();
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
	

};

#endif
