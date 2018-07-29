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

	//Testing Order verification and reservation
	//------------------------------------------------------------
//	Warehouse ware;
//	//create fake order to test with 
//	Order ord;
//	ord.ID_ = 456334;
//
//	Product p = ware.getProduct(5215667);
//	p.quantity_ = 4;
//	ord.products_.push_back(p);
//
//	p = ware.getProduct(7886538);
//	p.quantity_ = 3;
//	ord.products_.push_back(p);
//
//	p = ware.getProduct(92873884);
//	p.quantity_ = 6;
//	ord.products_.push_back(p);
//
//	p = ware.getProduct(73738462);
//	p.quantity_ = 5;
//	ord.products_.push_back(p);
//
//	/*std::cout << "\nSending order for verification: " << std::endl;
//	std::cout << ord.toString() << std::endl;
//*/
//	//Inventory inv = ware.getInventory(73738462);
//	//std::cout << "Inventory " << std::to_string(inv.getID()) << " contains:  " << std::to_string(inv.numStored())
//	//	<< std::endl;
//
//	if (ware.VerifyOrder(ord)) {
//		ware.AddOrder(ord);
//		std::cout << ware.getOrder(456334).toString() << std::endl;
//		//std::cout << std::to_string(ware.getInventory(73738462).numReserved())<< std::endl; // checking the memorys updated
//		//std::cout << std::to_string(ware.getInventory(73738462).numStored()) << std::endl;
//	}
//-----------------------------------------------------------------------------------

	// Testing Robot queue
	//-----------------------------------------------------------------------------------


	Warehouse ware;
	//create fake order to test with 
	Order ord;
	ord.ID_ = 456334;

	Product p = ware.getProduct(5215667);
	p.quantity_ = 1;
	ord.products_.push_back(p);

	p = ware.getProduct(7886538);
	p.quantity_ = 1;
	ord.products_.push_back(p);

	p = ware.getProduct(92873884);
	p.quantity_ = 1;
	ord.products_.push_back(p);

	p = ware.getProduct(73738462);
	p.quantity_ = 0;
	ord.products_.push_back(p);


	
		ware.CreateRobotArmy(2);

		//
		//ware.CreateStockOrders();
/*
		OrderReport report = ware.AddOrder(ord);
		if(report.verified)
			std::cout << "Succesfully verified and reserved order!! " << ord.toString() << std::endl;
		*/
		/*std::this_thread::sleep_for(std::chrono::seconds(1));
		while (ware.GetDeliveryBay()->Truck_available) {}

		std::this_thread::sleep_for(std::chrono::seconds(2));
		ware.KillAllThreads();*/

		/*while (ware.getOrder(ord.ID_).status != OrderStatus::OUT_FOR_DELIVERY) {}
		std::cout << "Yes its out for delivery!!" << std::endl;
*/
		//ware.KillRobots();
	



	std::cin.get();
	return 0;
}


