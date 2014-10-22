#include "strset.h"
#include "strsetconst.h"
#include <set>
#include <map>
#include <string>
#include <cstdlib>
#include <climits>
#include <stdexcept>
#include <iostream>

using std::map;
using std::set;
using std::string;
using std::runtime_error;
using std::cerr;
using std::cout;
using std::endl;
using std::pair;

const set<string> emptyset;
const int NUMBER_OF_TRIES_TO_GET_RANDOM_ID = 5;

int set_comparator(set<string> first, set<string> second);
bool set_exists(int id);
int get_unused_id();

map<int, set<string> > &getSets()
{
	static map<int, set<string> > *sets = new map<int, set<string> >();
	sets->insert(pair<int, set<string>>(strset42, {"42"}));
	return *sets;
}

unsigned long strset_new()
{
	int id = get_unused_id();
	getSets()[id];
	return id;
}

void strset_delete(unsigned long id)
{
	if (id == strset42)return;
	if (set_exists(id))
	{
		getSets().erase(id);
	}
	else
	{

	}
}

size_t strset_size(unsigned long id)
{
	if (set_exists(id))
	{
		return getSets()[id].size();
	}
	else
	{
		return 0;
	}
}

void strset_insert(unsigned long id, const char *value)
{
	if (id == strset42)return;
	if (set_exists(id))
	{
		getSets()[id].insert(string(value));
	}
	else
	{
	}
}

void strset_remove(unsigned long id, const char *value)
{
	if (id == strset42)return;
	if (strset_test(id, value))
	{
		getSets()[id].erase(string(value));
	}
}

int strset_test(unsigned long id, const char *value)
{
	if (set_exists(id))
	{
		string svalue(value);
		if (getSets()[id].find(svalue) != getSets()[id].end())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void strset_clear(unsigned long id)
{
	if (id == strset42)return;
	if (set_exists(id))
	{
		getSets()[id].clear();
	}
	else
	{

	}
}

int strset_comp(unsigned long id1, unsigned long id2)
{
	if (!set_exists(id1))
	{
		if (!set_exists(id2))
		{
			return 0;
		}
		else
		{
			return set_comparator(emptyset, getSets()[id2]);
		}
	}
	else
	{
		if (!set_exists(id2))
		{
			return set_comparator(getSets()[id1], emptyset);
		}
		else
		{
			return (getSets()[id1] > getSets()[id2]) - (getSets()[id1] < getSets()[id2]);
		}
	}
}

int set_comparator(set<string> first, set<string> second)
{
	if (first < second) return -1;
	if (first == second) return 0;
	return 1;
}

bool set_exists(int id)
{
	return getSets().find(id) != getSets().end();
}

int get_unused_id()
{
	int id = -1;
	for (int i = 0; i < NUMBER_OF_TRIES_TO_GET_RANDOM_ID; i++)
	{
		id = rand();
		if (!set_exists(id))
		{
			return id;
		}
	}
	for (int i = INT_MIN; i < INT_MAX; i++)
	{
		if (!set_exists(id))
		{
			return i;
		}
	}
	throw runtime_error("can't find empty index for creating new set");
}