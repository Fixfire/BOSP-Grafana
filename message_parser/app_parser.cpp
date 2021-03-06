#include "app_parser.h"
#include "../dci/types.h"
#include "json_utils.h"
#include "../dci/data_client.h"
#include "../message_parser/resource_parser.h"

#include <list>

using namespace bbque::stat;
using namespace bbque;

std::string app_parser::to_json_string()
{
    std::map<std::string, std::string> map = {
        {"id", std::to_string(id)},
        {"state", std::to_string(state)},
        {"name", json_utils::quote(name)},
        {"mapping", mapping_to_json()},
        {"tasks", tasks_to_json()}};
    return json_utils::obj_to_string(map);
}

std::string app_parser::mapping_to_json()
{
    std::list<res_bitset_t>::iterator it;
    std::list<std::string> mapping_array;

    for (it = mapping.begin(); it != mapping.end(); it++)
    {
        mapping_array.push_back(resource_parser::id_parser(*it));
    }
    return json_utils::array_to_string(mapping_array);
}

std::string app_parser::tasks_to_json()
{
    std::list<task_status_t>::iterator it;
    std::list<std::string> tasks_list = {};

    for (it = tasks.begin(); it != tasks.end(); ++it)
    {
        std::map<std::string, std::string> map = {
            {"id", std::to_string(it->id)},
            {"throughtput", std::to_string(it->throughput)},
            {"completion_time", std::to_string(it->completion_time)},
            {"bbq_id", resource_parser::id_parser(it->mapping)},
            {"n_threads", std::to_string(it->n_threads)}};
        tasks_list.push_back(json_utils::obj_to_string(map));
    }
    return json_utils::array_to_string(tasks_list);
}