/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Testing Classes as i develop them making sure functions work 
*				before integration
*/

#include "warehouse.h"

int main() {

	//Verifieng Inventory map is correctly working
	//-------------------------------------------------------------------------------------------
	////Testing Inventory Initilization from txt file
	////ID 5215667
	////ID 7886538
	//Inventory* inv;
	//Warehouse warehouse;

	////inv = warehouse.Inventory_ptr[5215667];
	////std::cout << std::to_string(warehouse.Inventories_[0].getID()) << std::endl;
	//std::cout << std::to_string(inv->getID()) << std::endl; // verified map is working correctly

	//std::cout << std::to_string(warehouse.getInventory(5215667)->getID()) << std::endl;


	//-----------------------------------------------------------------------------------
	

	// Testing gettting a free shelf and deleting the correct shelf
	//-----------------------------------------------------------------------------------
	/*Warehouse ware;
	ShelfLocation shelf;
	for (size_t i = 0; i < 7; i++)
	{
		shelf = ware.getStorage()->GetFreeShelf();
		std::cout << "Acquired Shelf: " << shelf << std::endl;
		if (ware.getStorage()->FreeShelf(shelf)) {
			std::cout << "Succesfully removed: " << shelf << std::endl;
		}
	}*/
	//-----------------------------------------------------------------------------------

	//Testing the robot queue and robots collecting orders.
	//------------------------------------------------------------
	Warehouse ware;

	Order ord;

	ord.ID_ = 456334;

	Product p = ware.getProduct(5215667);
	p.quantity_ = 4;
	ord.products_.push_back(p);
	//std::cout << std::to_string(ord.products_.back().quantity_) << std::endl;

	p = ware.getProduct(7886538);
	p.quantity_ = 3;
	ord.products_.push_back(p);

	/*ord.products_.back().quantity_ = 6;
	std::cout << std::to_string(ord.products_.back().quantity_) << std::endl;*/

	p = ware.getProduct(92873884);
	p.quantity_ = 6;
	ord.products_.push_back(p);

	p = ware.getProduct(73738462);
	p.quantity_ = 5;
	ord.products_.push_back(p);

	std::cout << "Sending order for verification: " << std::endl;
	std::cout << ord.toString() << std::endl;

	//if (ware.VerifyOrder(ord)) {
	//	//ware.AddOrder(ord);
	//	std::cout << "Order Verified" << std::endl;

	//}
	//ServerItem item1(5215667, 4); // this will pass
	//ServerItem item2(7886538, 40); // this will fail


	std::cin.get();
	return 0;
}
