#pragma once

#include "TestThread.h"
#include <random>
#include "Data.h"


class thread_obj
{
	bool valid{false};
	size_t id{0};
	bool completed{ false };
	void print_data(const size_t subID,const size_t id, nodeData& data);

public:

	std::vector<nodeData> data;
	std::vector<size_t> subscriptions; //List of subscribers

	//Constructors
	thread_obj(size_t ID) : id{ ID }, valid{ true } {data.clear(); subscriptions.clear(); };
	thread_obj() : valid{false} {};

	//Getters
	bool is_valid();
	bool get_completed();
	size_t getID();
	nodeData& get_found_data(size_t id);

	void completed_obj();

//Events
	//1
	void get_random_number();

	//2
	bool subscribe(thread_obj& subscription);

	//3
	void unsubscribe();
};

void run(thread_obj& ob);
thread_obj& get_random_object();
thread_obj& get_sub_object(size_t id);
thread_obj& get_id_object(size_t id);
nodeData& get_data_object(size_t id_ob, size_t id_data);
void create_object(size_t id);
void remove_subscriber(size_t id_subscriber, size_t id_subscription);
void remove_object(size_t id);
void add_sub_data(thread_obj& subscription, thread_obj& subscriber);