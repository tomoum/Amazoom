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
#include <mutex>
#include <map>

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

struct locationcomp {
	bool operator() (Location& lhs, Location& rhs)
	{
		if ((lhs.col < rhs.col) && (lhs.row < rhs.row)) {
			return true;
		}
		return false;
	}
};

class Storage {
private:
	std::mutex mutex_;
	int max_row;
	int max_col;
	char floor[MAX_FLOOR_SIZE][MAX_FLOOR_SIZE]; // floor storage [c][r]
	std::vector<StorageUnit> ShelfUnits;  //location robot needs to be to access shelf - theyre smart enough to recognize orientation of shelf relative to position
	std::map<Location, StorageUnit,locationcomp> mymap;
	std::vector<Location> bay1;
	std::vector<Location> bay2;
public:
	Storage() {
		LoadFloor();
		InitializeShelfLocations();
	}

	//Tries to find a free shelf returns a ShelfLocation or 
	//if non available returns an InvalidLocation type
	Location GetFreeShelf() {
		ShelfLocation location;

		for (StorageUnit unit : ShelfUnits) {
			for (int i = 0; i < sizeof(unit.shelves); i++ ) {
				if (unit.shelves[i] == EMPTY){
					{
						std::lock_guard<std::mutex> mylock(mutex_);
						unit.shelves[i] = FULL;
					}
					location.col = unit.col;
					location.row = unit.row;
					location.shelf = i;
					return location;
				}
			}
		}

		InvalidLocation v;
		return  v;
	}

	void FreeShelf(ShelfLocation location) {

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

	/*
	* Reads the floorplan and retrieves all shelf loactions and itializes shelf locations to 0=EMPTY
	*   Note: this adds the locations nearest to the bays first
	*/
	void InitializeShelfLocations() {
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
				else if (cur_char == RIGHT_STORAGE)
				{
					cur_loc.col = col + 1;
					cur_loc.row = row;
					ShelfUnits.push_back(cur_loc);
				}
				else if (cur_char == BAY_1) {
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
};

//
//
struct Location
{
	int row;
	int col;

	 bool operator() ( Location& lhs, Location& rhs)
	{
		if ((lhs.col < rhs.col) && (lhs.row < rhs.row)) {
			return true;
		}
		return false;
	}
};

struct InvalidLocation : Location {
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
