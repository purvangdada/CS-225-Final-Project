#pragma once
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include "node.h"

namespace flightMaps {
    class FlightGraph {
        public:

        private:
            // Holds the airports where id is the key and the airport is the value
            map<int, node> airports;

            // TODO: add parsing 
            double findDistance(int source, int destination) const; 
            const double RADIUS = 6371000;


            // line is a vector of all the information we need from one line of CSV
            // These constants are for where in line the values are
            const int AIRPORT_ID = 0;
            const int AIRPORT_NAME = 1;
            const int AIRPORT_LONGITUDE = 2;
            const int AIRPORT_LATITUDE = 3;
            void parseAirport(vector<string> line);

            const int ROUTE_SOURCE = 0;
            const int ROUTE_DESTINATION = 1;
            void parseRoute(vector<string> line); 
            


            

            
    }
}