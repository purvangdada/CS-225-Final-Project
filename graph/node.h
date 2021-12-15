#pragma once
#include <string>
#include <map>
#include "edge.h"

/**
 * Stores information about an airport
 * Airports act as the nodes of our graph
 */

class Node {
    public:
    //Constructors
        Node();
        Node(int id, std::string name, double longitude, double latitude);

        bool operator==(const Node& other) const; 

        int getId() const;
        std::string getName() const;
        double getLongitude() const;
        double getLatitude() const;
        void setId(int id);
        void setName(std::string name);
        void setLongitude(double longitude);
        void setLatitude(double latitude);

        //id of destination
        void addRoute(int id, Edge route);
    
        std::map<int, Edge> getOutgoing();

    private:
        int id_;
        std::string name_;
        double longitude_;
        double latitude_;
        // Map of all routes leaving this airport where the airport id is the key
        // std::unordered_map<int, Edge::Edge> outgoing;
        std::map<int, Edge> outgoing;

};
