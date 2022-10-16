#pragma once

#include "TestThread.h"
#include <random>
#include "Data.h"


class thread_obj
{
	bool valid;
	bool completed{ false };
	std::thread::id id{};

	void print_data(const std::thread::id subID,const std::thread::id id, nodeData& data);

public:
	std::vector<nodeData> data;
	std::vector<std::thread::id> subscriptions; //List of subscribers

	//Constructors
	thread_obj(std::thread::id ID) : id{ ID }, valid{true} {};
	thread_obj() : valid{false} {};

	//Getters
	bool is_valid();
	bool get_completed();
	std::thread::id getID();
	nodeData& get_found_data(std::thread::id id);

//Events
	//1
	void get_random_number();

	//2
	bool subscribe(thread_obj& subscription);

	//3
	void unsubscribe(thread_obj& subscription);
};

thread_obj& get_random_object();
thread_obj& get_sub_object(std::thread::id id);
thread_obj& get_id_object(std::thread::id id);
nodeData& get_data_object(std::thread::id id_ob, std::thread::id id_data);
void create_object(std::thread::id id);
void remove_subscriber(std::thread::id id_subscriber, std::thread::id id_subscription);
void remove_object(std::thread::id id);
void add_sub_data(thread_obj& subscription, thread_obj& subscriber);