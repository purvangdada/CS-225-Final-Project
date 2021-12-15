#include "graph/flightGraph.h"
#include <unordered_map>

void shortestpathhelper(FlightGraph graph, int sourceid, int destid, std::unordered_map<int, int> & bcval);

std::unordered_map<int, int> betweennesscentrality(FlightGraph graph);

void nodecolorhelper(FlightGraph graph, int curnode, std::unordered_map<int, int> & colorval);

std::unordered_map<int, int> graphcoloring(FlightGraph graph);