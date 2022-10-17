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
	}
}

size_t get_new_free_id()
{
	lock_guard<mutex> mh{ mut };
	size_t i_count{0};
	if (objects.size() > 0)
	{
		auto pred([&](thread_obj& obj) {return obj.getID() != i_count; });
		auto found_obj(find_if(begin(objects), end(objects), pred));
		if (found_obj != objects.end())
		{
			return i_count;
		}
		i_count++;
		if (i_count > 99)
		{
			finished = true;
			return i_count;
		}
	}
	else
	{
		return 0;
	}
}

void node_function(size_t id)
{
	create_object(id);
	thread_obj& object = get_id_object(id);
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
		cout << id << "\n";
		this_thread::sleep_for(200ms);
	}
}
/////////////////////////////////////
bool new_node()
{
	unique_ptr<thread> temp(new thread{ node_function, get_new_free_id()});
	std::thread::id id_thread (temp->get_id());
	nodes.emplace_back(std::move(*temp));
		
	const auto pred([&](thread& node) {return node.get_id() == id_thread; });
	auto found_node(find_if(begin(nodes), end(nodes), pred));
	found_node->detach();
	return true;
}

int random_chance()					
{
	return int(rand() % 100 + 1);	
}

bool event_happend(int chance)		
{
	if (random_chance() < chance)	
	{
		return true;				
	}
	else
	{
		return false;				
	}
}
void add_data(size_t id_obj, size_t id_data, int value)
{
	nodeData& data (get_data_object(id_obj, id_data));					
	{
		lock_guard<mutex> mt{ mut };
		data.data += value;
		data.count++;
	}
}

thread_obj& get_random_object()
{
	if(objects.size() != 0)
	{
		lock_guard<mutex> lt{ mut };
		size_t i = (rand() % (objects.size()));
		thread_obj& temp = objects[i];
		return temp;
	}
}

thread_obj& get_sub_object(size_t id)
{
	if (objects.size() > 1)
	{
		thread_obj& temp = get_random_object();
		
		if (temp.is_valid())
		{
			if (temp.getID() != id)
			{
				return temp;
			}
			else
			{
				return get_sub_object(id);
			}
		}
		
	}
}
thread_obj& get_id_object(size_t id)
{
	const auto pred([&](thread_obj& i) {return i.getID() == id; });
	const auto found_obj(find_if(begin(objects), end(objects), pred));
	return *found_obj;
}

nodeData& get_data_object(size_t id_ob, size_t id_data)
{
	const auto pred_data([&](nodeData& j) {return j.id == id_data; });
	auto& temp (get_id_object(id_ob));
	const auto found_data(find_if(begin(temp.data), end(temp.data), pred_data));
	return *found_data;
}

void create_object(size_t id)
{
	objects.emplace_back(move(thread_obj(id)));
}

void remove_subscriber(size_t id_subscriber, size_t id_subscription)
{
	thread_obj& temp(get_id_object(id_subscription));

	const auto pred([&](size_t& id) {return id == id_subscriber; });
	const auto found_obj(find_if(begin(temp.subscriptions), end(temp.subscriptions), pred));
}

void remove_object(size_t id)
{
	lock_guard<mutex> mu{ mut };
	auto pred([&](thread_obj& i) {return i.getID() == id; });
	const auto new_end(remove_if(begin(objects), end(objects), pred));
	objects.erase(new_end, objects.end());
}

void add_sub_data(thread_obj& subscription, thread_obj& subscriber)
{
	lock_guard<mutex> ty{ mut };
	subscription.subscriptions.emplace_back(subscriber.getID());
	subscriber.data.emplace_back(subscription.getID ());
}

int main()
{
	thread nodes_manager(manager);

	for (size_t i = 0; i < count_nodes; i++)
	{
		nodes.emplace_back(node_function, i);
	}
	//Run
	nodes_manager.join();
	for (auto& i : nodes)
	{
		i.detach();
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
