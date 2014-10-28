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
using std::to_string;

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
static bool contains(int id, string element);


static void log(string s)
{
	if (debug == 0)
		return;
	cout << s << endl;
}

inline static void n_exist_err(int id, string func)
{
	log(func + ": set " + to_string(id) + " does not exist");
}


static map<int, set<string> > &getSets()
{
	static map<int, set<string> > *sets = new map<int, set<string> >();
	sets->insert(pair<int, set<string>>(strset42, {"42"}));
	return *sets;
}

unsigned long strset_new()
{
	log(string(__func__) + "()");
	int id = get_unused_id();
	getSets()[id];
	log(string(__func__) + ": created a new set with the id of " + to_string(id));
	return id;
}

void strset_delete(unsigned long id)
{
	log(string(__func__) + "(" + to_string(id) + ")");
	if (id == strset42)
	{
		log(string(__func__) + ": trying to delete the 42 set");
		return;
	}
	if (set_exists(id))
	{
		log(string(__func__) + ": set " + to_string(id) + " deleted");
		getSets().erase(id);
	}
	else
	{
		n_exist_err(id, string(__func__));
	}
}

size_t strset_size(unsigned long id)
{
	log(string(__func__)  + "(" + to_string(id) + ")");
	if (set_exists(id))
	{
		log(string(__func__) + ": set " + to_string(id) + " contains " + to_string(getSets()[id].size()) + " element(s)");
		return getSets()[id].size();
	}
	else
	{
		n_exist_err(id, string(__func__));
		return 0;
	}
}

void strset_insert(unsigned long id, const char *value)
{
	log(string(__func__) + "(" + to_string(id) + ", " + value + ")");
	if (id == strset42)
	{
		log("strset_insert: attempt to insert into the 42 set");
		return;
	}
	if (set_exists(id))
	{
		if(contains(id, string(value)))
		{
			log(string(__func__) + ": set " + to_string(id) + ", element \"" + value + "\" was already present");
		}
		else
		{
			log( string(__func__) + ": set " + to_string(id) + ", element \"" + value + "\" inserted");
		}
		getSets()[id].insert(string(value));
		
	}
	else
	{
		n_exist_err(id, string(__func__));
	}
}

void strset_remove(unsigned long id, const char *value)
{
	log(string(__func__) + "(" + to_string(id) + ", " + value + ")");
	if (id == strset42)
	{
		log("strset_remove: atempt to remove from the 42 set");
		return;
	}
	if (set_exists(id))
	{
		if(!contains(id, string(value)))
		{
			log(string(__func__) + ": set " + to_string(id) + " does not contain the element \"" + value  + "\"");
		}
		else
		{
			log(string( __func__) + ": set " +  to_string(id) + ", element \"" + value + "\" removed");
		}	
		getSets()[id].erase(string(value));
	}
	else
	{
		n_exist_err(id, string(__func__));
	}
}

int strset_test(unsigned long id, const char *value)
{
	log(string(__func__) + "(" + to_string(id) + ", " + value + ")");
	if (set_exists(id))
	{
		string svalue(value);
		if (contains(id, string(value)))
		{
			log(string(__func__) + ": set " + to_string(id) + " contains the element \"" + value + "\""); 
			return 1;
		}
		else
		{
			log(string(__func__) + ": set " + to_string(id) + " does not contain the element \"" + value + "\"");
			return 0;
		}
	}
	else
	{
		n_exist_err(id, string(__func__));
		return 0;
	}
}

void strset_clear(unsigned long id)
{
	log(string(__func__) + "(" + to_string(id) + ")");
	if (id == strset42)
	{
		log(string(__func__) + ": trying to clear the 42 set");
		return;
	}
	if (set_exists(id))
	{
		log(string(__func__) + ": set " + to_string(id) + " is now empty");
		getSets()[id].clear();
	}
	else
	{
		n_exist_err(id, string(__func__));
	}
}

int strset_comp(unsigned long id1, unsigned long id2)
{
	log(string(__func__) + "(" + to_string(id1) + ", " + to_string(id2) + ")");
	if (!set_exists(id1))
	{
		n_exist_err(id1, string(__func__));
		if (!set_exists(id2))
		{
			n_exist_err(id2, string(__func__));
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
			n_exist_err(id2, string(__func__));
			return set_comparator(getSets()[id1], emptyset);
		}
		else
		{
			int ans = set_comparator(getSets()[id1], getSets()[id2]);
			log(string(__func__) + ": the result of comparing set " + to_string(id1) + " to set " + to_string(id2) + " is " + to_string(ans));		
			return ans;
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

static bool contains(int id, string element)
{
	return (getSets()[id].find(element) != getSets()[id].end()); 
}
