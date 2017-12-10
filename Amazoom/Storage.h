/*
*Date: 12/1/2017
*Author: Muhab Tomoum - 52141132
*Description: Keeps track of the storage units status EMPTY/FULL in the warehouse
*/

#ifndef STORAGE_H
#define STORAGE_H

#include <chrono>
#include <random>
#include <cmath> 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <fstream>
#include <vector>
#include <mutex>
#include <iostream>

#define WALL_CHAR 'X'
#define EMPTY_CHAR ' '
#define LEFT_STORAGE_CHAR 'L'
#define RIGHT_STORAGE_CHAR 'R'
#define BAY_1_CHAR '1'
#define BAY_2_CHAR '2'

#define MAX_FLOOR_SIZE 34
#define NUM_SHELVES 6
#define FLOOR_FILE_NAME "Warehouse1.txt"

struct Location
{
	int row;
	int col;

	virtual std::string toString() const {
		std::string out = "Row: ";
		out.append(std::to_string(row));
		out.append(" Col: ");
		out.append(std::to_string(col));
		return out;
	}

	// overloaded stream operator for printing
	friend std::ostream& operator<<(std::ostream& os, const Location& s) {
		os << s.toString();
		return os;
	}
};

struct ShelfLocation : Location
{
	int shelf;

	//Intializes the location to be invalid. 
	ShelfLocation() {
		row = -1;
		col = -1;
		shelf = -1;
	}

	ShelfLocation(const ShelfLocation &other) {
		row = other.row;
		col = other.col;
		shelf = other.shelf;
		
	}

	ShelfLocation& operator=(ShelfLocation other)
	{
		row = other.row;
		col = other.col;
		shelf = other.shelf;
		return *this;
	}
	bool isValid() {
		if (row != -1 && col != -1 && shelf != -1) {
			return true;
		}
		return false;
	}

	std::string toString() const {
		std::string out = "Row: ";
		out.append(std::to_string(row));
		out.append(" Col: ");
		out.append(std::to_string(col));
		out.append(" Shelf Unit: ");
		out.append(std::to_string(shelf));
		return out;
	}

	friend bool operator==(const ShelfLocation& a, const ShelfLocation& b) {
		return (a.row == b.row) && (a.col == b.col) && (a.shelf == b.shelf);
	}
};

class Storage {
private:
	std::mutex mutex_;
	char floor[MAX_FLOOR_SIZE][MAX_FLOOR_SIZE]; // floor storage [r][c]
	std::vector<ShelfLocation> FreeShelfs_;
	std::vector<ShelfLocation> OccupiedShelfs_;
	std::vector<Location> bay1;
	std::vector<Location> bay2;
	size_t max_row;
	size_t max_col;
public:
	Storage() {
		LoadFloor();
		std::cout << "Loaded floormap of warehouse: " << std::endl;
		printFloor();

		InitializeShelfLocations();
	}

	//Returns a random free shelf location or if none available returns 
	//a loc with row==col==0
	ShelfLocation GetFreeShelf() {
		ShelfLocation location;

		if (!FreeShelfs_.empty()) {
			std::lock_guard<std::mutex> mylock(mutex_);
			/*std::default_random_engine rnd(
				std::chrono::system_clock::now().time_since_epoch().count());
			std::uniform_real_distribution<int> dist(0, FreeShelfs_.size());*/
			srand(time(NULL));
			int rand_num = rand() % FreeShelfs_.size();

			location = FreeShelfs_[rand_num];
			OccupiedShelfs_.push_back(location);
			FreeShelfs_.erase(FreeShelfs_.begin() + rand_num);
			return location;
		}

		
		return location;
	}

	// tries to free the given location in return true if successful false otherwise
	bool FreeShelf(ShelfLocation location) {
		if (!location.isValid()) {
			return false;
		}

		for (std::vector<ShelfLocation>::iterator it = OccupiedShelfs_.begin(); it != OccupiedShelfs_.end(); ++it) {
			if( *it == location ){
				std::lock_guard<std::mutex> mylock(mutex_);
				FreeShelfs_.push_back(*it);
				OccupiedShelfs_.erase(it);
				//std::cout << "Freed Shelf at:" << it->toString() << std::endl;
				return true;
			}
		}

		return false;
	}

	void printFloor() {
		for (size_t row = 0; row < max_row; row++) {
			for (size_t col = 0; col < max_col; col++) {
				std::cout << floor[row][col];
			}
			std::cout << std::endl;
		}
	}

private:
	
	//Reads a floorplan from a filename and stores it in floor[][]
	void LoadFloor() {
		std::ifstream fin(FLOOR_FILE_NAME);
		std::string line;

		if (fin.is_open()) {
			//std::cout << "File is open" << std::endl;
			int row = 0;  // zeroeth row
			
			while (std::getline(fin, line)) {
				//std::cout << line << std::endl;
				max_col = line.length();
				for (size_t col = 0; col<line.length(); col++) {
					floor[row][col] = line[col];
				}
				row++;
			}
			max_row = row;
			fin.close();
		}

	}

	//Reads the floorplan and retrieves all shelf loactions 
	void InitializeShelfLocations() {
		char cur_char;
		ShelfLocation cur_loc;

		for (size_t row = 0; row < max_row; row++) {
			for (size_t col = 0; col < max_col; col++) {
				cur_char = floor[row][col];
				
				if (cur_char == LEFT_STORAGE_CHAR) {
					cur_loc.col = col - 1;
					cur_loc.row = row;
					PopulateShelfs(cur_loc);
					//std::cout << "Current Char: " << cur_char << std::endl;
					//std::cout << "Recognized as =  "<< LEFT_STORAGE_CHAR << std::endl;
					
				}
				else if (cur_char == RIGHT_STORAGE_CHAR)
				{
					//std::cout << "Current Char: " << cur_char << std::endl;
					//std::cout << "Recognized as =  " << RIGHT_STORAGE_CHAR << std::endl;
					cur_loc.col = col + 1;
					cur_loc.row = row;
					PopulateShelfs(cur_loc);
				}
				else if (cur_char == BAY_1_CHAR) {
					//std::cout << "Current Char: " << cur_char << std::endl;
					//std::cout << "Recognized as =  " << BAY_1_CHAR << std::endl;
					cur_loc.col = col;
					cur_loc.row = row;
					PopulateShelfs(cur_loc);
				}
				else if (cur_char == BAY_2_CHAR) {
					//std::cout << "Current Char: " << cur_char << std::endl;
					//std::cout << "Recognized as =  " << BAY_2_CHAR  << std::endl;
					cur_loc.col = col;
					cur_loc.row = row;
					PopulateShelfs(cur_loc);
				}
			}
		}
	}

	void PopulateShelfs(ShelfLocation loc) {
		for (int i = 0; i < NUM_SHELVES; i++) {
			loc.shelf = i;
			FreeShelfs_.push_back(loc);
		}
	}
};

#endif
