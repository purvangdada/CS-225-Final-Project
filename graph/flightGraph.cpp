#include "flightGraph.h"

using namespace std;
/**
 * Calculate the distance between two airports using the Haversine Formula
 * @param source source airport
 * @param destination destination airport
 * @return distance in km between airports
 */ 
double FlightGraph::findDistance(int source, int destination) const {
    double sourceLat = airports.at(source).getLatitude();
    double sourceLon = airports.at(source).getLongitude();
    double destLat = airports.at(destination).getLatitude();
    double destLon = airports.at(destination).getLongitude();

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
    // DONT USE STOI WE ARE NOT IN C++ 11
    // airport.setId(stoi(line[AIRPORT_ID]));
    // airport.setName(line[AIRPORT_NAME]);
    // airport.setLatitude(stof(line[AIRPORT_LATITUDE]));
    // airport.setLongitude(stof(line[AIRPORT_LONGITUDE])); 

    int airportId = atoi(line[AIRPORT_ID].c_str());
    string airportName = line[AIRPORT_NAME];
    double airportLongitude = atof(line[AIRPORT_LONGITUDE].c_str());
    double airportLatitude = atof(line[AIRPORT_LATITUDE].c_str());

    Node airport(airportId, airportName, airportLongitude, airportLatitude);
    airports.insert(pair<int, Node>(airport.getId(), airport));
}

void FlightGraph::parseRoute(vector<string> line) {
    int source = atoi(line[ROUTE_SOURCE].c_str());
    int destination = atoi(line[ROUTE_DESTINATION].c_str());
    double distance = findDistance(source, destination);
    Edge route(source, destination, distance);
    

    // if the source airport has less than one outgoing route to destination, add it to that airports routes???
    // Basically makes sure that there isn't already a same route
    if (airports[source].getOutgoing().count(destination) < 1) {
        airports[source].addRoute(destination, route);
    }
}

vector<int> BFS(int start, int end){
    vector<bool> visited(airports.size());
    
    for (unsigned i = 0; i < airports.size(); i++) {
        visited[i] = false;
    }

    queue<int> airportQueue;    //  queue 
    vector<int> BFSOrder;  //  order of airports visited during BFS
    airportQueue.push(start);   //  enqueue first airport
    int current = start;    //  setting current to first airport
    //  BFS implementation
    while (!airportQueue.empty()) {
        current = airportQueue.front();
        visited[current] = true;
        BFSOrder.push(current);
        if (current == end){
            break;
        }
        for (auto it = edges[current].begin(); it != edges[current].end(); it++) {    //  search all departures from current airport
            if (!visited[it.getDestination()]) {  // if next airport has not been visited
                airportQueue.push(it.getDestination());   //  enqueue the next airport
            }
        }
        airportQueue.pop(); // pop it off from the queue once traversed
    }

    return BFSOrder;
}
