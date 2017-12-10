/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Provides the defintion of a product
*/

#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include "Storage.h"

struct Product {
	 std::string name_;
	 int ID_;
	 double weight_;
	 double price_;
	 ShelfLocation location_;
	 int quantity_;

	Product( std::string name,  int id,  double weight,  double price) :
		name_(name), ID_(id), weight_(weight), price_(price) {}

	Product() {}

	Product(const Product &p2) { 
		ID_ = p2.ID_; 
		name_ = p2.name_;
		weight_ = p2.weight_;
		price_ = p2.price_;
		quantity_ = p2.quantity_;
		location_ = p2.location_;
	}

	std::string qString() {
		return std::to_string(quantity_);
	}

	std::string toString() const {
		std::string out = name_;
		out.append(" - ");
		out.append(std::to_string(ID_));
		return out;
	}

	// overloaded stream operator for printing
	//    std::cout << product
	friend std::ostream& operator<<(std::ostream& os, const Product& s) {
		os << s.toString();
		return os;
	}

	Product& operator=(Product other)
	{
		ID_ = other.ID_;
		name_ = other.name_;
		weight_ = other.weight_;
		price_ = other.price_;
		quantity_ = other.quantity_;
		location_ = other.location_;
		return *this;
	}

};


#endif

