#ifndef ROBOT_H
#define ROBOT_H


#include <cpen333/thread/thread_object.h>
#include <iostream>
#include <thread>
#include "DynamicOrderQueue.h"

#define MAX_CAPACITY 200 //in kg

class Robot {
private:
	DynamicOrderQueue& queue_;
	std::vector<Product> onBoard;

public:
	Robot(DynamicOrderQueue& queue) :queue_(queue) {}



};

#endif