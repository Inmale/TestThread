#pragma once
#include <thread>
struct nodeData
{
	nodeData()
	{
		data = 0;
		count = 0;
	}
	nodeData(std::thread::id ID) : id{ ID }, data{ 0 }, count{0} {}
	std::thread::id id;
	int data;
	size_t count;
};