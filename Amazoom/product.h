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

class Product {
public:
	const std::string name;
	const int ID;
	const double weight_kg;
	const double price;

	Product(const std::string name, const int id, const double weight, const double price) :
		name(name), ID(id), weight_kg(weight), price(price) {}

	std::string toString() const {
		std::string out = name;
		out.append(" - ");
		out.append(std::to_string(ID));
		return out;
	}

	// overloaded stream operator for printing
	//    std::cout << product
	friend std::ostream& operator<<(std::ostream& os, const Product& s) {
		os << s.toString();
		return os;
	}


};


#endif

