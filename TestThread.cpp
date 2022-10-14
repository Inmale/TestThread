// TestThread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Object.h"

using namespace std;
using namespace chrono_literals;

mutex mut;
condition_variable cv;
vector<thread> nodes;
vector<thread_obj> objects;

void manager()
{
	while (!finished)
	{
		//delay
		this_thread::sleep_for(100ms);
		//delete object if completed
		for (auto& i : objects)
		{
			if (i.get_completed())
			{
				lock_guard<mutex> lm{ mut };
				objects.push_back(i);
				objects.pop_back();
			}
		}
		if (objects.size() < 2)
		{
			finished = true;
		}
	}
}

void node_function(std::thread::id id)
{
	while (!object.get_completed())
	{
		if (event_happend(25))
		{
			object.get_random_number();
		}
		if (event_happend(20))
		{
			//object.subscribe(get_random_object());
		}
		if (event_happend(20))
		{
			//object.unsubscribe();
		}
		if (event_happend(15))
		{

		}
	}
}

bool new_node()
{
	
	if (id < 999)
	{
		unique_ptr<thread> temp (new thread{ node_function, id });
		auto id_thread = temp->get_id();
		nodes.emplace_back(std::move(*temp));
		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].get_id() == id_thread)
			{
				nodes[i].join();
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
////////////////////////////////////
int random_chance()					//
{
	return int(rand() % 100 + 1);	//
}

bool event_happend(int chance)		//
{
	if (random_chance() < chance)	//
	{
		return true;				//
	}
	else
	{
		return false;				//
	}
}
void add_data(std::thread::id id_sub, std::thread::id id, int value) //
{
	for (auto& i : objects)  //
	{
		if (i.getID() == id_sub)
		{
			for (auto& j : i.data)  //
			{
				if (j.id == id)			//
				{
					lock_guard<mutex> mt{ mut };	//
					j.data += value;		//
					j.count++;		//
				}
			}
		}
	}
}
////////////////////////////////////
thread_obj& get_random_object()
{
	{
		lock_guard<mutex> lt{ mut };
		size_t i = (rand() % (objects.size()));
		thread_obj& temp = objects[i];
		return temp;
	}
}

thread_obj* get_sub_object(size_t id)
{
	
	thread_obj* temp;
	if (objects.size() > 1)
	{
		//temp = get_random_object();
		if (true)
		{
			if (temp->getID() != id)
			{
				return temp;
			}
			else
			{
				return get_sub_object(id);
			}
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

int main()
{
	thread nodes_manager(manager);

	for (int i = 0; i < count_nodes; i++)
	{
		nodes.emplace_back(node_function, i);
	}
	//Run
	nodes_manager.join();
	for (auto& i : nodes)
	{
		i.join();
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
