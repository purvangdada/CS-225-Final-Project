#include "flightGraph.h"

using namespace std;

FlightGraph::FlightGraph(const string &airportData, const string &routeData) {
    airportData_ = airportData;
    routeData_ = routeData;
    initialize();
}

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
    if (atoi(line[ROUTE_CONNECTING].c_str()) == 0) {
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
}

vector<int> FlightGraph::BFT(int start){
    vector<bool> visited(airports.size()); // to keep track of visited nodes
    set<int> unvisited; // to keep track of completely disconnected nodes

    for (unsigned i = 0; i < airports.size(); i++) { // set all nodes to non visted yet
        visited[i] = false;
        unvisited.insert(i);
    }

    std::queue<int> airportQueue; // queue to implement bfs 
    std::vector<int> BFSOrder; // vector to return
    airportQueue.push(start);  
    int current = start;    
    //  BFS implementation
    while (!airportQueue.empty() && !unvisited.empty()) {
        if(airportQueue.empty() && !unvisited.empty()){ // if explored all elements in connected component, fetch node from other connected component
            int disconnectedNode = *(unvisited.begin());
            airportQueue.push(disconnectedNode);
        }
        current = airportQueue.front();
        visited[current] = true;
        unvisited.erase(current);
        BFSOrder.push_back(current);
        for (auto it = edges[current].begin(); it != edges[current].end(); it++) {    
            if (!visited[it->getDestination()]) {  
                airportQueue.push(it->getDestination());  
            }
        }
        airportQueue.pop(); 
    }


    return BFSOrder;
}

/**
 * Separates a singular line of CSV into a vector of strings
 * Removes quotation marks from output
 * @param line a line of csv
 * @return the line in a vector form
 */ 
vector<string> FlightGraph::parseLine(const string &line) {
    char temp;
    bool isQuote = false;
    string current = "";
    vector<string> output;

    for (size_t i = 0; i < line.size(); i++) {
        temp = line[i];
        if (isQuote == false) {
            if (temp == ',') {
                //add a new string to the vector if there is a comma
                output.push_back(current);
                current = "";
            } else if (temp == '"') {
                isQuote = true;
            } else {
                current += temp;
            }
        } else {
            if (temp == '"' && i + 1 < line.size()) {
                if (line[i+1] == '"') {
                    current += '"';
                    i++;
                } else {
                    isQuote = false;
                }
            } else {
                current += temp;
            }
        }
    }
    return output;
}

/**
 * Helps the constructor in filling the maps with airports and routes
 */
void FlightGraph::initialize() {
    initializeAirports();
    initializeRoutes();
}

/**
 * Fills map of airports
 */
void FlightGraph::initializeAirports() {
    ifstream infile(airportData_);
    string temp;

    while(getline(infile, temp)) {
        vector<string> line = parseLine(temp);
        parseAirport(line);
    }
    infile.close();
}


void FlightGraph::initializeRoutes() {
    ifstream infile(routeData_);
    string temp;

    while(getline(infile, temp)) {
        vector<string> line = parseLine(temp);
        parseRoute(line);
    }
    infile.close();
}

void FlightGraph::addAirport(Node airport) {
    airports.insert(pair<int, Node>(airport.getId(), airport));
}

void FlightGraph::addRoute(Edge route) {
    airports.at(route.getSource()).addRoute(route.getDestination(), route);
}