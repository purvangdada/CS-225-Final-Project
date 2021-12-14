#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

TEST_CASE("BFT works") {
    FlightGraph f();
    Node airport1(1, "airport1", 5.0, 5.0);
    Node airport2(2, "airport2", 10.0, 0.0);
    Node airport3(3, "airport3", 0.0, 0.0);
    Node airport4(4, "airport4", 3.0, 20.0);
    Node airport5(5, "airport5", 5.0, 30.0);
    f.addAirport(airport1);
    f.addAirport(airport2);
    f.addAirport(airport3);
    f.addAirport(airport4);
    f.addAirport(airport5);
    Edge OneToTwo(1, 2);
    Edge TwoToOne(2, 1);
    Edge ThreeToOne(3, 1);
    Edge TwoToThree(2, 3);
    Edge TwoToFive(2, 5);
    Edge ThreeToFour(3, 4);
    f.addEdge(OneToTwo);
    f.addEdge(TwoToOne);
    f.addEdge(ThreeToOne);
    f.addEdge(TwoToThree);
    f.addEdge(TwoToFive);
    f.addEdge(ThreeToFour);

    vector<int> bft1 = f.BFT(1);
    vector<int> bft2 = f.BFT(2);
    vector<int> expected1 = {1, 2, 3, 5, 4};
    vetor<int> expected2 = {2, 1, 3, 5, 4};
    REQUIRE(bft1 == expected1);
    REQUIRE(bft2 == expected2);
}