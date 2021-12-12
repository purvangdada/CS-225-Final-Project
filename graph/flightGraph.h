#pragma once
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include "node.h"
#include "edge.h"

class FlightGraph {
    public:
        FlightGraph();
    private:
        // Holds the airports where id is the key and the airport is the value
        // using unordered_map and vector of edges to simulate hash table
        std::unordered_map<int, Node> airports;
        std::unordered_map<int, std::vector<Edge>> edges;
        // this last map is USED ONLY FOR GRAPH COLORING, stores all the edges a node is the destination of
        std::unordered_map<int, std::vector<Edge>> edgesbydest;

        // TODO: add parsing 
        double findDistance(int source, int destination) const; 
        const double RADIUS = 6371000;


        // line is a vector of all the information we need from one line of CSV
        // These constants are for where in line the values are
        const int AIRPORT_ID = 0;
        const int AIRPORT_NAME = 1;
        const int AIRPORT_LONGITUDE = 2;
        const int AIRPORT_LATITUDE = 3;
        void parseAirport(std::vector<std::string> line);

        const int ROUTE_SOURCE = 0;
        const int ROUTE_DESTINATION = 1;
        void parseRoute(std::vector<std::string> line);       
};