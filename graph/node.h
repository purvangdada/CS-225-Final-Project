#pragma once
#include <string>
#include <map>
#include "edge.h"

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

            bool operator==(const Node& other);

            int getId();
            std::string getName();
            double getLongitude();
            double getLatitude();
            void setId(int id);
            void setName(std::string name);
            void setLongitude(double longitude);
            void setLatitude(double latitude);

            //id of destinatino
            void addRoute(int id, Edge route);
        
            map<int, Edge> getOutgoing();

        private:
            int id_;
            std::string name_;
            double longitude_;
            double latitude_;
            // Map of all routes leaving this airport where the airport id is the key
            // std::unordered_map<int, Edge::Edge> outgoing;
            std::map<int, Edge> outgoing;

    };
}