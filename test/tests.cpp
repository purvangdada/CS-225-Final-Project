#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

TEST_CASE("BFT works") {
    FlightGraph f("graph/airports.dat", "graph/routes.dat");
    f.initialize();
    auto result = f.BFT(0);
    for(unsigned i = 0; i < result.size(); i++) {
        cout << result[i];
        /*if (result[i] == result[i++]) {

            return false;
        }*/

        // each airport only shows up once
        // every airport is traversed
        // create a set [airport]
        check if the airport is already in the set
            return false
        else
            add the current to the set

    }
    return true;
}