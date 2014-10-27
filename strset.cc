#include "strset.h"
#include "strsetconst.h"
#include <set>
#include <map>
#include <string>
#include <cstdlib>
#include <climits>
#include <stdexcept>
#include <iostream>
#include <sstream>

using std::map;
using std::set;
using std::string;
using std::runtime_error;
using std::stringstream;
using std::cerr;
using std::cout;
using std::endl;
using std::pair;

#if DEBUG_LEVEL == 1
	static const bool debug = 1;
#else
	static const bool debug = 0;
#endif

const set<string> emptyset;
const int NUMBER_OF_TRIES_TO_GET_RANDOM_ID = 5;

static int set_comparator(set<string> first, set<string> second);
static bool set_exists(int id);
static int get_unused_id();

static void log(string s)
{
	if (debug == 0)
		return;
	cout << s << endl;
}

static map<int, set<string> > &getSets()
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
	stringstream ss;
	ss << __func__ << "(" << id << ")";
	log(ss.str());
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
	stringstream ss;
	ss << __func__ << "(" << id <<", " << value << ")";
	log(ss.str());
	if (id == strset42)
	{
		log("strset_insert: attempt to insert into the 42 set");
		return;
	}
	if (set_exists(id))
	{
		if(getSets()[id].find(string(value)) != getSets()[id].end())
		{
			stringstream ss;
			ss << __func__ << ": set " << id << ", element \"" << value << "\" was already present";
			log(ss.str());
		}
		else
		{
			ss << __func__ << ": set " << id << ", element \"" << value << "\" inserted";
			log(ss.str());
		}
		getSets()[id].insert(string(value));
		
	}
	else
	{
		stringstream ss;
		ss<< __func__ << ": set " << id << " does not exist";
		log(ss.str());
	}
}

void strset_remove(unsigned long id, const char *value)
{
	stringstream ss;
	ss << __func__ << "(" << id << ", " << value << ")";
	log(ss.str());
	if (id == strset42)
	{
		log("strset_remove: atempt to remove from the 42 set");
		return;
	}
	if (strset_test(id, value))
	{
		if(getSets()[id].find(string(value)) == getSets()[id].end())
		{
			stringstream ss;
			ss << __func__ << ": set " << id << " does not contain the element \""<< value <<"\"";
			log(ss.str());
		}
		else
		{
			stringstream ss;
			ss << __func__ <<": set " << id << ", element " << value << "removed";
			log(ss.str());
		}	
		getSets()[id].erase(string(value));
	}
	else
	{
		stringstream ss;
		ss << __func__ << ": set " << id << " does not exist"; 
		log(ss.str());
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

static int set_comparator(set<string> first, set<string> second)
{
	if (first < second) return -1;
	if (first == second) return 0;
	return 1;
}

static bool set_exists(int id)
{
	return getSets().find(id) != getSets().end();
}

static int get_unused_id()
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
