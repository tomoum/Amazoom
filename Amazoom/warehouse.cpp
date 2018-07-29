/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Automated warehouse control system
*/

#include "warehouse.h"
#include "Inventory.h"
#include "Robot.h"

int main() {

	Warehouse Amazoom;

	Amazoom.CreateRobotArmy(4);
	//create fake orders
	Order ord;
	OrderReport report;
	for (size_t i = 0; i < 5; i++)
	{
		ord = Amazoom.GenerateOrder();
		report = Amazoom.AddOrder(ord);

		if (report.verified) {
			std::cout << "Succesfully verified and reserved order!! " << ord.toString() << std::endl;
		}
		else {
			std::cout << "Failed to verify order! Product ID: " << report.product << "Quantity Available: " << std::to_string(report.quantity) << std::endl;
		}
	}
	
	Amazoom.KillRobots();

	std::cin.get();
	return 0;
}
