
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <thread>
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


#define NUM_PRODUCTS 5
#define PRODUCT_DESCRIPTION_FILE "Products.txt"

class Warehouse {
private:
	std::map<int, Inventory*> Inventory_ptr;
	Inventory Inventories_[NUM_PRODUCTS];
	Storage StorageUnits;
	Product Products_[NUM_PRODUCTS];

public:
	Warehouse(){
		InitProductInfo();
		InitInventories();
	}

	Storage* getStorage() {
		return &StorageUnits;
	}

	void InitInventories() {
		for (size_t i = 0; i < NUM_PRODUCTS; i++)
		{
			std::cout << "Adding " << NUM_PRODUCTS_INIT<< " products to Inventory: " 
				<< Inventories_[i].getProduct().toString()
				<< std::endl;
			
			for (int j = 0; j < NUM_PRODUCTS_INIT; j++) {
				Inventories_[i].store(StorageUnits.GetFreeShelf());
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
			std::cout << "Loaded Products: " << line << std::endl;

			while (std::getline(fin, line) && count < NUM_PRODUCTS) {
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
						Products_[count] = Product(name, id, weight, price); // add the product 
						Inventories_[count].setProduct(Products_[count]); // assign the inventory the product
						Inventory_ptr[id] = &Inventories_[count]; //add ID,Inventory pair to map
						std::cout << "Product: " << Products_[count] << std::endl;
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
		
};

#endif 

