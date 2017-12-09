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

	Warehouse ware;

	std::cin.get();
	return 0;
}
