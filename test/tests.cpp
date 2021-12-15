#include "../catch/catch.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <limits>

#include "../graph/flightGraph.h"
#include "../graph/node.h"
#include "../graph/edge.h"
#include "../algorithms.cpp"

using namespace std;

TEST_CASE("Parse Route, simple") {
    //2B,410,AER,2965,KZN,2990,,0,CR2
    FlightGraph f = FlightGraph();
    Node airport13(13, "airport13", 0.0, 0.0);
    Node airport29(29, "airport29", 0.0, 10.0);
    f.addAirport(airport13);
    f.addAirport(airport29);
    vector<string> line = {"2B", "410", "AER", "13", "KZN", "29", "", "0", "CR2"};
    f.parseRoute(line);
    map<int, Edge> expected;
    Edge expectedEdge = Edge(13, 29);
    expected.insert(pair<int, Edge>(13, expectedEdge));
    REQUIRE(f.airports.at(13).getOutgoing().at(29) == expected.at(13));
}

TEST_CASE("Parse Route, ignores connecting flights") {
    //2B,410,AER,2965,KZN,2990,,1,CR2
    FlightGraph f = FlightGraph();
    Node airport13(13, "airport13", 0.0, 0.0);
    Node airport29(29, "airport29", 0.0, 10.0);
    f.addAirport(airport13);
    f.addAirport(airport29);
    vector<string> line = {"2B", "410", "AER", "13", "KZN", "29", "", "1", "CR2"};
    f.parseRoute(line);
    REQUIRE(f.airports.at(13).getOutgoing().empty());
    REQUIRE(f.airports.at(29).getOutgoing().empty());
}

TEST_CASE("Parse Route, distance equation") {
    FlightGraph f = FlightGraph();
    Node airport13(13, "airport13", 0.0, 5.0);
    Node airport29(29, "airport29", 3.0, 10.0);
    f.addAirport(airport13);
    f.addAirport(airport29);
    vector<string> line = {"2B", "410", "AER", "13", "KZN", "29", "", "0", "CR2"};
    f.parseRoute(line);
    //relative error of 5
    REQUIRE(abs(f.airports.at(13).getOutgoing().at(29).getDistance() - 648.2) < 5);
}

TEST_CASE("Parse Airport, simple") {
    //1,"airport","Chicago","USA","GKA","AYGA",-6,145,5282,10,"U","Pacific/Port_Moresby","airport","OurAirports"
    FlightGraph f = FlightGraph();
    vector<string> line = {"1", "airport", "Chicago", "USA", "GKA", "AYGA", "-6", "145", "5282", "10", "U", "Pacific/Port_Moresby", "airport", "OurAirports"};
    f.parseAirport(line);
    Node expected = Node(1, "airport", -6, 145);
    REQUIRE(f.airports.at(1) == expected);
    REQUIRE(f.airports.at(1).getLongitude() == -6);
    REQUIRE(f.airports.at(1).getLatitude() == 145);
}

TEST_CASE("Parse Line, simple airport") {
    //1,"airport","Chicago","USA","GKA","AYGA",-6,145,5282,10,"U","Pacific/Port_Moresby","airport","OurAirports"
    FlightGraph f = FlightGraph();
    vector<string> line = f.parseLine("1,\"airport\",\"Chicago\",\"USA\",\"GKA\",\"AYGA\",-6,145,5282,10,\"U\",\"Pacific/Port_Moresby\",\"airport\",\"OurAirports\"");
    vector<string> expected = {"1", "airport", "Chicago", "USA", "GKA", "AYGA", "-6", "145", "5282", "10", "U", "Pacific/Port_Moresby", "airport"};
    REQUIRE(line == expected);
}

TEST_CASE("Parse Line, simple route") {
    //2B,410,AER,2965,KZN,2990,,1,CR2
    FlightGraph f = FlightGraph();
    vector<string> line = f.parseLine("2B,410,AER,2965,KZN,2990,,1,CR2");
    vector<string> expected = {"2B", "410", "AER", "2965", "KZN", "2990", "", "1"};
    REQUIRE(line == expected);
}

TEST_CASE("Parse Line, comma in name") {
    //1,"airport","Chicago","USA","GKA","AYGA",-6,145,5282,10,"U","Pacific/Port_Moresby","airport","OurAirports"
    FlightGraph f = FlightGraph();
    vector<string> line = f.parseLine("1,\"air,port\",\"Chicago\",\"USA\",\"GKA\",\"AYGA\",-6,145,5282,10,\"U\",\"Pacific/Port_Moresby\",\"airport\",\"OurAirports\"");
    vector<string> expected = {"1", "air,port", "Chicago", "USA", "GKA", "AYGA", "-6", "145", "5282", "10", "U", "Pacific/Port_Moresby", "airport"};
    REQUIRE(line == expected);
}

TEST_CASE("Reading File, short") {
    FlightGraph graph = FlightGraph("graph/shortairports.dat", "graph/shortroutes.dat");
    REQUIRE(graph.airports.size() == 5);
    REQUIRE(graph.airports.at(2).getOutgoing().size() == 3);
    REQUIRE(graph.edges.size() == 5);
    REQUIRE(graph.edges.at(1).size() == 1);
    REQUIRE(graph.edges.at(2).size() == 3);
    REQUIRE(graph.edges.at(3).size() == 2);
    REQUIRE(graph.edges.at(4).size() == 0);
    REQUIRE(graph.edges.at(5).size() == 0);
}

TEST_CASE("BFT works") {
    FlightGraph f = FlightGraph("graph/shortairports.dat", "graph/shortroutes.dat");
    
    vector<int> bft1 = f.BFT(1);
    vector<int> expected1 = {1, 2, 3, 5, 4};
    vector<int> bft2 = f.BFT(2);
    vector<int> expected2 = {2, 1, 3, 5, 4};
    vector<int> bft3 = f.BFT(3);
    vector<int>expected3 = {3, 1, 4, 2, 5};
    vector<int> bft4 = f.BFT(4);
    vector<int> expected4 = {4};
    vector<int> bft5 = f.BFT(5);
    vector<int> expected5 = {5};
    REQUIRE(bft1 == expected1);
    REQUIRE(bft2 == expected2);
    REQUIRE(bft3 == expected3);
    REQUIRE(bft4 == expected4);
    REQUIRE(bft5 == expected5);
}

TEST_CASE("Betweenness centrality") {
    FlightGraph f = FlightGraph("graph/shortairports.dat", "graph/shortroutes.dat");
    std::unordered_map<int, int> nodesize = betweennesscentrality(f);
    REQUIRE(nodesize.at(1) == 2);
    REQUIRE(nodesize.at(2) == 4);
    REQUIRE(nodesize.at(3) == 2);
    REQUIRE(nodesize.at(4) == 0);
    REQUIRE(nodesize.at(5) == 0);
}

