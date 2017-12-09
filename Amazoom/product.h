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


class Product {

public:
	 std::string name_;
	 int ID_;
	 double weight_;
	 double price_;
	 ShelfLocation location_;

	Product( std::string name,  int id,  double weight,  double price) :
		name_(name), ID_(id), weight_(weight), price_(price) {}

	Product() :
		name_("No name"), ID_(000), weight_(000), price_(000) {}

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
		//std::cout << "copy assignment of Product\n";
		std::swap(name_, other.name_);
		std::swap(ID_, other.ID_);
		std::swap(weight_, other.weight_);
		std::swap(price_, other.price_);
		std::swap(location_, other.location_);
		return *this;
	}

};


#endif

