/**
 *@file
 *
 * This file contains the definition of a Song in our database
 *
 */

#ifndef SERVEROBJECTS_H
#define SERVEROBJECTS_H

#include <string>
#include <iostream>

#define MAX_NUM_PRODUCTS 5

 //Represents product id and quantity
struct ServerProduct {
	 int product_id;
	 int price_;
	 std::string name_;
	 int quantity;


	std::string toString() const {
		std::string out = std::to_string(product_id);
		out.append(" - ");
		out.append(std::to_string(quantity_));
		return out;
	}

	// overloaded stream operator for printing
	//    std::cout << product
	friend std::ostream& operator<<(std::ostream& os, const ServerProduct& s) {
		os << s.toString();
		return os;
	}


};

// This "song" class is Immutable: once constructed it cannot be changed.
class ServerOrder {
 public:
	 std::vector<ServerProduct>  products_;
	 int ID_;

	 ServerOrder() {}

	 ServerOrder& operator=(ServerOrder other)
	 {
		 ID_ = other.ID_;
		 products_ = other.products_;
		 return *this;
	 }
	 //Order(Product prod, int quantity): {}

	 std::string toString() {

		 std::string out = "\n*********Order ID: ";
		 out.append(std::to_string(ID_) + "**********\n");
		 out.append("\nProducts:");
		 for (auto product : products_) {
			 out.append("\n" + product.name_);
		 }
		 out.append("\n************************************\n");
		 return out;
	 }

	 // overloaded stream operator for printing
	 //    std::cout << product
	 friend std::ostream& operator<<(std::ostream& os, ServerOrder& s) {
		 os << s.toString();
		 return os;
	 }
  
  // equal-to operator for comparisons, both artist and title must match
  friend bool operator==(const ServerOrder& a, const ServerOrder& b) {
    return (a.products_ == b.products_) && (a.ID_ == b.ID_);
  }

  // not-equal-to operator for comparisons
  friend bool operator!=(const ServerOrder& a, const ServerOrder& b) {
    return !(a == b);
  }

};

class ServerReport {
	bool verified;
	int product_ID;
	int quantity;
};

#endif //LAB4_MUSIC_LIBRARY_SONG_H
