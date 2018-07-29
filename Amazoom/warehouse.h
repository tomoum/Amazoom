
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
#include "OrderQueue.h"
#include "Storage.h"
#include "Trucks.h"
#include <cpen333/thread/semaphore.h>
#include "LoadingBay.h"
#include "ManagersUI.h"

#define NUM_PRODUCTS_INIT 20
#define ID_FILE_IDENTIFIER "ID"
#define NAME_FILE_IDENTIFIER "name"
#define PRICE_FILE_IDENTIFIER "price"
#define WEIGHT_FILE_IDENTIFIER "weight"
#define PRODUCT_DESCRIPTION_FILE "Products.txt"


class Warehouse {
private:
	Storage StorageUnits_;
	bool quit_all;
	/*TruckHandler* truck_handler;

	LoadingBay Delivery_bay;*/
	//ManagerUI* ui;

	RobotOrderQueue order_queue;
	std::vector<Robot*> robots_;

	//std::map<int, bool> low_stock; // if true then the product is low stock
	std::map<int, int> Inventory_ptr; //maps product id to inventory
	std::vector<Inventory> Inventories_;

	std::map<int, int> Product_ptr;
	std::vector<Product> Products_;

	std::mutex order_mutex;
	std::map<int, int> Order_ptr; // maps the order to an order id
	std::vector<Order> Orders_;

public:
	Warehouse(){
		InitWarehouse();
		InitInventories();
		quit_all = false;
		/*ui = new ManagerUI(Orders_, Orderptr, order_mutex, Products_, Product_ptr, Inventories_, Inventory_ptr, quit_all);

		ui->start();*/
		//truck_handler = new TruckHandler(Products_, quit_all, Delivery_bay);
		//loading_bay = new LoadingBay(Products_, quit_all);
		//truck_handler->start();
	}

	~Warehouse(){
		//KillRobots();
		// Free memory
		for (auto& robot : robots_) {
			delete robot;
			robot = nullptr;
		}
		/*delete ui;
		ui = nullptr;*/

	}

	void CreateRobotArmy(int nrobots) {

		for (int i = 0; i<nrobots; ++i) {
			robots_.push_back(new Robot(order_queue, i, StorageUnits_,Order_ptr,Orders_,order_mutex,Inventory_ptr,Inventories_) );
		}

		//creating robots
		for (auto& robot : robots_) {
			robot->start();
		}
		
	}

	std::vector<Product> getProducts() {
		return Products_;
	}

	//Sets a shared bool for all threads to quit and waits for them to join.
	void KillAllThreads() {
		KillRobots();
		quit_all = true;
		
		//truck_handler->join();
		//std::cout << "Truck handler quit." << std::endl;
	}

	//Closes the robot threads by putting a poisen pill in the queue
	void KillRobots(){

		Order kill_order;
		kill_order.task_ = RobotTask::QUIT;

		for (size_t i = 0; i < robots_.size(); ++i) {
			order_queue.add(kill_order);
		}
		

		//waiting for robots to quit
		for (auto& robot : robots_) {
			robot->join();
		}

		std::cout << "All Robots dead." << std::endl;

	}

	//Generates a vector of random number of each product
	std::vector<Product> GenerateStock() {
		srand(time(NULL));
		int rand_num = rand() % 1;
		std::vector<Product> out;

		for (auto product : Products_) {
			rand_num = rand() % RAND_STOCK;

			for (int i = 0; i < rand_num; i++)
			{
				out.push_back(product);
			}
		}

		return out;
	}

	Order GenerateOrder() {
		Order order;
		srand(time(NULL));
		order.ID_ = rand() % 500;
		int rand_num;
		std::vector<Product> out;

		for (auto product : Products_) {
			rand_num = rand() % RAND_STOCK;
			product.quantity_ = rand_num;
			out.push_back(product);
		}

		order.products_ = out;
		return order;
	}

	void CreateStockOrders() {
		Order order;
		order.task_ = RobotTask::UNLOAD;
		order.ID_ = 1;
		std::vector<Product> stocked_products = GenerateStock();
		
		double weight = 0;
		int num_orders = 1;

		for (auto product : stocked_products) {
			product.location_ = StorageUnits_.GetFreeShelf();
			if (weight + product.weight_ < ROBOT_MAX_CAPACITY) {
				order.products_.push_back(product);
			}
			else {
				
				order_queue.add(order);

				order.products_.clear();
				order.task_ = RobotTask::UNLOAD;
				order.ID_ = 1; // used as the bay number
				order.products_.push_back(product);


				weight = product.weight_;
				num_orders++;
			}
			
		}

		std::cout << "Added " << std::to_string(num_orders)<< " orders for unloading." << std::endl;

	}

	//Verifies an order by checking inventories if they can reserve all items
	//
	//@param order must have order id, products, quantity intialized
	//@return true if successful false otherwise
	bool VerifyOrder(Order &order, OrderReport& report) {
		std::vector<Product> reserved;
		int numReserved;
		int numUnRes;

		//std::cout << "Verifying Order: " << order.toString() << std::endl;

			for (auto prod : order.products_) {
			std::cout << "Product: " << prod.ID_ << std::endl;
			std::cout << "Quantity: " << prod.quantity_<< std::endl;
			//Inventory* Inv = getInventory(prod->ID_);
			numReserved = getInventory(prod.ID_).Reserve(prod.quantity_);

			//if u couldnt reserve the required quantity of a certain product free them all
			if (numReserved != prod.quantity_) {
				std::cout << "Could not Reserve: " << prod.toString() << std::endl;
				report.product = prod;
				report.quantity = numReserved;
				report.verified = false;
				
				// free all the reserved items if any
				for (std::vector<Product>::iterator res_it = reserved.begin(); res_it != reserved.end(); ++res_it) {
					numUnRes = getInventory(res_it->ID_).UnReserve(res_it->quantity_);
					if (numUnRes != res_it->quantity_) {
						std::cout << "Could not Unreserve: " << *res_it << std::endl;
					}
					std::cout << "Removed Reservation of: " << *res_it << std::endl;
				}
				return false;
			}
			
			reserved.push_back(Product(prod));
			std::cout << "Reserved: " << prod.toString() << " for order ID: "<< order.ID_<< std::endl;
		}
		std::cout << std::endl;
		order.status = OrderStatus::READY_FOR_COLLECTION;

		{
			std::lock_guard<std::mutex> mylock(order_mutex);
			Orders_.push_back(order);
			Order_ptr[order.ID_] = Orders_.size() - 1; // index starts at 0
		}
		

		return true;
	}

	//Poppulates the products in order with shelf locations then adds it to collection queue
	// Updates the order status
	//pre conditions: must verify order before attempting to add it;
	OrderReport AddOrder(Order order_in){
		OrderReport report;

		if (!VerifyOrder(order_in, report)) {
			return report;
		}
	
		order_in.task_ = RobotTask::COLLECT_AND_LOAD;
		std::vector<Product> robot_collection;
		ShelfLocation loc;

		for (auto product : order_in.products_) {
			Product p = product;

			for (int i = 0; i < product.quantity_; i++)
			{
				p.location_ = getInventory(p.ID_).aquire();
				robot_collection.push_back(p);
			}
			
			
		}

		{
			std::lock_guard<std::mutex> mylock(order_mutex);
			Orders_.push_back(order_in);
			Order_ptr[order_in.ID_] = Orders_.size() - 1; // index starts at 0
		}

		order_in.products_ = robot_collection;
		order_queue.add(order_in);
		return report;
	}

	Order getOrder(int order_id) {
		std::lock_guard<std::mutex> mylock(order_mutex);
		return Orders_[Order_ptr[order_id]];
	}

	//adds some stocks to beging with
	void InitInventories() {

		for (std::vector<Inventory>::iterator Inv = Inventories_.begin(); Inv != Inventories_.end(); ++Inv) {
			std::cout << "Adding " << NUM_PRODUCTS_INIT << " products to Inventory: "
				<< Inv->toString()
				 << std::endl;

			for (int j = 0; j < NUM_PRODUCTS_INIT; j++) {
				ShelfLocation s = StorageUnits_.GetFreeShelf();
				if (!s.isValid())
					break;

				Inv->store(s);
			}
		}

		
	}

	// Read Product IDs from a file and create a new Inventory for each one
	// and map it accodiring to the ID for easy access
	void InitWarehouse(){
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
						Inventory_ptr[id] = count;
						//low_stock[id] = false;

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

	Inventory& getInventory(int product_id) {
		return Inventories_[Inventory_ptr[product_id]];
	}
		
	Product getProduct(int product_id) {
		return Products_[Product_ptr[product_id]];
	}

};

//if bool is true order is succsefully reserved
//otherwise the product contained can only have quantity reserved which is less than requested

#endif 

