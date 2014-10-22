#include "strset.h"
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
using std::endl;

const set<string> emptyset;
const int NUMBER_OF_TRIES_TO_GET_RANDOM_ID = 5;

map<int, set<string> > sets;

int set_comparator(set<string> first, set<string> second);
bool set_exists(int id);
int get_unused_id();


unsigned long strset_new()
{
	int id = get_unused_id();
	sets[id];
	return id;
}

void strset_delete(unsigned long id)
{
	if (set_exists(id))
	{
		sets.erase(id);
	}
	else
	{

	}
}

size_t strset_size(unsigned long id)
{
	if (set_exists(id))
	{
		return sets[id].size();
	}
	else
	{
		return 0;
	}
}

void strset_insert(unsigned long id, const char *value)
{
	if (set_exists(id))
	{
		sets[id].insert(string(value));
	}
	else
	{
	}
}

void strset_remove(unsigned long id, const char *value)
{
	if (strset_test(id, value))
	{
		sets[id].erase(string(value));
	}
}

int strset_test(unsigned long id, const char *value)
{
	if (set_exists(id))
	{
		string svalue(value);
		if (sets[id].find(svalue) != sets[id].end())
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
	if (set_exists(id))
	{
		sets[id].clear();
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
			return set_comparator(emptyset, sets[id2]);
		}
	}
	else
	{
		if (!set_exists(id2))
		{
			return set_comparator(sets[id1], emptyset);
		}
		else
		{
			return (sets[id1] > sets[id2]) - (sets[id1] < sets[id2]);
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
	return sets.find(id) != sets.end();
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