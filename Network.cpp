#include "Network.h"
#include <iostream>
#include <deque>
#include <iterator>

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/topological_sort.hpp"
using namespace GenericNEAT;
using namespace boost;


Network::Network()
{
	adjacency_list<> g(8);
}


Network::~Network()
{
}
