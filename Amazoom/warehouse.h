
#ifndef WAREHOUSE_H
#define WAREHOUSE_H


#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <utility> 
#include <string>
#include <map>
#include "Inventory.h"
#include "Robot.h"
#include "DynamicOrderQueue.h"
#include "Storage.h"

#define NUM_PRODUCTS_INIT 20
#define ID_FILE_IDENTIFIER "ID"
#define NAME_FILE_IDENTIFIER "name"
#define PRICE_FILE_IDENTIFIER "price"
#define WEIGHT_FILE_IDENTIFIER "weight"


#define PRODUCT_DESCRIPTION_FILE "Products.txt"

class Warehouse {
private:
	Storage StorageUnits;

	std::map<int, Inventory*> Inventory_ptr; //maps inventories to product id
	std::vector<Inventory> Inventories_;
	//Inventory Inventories_[NUM_PRODUCTS];

	std::map<int, int> Product_ptr;
	std::vector<Product> Products_;
	//Product Products_[NUM_PRODUCTS];

	std::map<int, Order*> Order_ptr; // maps the order to an order id
	std::vector<Order> Orders_;
public:
	Warehouse(){
		InitProductInfo();
		InitInventories();
	}

	//Verifies an order by checking inventories if they can reserve all items
	//
	//@param order must have order id, products, quantity intialized
	//@return true if successful false otherwise
	bool VerifyOrder(Order &order) {
		std::vector<Product> reserved;
		int numReserved;
		int numUnRes;

		std::cout << "Verifying Order: " << order<< std::endl;

		for (std::vector<Product>::iterator ord_it = order.products_.begin(); ord_it != order.products_.end(); ++ord_it) {
			numReserved = getInventory(ord_it->ID_)->Reserve(ord_it->quantity_);

			//if u couldnt reserve the required quantity of a certain product free them all
			if (numReserved != ord_it->quantity_) {
				std::cout << "Could not Reserve: " << *ord_it << std::endl;
				// free all the reserved items if any
				for (std::vector<Product>::iterator res_it = reserved.begin(); res_it != reserved.end(); ++res_it) {
					numUnRes = getInventory(res_it->ID_)->UnReserve(ord_it->quantity_);
					if (numUnRes != res_it->quantity_) {
						std::cout << "Could not Unreserve: " << *res_it << std::endl;
					}
					std::cout << "Removed Reservation of: " << *res_it << std::endl;
				}
				return false;
			}

			reserved.push_back(*ord_it);
			std::cout << "Reserved: " << *ord_it  << " for order ID: "<< order.ID_<< std::endl;
		}
		std::cout << "Succesfully verified and reserved order: " << order.ID_ << std::endl;

		return true;
	}

	
	//Poppulates the products in order with shelf locations then adds it to collection queue
	// Updates the order status
	//pre conditions: must verify order before attempting to add it;
	void AddOrder(Order order_in){
		order_in.status = OrderStatus::READY_FOR_COLLECTION;
		order_in.task_ = RobotTask::COLLECT_AND_LOAD;

		for (std::vector<Product>::iterator product = order_in.products_.begin(); product != order_in.products_.end(); ++product) {
			order_in.order_weight += product->weight_;
			ShelfLocation loc = Inventories_[product->ID_].aquire();
			
			if (loc.isValid()) {
				product->location_ = loc;
			}
			else {
				//Ideally would throw an exception but i have no time right now
				std::cout << "Error retrieving item from inventory! " << std::endl;
			}
			
		}
		Orders_.push_back(order_in);
		Order_ptr[order_in.ID_] = &Orders_.back();

	}

	Storage* getStorage() {
		return &StorageUnits;
	}

	Order* getOrder(int order_id) {
		return Order_ptr[order_id];
	}

	//adds some stocks to beging with
	void InitInventories() {

		for (std::vector<Inventory>::iterator Inv = Inventories_.begin(); Inv != Inventories_.end(); ++Inv) {
			std::cout << "Adding " << NUM_PRODUCTS_INIT << " products to Inventory: "
				<< Inv->toString()
				 << std::endl;

			for (int j = 0; j < NUM_PRODUCTS_INIT; j++) {
				ShelfLocation s = StorageUnits.GetFreeShelf();
				if (!s.isValid())
					break;

				Inv->store(s);
			}
		}

		
	}

	// Read Product IDs from a file and create a new Inventory for each one
	// and map it accodiring to the ID for easy access
	void InitProductInfo(){
		std::ifstream fin(PRODUCT_DESCRIPTION_FILE); // text file with Product descriptions
		std::string line;
		bool read = false; // dont read first line 

		if (fin.is_open()) {

			std::string name;
			int id;
			double weight;
			double price;

			int count = 0;

			std::cout << "Loading Products... " << line << std::endl;
			std::cout << std::endl;

			while (std::getline(fin, line)) {
				if (line.compare(NAME_FILE_IDENTIFIER) == 0) {
					if (std::getline(fin, line)) {
						name = line;
						//std::cout << "Name: " << line << std::endl;
					}
				}
				else if (line.compare(ID_FILE_IDENTIFIER) == 0) {
					if (std::getline(fin, line)) {
						id = std::stoi(line); // ID
						//std::cout << "ID: " << id << std::endl;
					}
				}
				else if (line.compare(WEIGHT_FILE_IDENTIFIER) == 0) {
					if (std::getline(fin, line)) {
						weight = std::stod(line);
						//std::cout << "Weight :" << weight << std::endl;
					}
				}
				else if (line.compare(PRICE_FILE_IDENTIFIER) == 0) {
					if (std::getline(fin, line)) {
						price = std::stod(line);
						//std::cout << "Price :" << weight << std::endl;

						//Add Product and link to its ID
						Products_.push_back(Product(name, id, weight, price)); // add the product 
						Product_ptr[id] = count;
						
						//Create Inventory and link to Product ID
						Inventories_.push_back(Inventory(id));
						Inventory_ptr[id] = &Inventories_.back();

						std::cout << "Product: " << Products_[count].toString() << std::endl;
						count++;
						std::cout << "Num Products: " <<count << std::endl;
					}
				}
			}
			fin.close();

		}
		else{
			std::cout << "Warehouse could not open file for reading:" << PRODUCT_DESCRIPTION_FILE << std::endl;
		}
		
	}

	Inventory* getInventory(int product_id) {
		return Inventory_ptr[product_id];
	}
		
	Product getProduct(int product_id) {
		return Products_[Product_ptr[product_id]];
	}

};

#endif 

