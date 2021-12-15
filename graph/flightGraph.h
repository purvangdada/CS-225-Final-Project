#pragma once
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <fstream>
#include <queue>
#include "node.h"
#include "edge.h"

class FlightGraph {
    public:
        FlightGraph(const std::string &airportData, const std::string &routeData);
        FlightGraph();

        void addAirport(Node airport);
        void addRoute(Edge route);
            // Holds the airports where id is the key and the airport is the value
        // using unordered_map and vector of edges to simulate hash table
        std::unordered_map<int, Node> airports;
        std::unordered_map<int, std::vector<Edge>> edges;
        // this last map is USED ONLY FOR GRAPH COLORING, stores all the edges a node is the destination of
        std::unordered_map<int, std::vector<Edge>> edgesbydest;

        std::vector<int> BFT(int start);

        // line is a vector of all the information we need from one line of CSV
        void parseAirport(std::vector<std::string> line);
        void parseRoute(std::vector<std::string> line);
        // Converts one line of csv into a vector of strings to be used in functions
        std::vector<std::string> parseLine(const std::string &line);
    private:

        double findDistance(int source, int destination) const; 
        const double RADIUS = 6371000;

        // These constants are for where in line the values are
        const int AIRPORT_ID = 0;
        const int AIRPORT_NAME = 1;
        const int AIRPORT_LONGITUDE = 7;
        const int AIRPORT_LATITUDE = 6;

        const int ROUTE_SOURCE = 3;
        const int ROUTE_DESTINATION = 5;
        const int ROUTE_CONNECTING = 7;
        
        std::string airportData_;
        std::string routeData_;

        // Initialize function and helpers fill in airport and edge maps
        void initialize();
        void initializeAirports();
        void initializeRoutes();
};
