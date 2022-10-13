#include "Object.h"

void thread_obj::print_data(const size_t subID, const size_t id, const nodeData& data)
{   
    std::lock_guard<std::mutex> lock{m};
    std::cout << id << "-->" << subID << ": " << "S= " << data.data << "  " << id << "-->" << subID << ": " << "N= " << data.count << "\n";
}

bool thread_obj::get_completed()
{
    return completed;
}

size_t thread_obj::getID()
{
    return id;
}

nodeData& thread_obj::get_found_data(size_t id)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].id == id)
        {
            return data[i];
        }
    }
}

void thread_obj::get_random_number()
{ 
    if (subscriptions.size() > 0 && data.size() > 0)
    {
        int data = rand() % 1000;
        for (size_t i = 0; i < subscriptions.size(); i++)
        {
            nodeData _data = subscriptions[i].get_found_data(id);
            _data.count++;
            _data.data += data;
            print_data(subscriptions[i].id, id, _data);
        }
    }
}

bool thread_obj::subscribe()
{
    return false;
}

bool thread_obj::unsubscribe()
{
    return false;
}

bool thread_obj::new_node()
{
    return false;
}
