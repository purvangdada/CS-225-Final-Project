#pragma once
#include <string>

namespace flightMaps{

    /**
     * Stores information about an airport
     * Airports act as the nodes of our graph
     */

    class Node {
        public:
        //Constructors
            Node();
            Node(int id, std::string name, double longitude, double latitude);

            bool operator ==(const Node& other);

        private:
            int id_;
            std::string name_;
            double longitude_;
            double latitude_;

    };
}