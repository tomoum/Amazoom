/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Keeps track of the storage units status EMPTY/FULL in the warehouse
*/

#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>
#include <vector>

#define WALL_CHAR 'X'
#define EMPTY_CHAR ' '
#define LEFT_STORAGE 'L'
#define RIGHT_STORAGE 'R'
#define BAY_1 '1'
#define BAY_2 '2'

#define MAX_FLOOR_SIZE 34
#define MAX_STORAGE_CAP_PER_UNIT 6 // 1 unit has 6 shelves - 1 shelf holds 1 product
#define FILE_NAME "Data/Warehouse1.txt"
#define EMPTY 0
#define FULL 1

class Storage {
private:
	int max_row;
	int max_col;
	char floor[MAX_FLOOR_SIZE][MAX_FLOOR_SIZE]; // floor storage [c][r]
	std::vector<StorageUnit> ShelfUnits;  //location robot needs to be to access shelf - theyre smart enough to recognize orientation of shelf relative to position
	std::vector<Location> bay1;
	std::vector<Location> bay2;
public:
	Storage() {
		LoadFloor();
		GetShelfLocations();
	}


	/*
	* Reads the floorplan and retrieves all shelf loactions and itializes shelf capacity to 0
	*   Note: floorplan
	*/
	void GetShelfLocations(){
		char cur_char;
		StorageUnit cur_loc;

		for (int row = 0; row < max_row; row++) {
			for (int col = 0; col < max_col; col++) {
				cur_char = floor[col][row];
				if (cur_char == LEFT_STORAGE) {
					cur_loc.col = col - 1;
					cur_loc.row = row;
					ShelfUnits.push_back(cur_loc);
				}
				else if(cur_char == RIGHT_STORAGE)
				{
					cur_loc.col = col + 1;
					cur_loc.row = row;
					ShelfUnits.push_back(cur_loc);
				}
				else if(cur_char == BAY_1){
					cur_loc.col = col;
					cur_loc.row = row;
					bay1.push_back(cur_loc);
				}
				else if (cur_char == BAY_2) {
					cur_loc.col = col;
					cur_loc.row = row;
					bay2.push_back(cur_loc);
				}
			}
		}
	}

private:

	/*
	* Reads a floorplan from a filename and stores it in floor[][]
	*/
	void LoadFloor() {
		std::ifstream fin(FILE_NAME);
		std::string line;

		if (fin.is_open()) {
			int row = 0;  // zeroeth row
			while (std::getline(fin, line)) {
				int cols = line.length();
				max_col = cols;
				for (size_t col = 0; col<cols; ++col) {
					floor[col][row] = line[col];
				}
				++row;
			}
			max_row = row;
			fin.close();
		}
	}
};

struct Location
{
	int row;
	int col;
};

struct ShelfLocation : Location
{
	int shelf;
};

struct StorageUnit : Location
{
	//1 shelf holds 1 product
	// True is full --- false is empty
	int shelves[MAX_STORAGE_CAP_PER_UNIT]{};
};

#endif
