#pragma once
#include <thread>
struct nodeData
{
	nodeData()
	{
		data = 0;
		count = 0;
	}
	nodeData(size_t ID) : id{ ID }, data{ 0 }, count{0} {}
	size_t id;
	int data;
	size_t count;
};