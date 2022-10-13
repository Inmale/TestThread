#pragma once

#include "TestThread.h"
#include <random>
#include "Data.h"

class thread_obj
{
	bool completed{ false };
	size_t id{0};

	void print_data(const size_t subID,const size_t id, const nodeData& data);

public:
	std::vector<nodeData> data;

	std::vector<thread_obj> subscriptions;

	thread_obj(size_t ID) { id = ID; };

	bool get_completed();

	size_t getID();

	nodeData& get_found_data(size_t id);

//Events
	//1
	void get_random_number();

	//2
	bool subscribe();

	//3
	bool unsubscribe();

	//4
	bool new_node();
};