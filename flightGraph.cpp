#include "flightGraph.h"

namespace flightMaps {
    /**
     * Calculate the distance between two airports using the Haversine Formula
     * @param source source airport
     * @param destination destination airport
     * @return distance in km between airports
     */ 
    double FlightGraph::findDistance(int source, int destination) const {
        double sourceLat = airports[source].getLatitude();
        double sourceLon = airports[source].getLongitude();
        double destLat = airports[destination].getLatitude();
        double destLon = airports[destination].getLongitude();

        //convert lat to radians
        double phi1 = sourceLat * M_PI / 180; 
        double phi2 = destLat * M_PI / 180;
        double deltaPhi = (destLat - sourceLat) * M_PI / 180;
        double deltaLambda = (destLon - sourceLon) * M_PI / 180;

        double a = sin((deltaPhi / 2) * (deltaPhi / 2)) + cos(phi1) * cos(phi2) * sin((deltaLambda / 2) * (deltaLambda / 2));
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return (RADIUS * c) / 1000; //Returns in km
    } 

    /**
     * Converts the vector of csv information into an airport node and adds it to the map of airports
     * 
     * @param line a vector of data in one line of csv
     */
    void FlightGraph::parseAirport(vector<string> line) {
        Node airport;
        airport.setId(std::stoi(line[AIRPORT_ID]));
        airport.setName(line[AIRPORT_NAME]);
        airport.setLatitude(std::stof(line[AIRPORT_LATITUDE]));
        airport.setLongitude(std::stof(line[AIRPORT_LONGITUDE])); 

        airports.insert(airport.getId(), airport);
    }

    void FlightGraph::parseRoute(vector<string> line) {
        int source = stoi(line[ROUTE_SOURCE]);
        int destination = stoi(line[ROUTE_DESTINATION]);
        double distance = findDistance(source, destination);
        Edge::Edge route(source, destination, distance);

        // if the source airport has less than one outgoing route to destination, add it to that airports routes???
        // Basically makes sure that there isn't already a same route
        if (airports[source].getOutgoing().count(destination) < 1) {
            airports[source].addRoute(destination, route));
        }
    }
}