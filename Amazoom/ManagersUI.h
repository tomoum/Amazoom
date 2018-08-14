/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Allows the warehouse manager access to some data, query stock levels, shutdown operations etc. 
*/

#ifndef MANAGERSUI_H
#define MANAGERSUI_H
#include "warehouse.h"

class ManagerUI : public cpen333::thread::thread_object {
	std::map<int, int>& Inventory_ptr; //maps product id to inventory
	std::vector<Inventory>& Inventories_;
	std::map<int, int>& Product_ptr;
	std::vector<Product>& Products_;
	std::mutex& order_mutex;
	std::map<int, int>& Order_ptr; // maps the order to an order id
	std::vector<Order>& Orders_;
	bool& quit_;

	ManagerUI(std::vector<Order>& Orders, 
			  std::map<int, int>& Orderptr, 
			  std::mutex& ordermutex, 
			  std::vector<Product>& Products, 
			  std::map<int, int>& Productptr, 
			  std::vector<Inventory>& Inventories,
			  std::map<int, int>& Inventory_ptr, bool& quit)
			:	Orders_(Orders),
				Order_ptr(Orderptr),
				order_mutex(ordermutex),
				Products_(Products),
				Product_ptr(Productptr),
				Inventories_(Inventories),
				Inventory_ptr(Inventory_ptr),
				quit_(quit){

	
	}

	int main() {
		safe_printf("Manager UI Started.");
		PrintMainMenu();

		return 0;
	}

	void PrintMainMenu() {
		safe_printf("***********MENU***********\n");
		safe_printf("Options: \n");
		safe_printf("1- Check on Order status. \n");
		safe_printf("2- Check on Stock level of a product. \n");
		safe_printf("**************************\n");
	}


};

class LowStockAlert : public cpen333::thread::thread_object {
	std::vector<Product>& Products_;
	std::map<int, bool>& low_stock_;
	bool& quit_;

	LowStockAlert(std::map<int, bool>& low_stock, std::vector<Product>& Products, bool quit) 
		: Products_(Products), low_stock_(low_stock), quit_(quit) {}

	int main() {
		while (1) {
			if (quit_)
				return 0;

			for (auto product : Products_) {
				if (low_stock_[product.ID_]) {
					safe_printf("Product %s is low on stock.", product.toString());
					low_stock_[product.ID_] = false;
				}
			}
		}

		return 0;
	}
	
};


#endif