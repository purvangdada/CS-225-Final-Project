#include "node.h"

namespace flightMaps {
    /**
     * Default constructor for a node
     */
    Node::Node() {
        id_ = -1;
        longitude_ = 0.0;
        latitude_ = 0.0;
        name_ = "";
    }

    /**
     * Constructs a node with given parameters
     * @param id
     * @param name
     * @param longitude
     * @param latitude
     */
    Node::Node(int id, string name, double longitude, double latitude) {
        id_ = id;
        name_ = name;
        longitude_ = longitude;
        latitude_ = latitude;
    }

    /**
     * Gets airport id
     * @return id
     */ 
    int Node::getId() {
        return id_;
    }

    /**
     * Gets airport name
     * @return name
     */ 
    std::string Node::getName() {
        return name_;
    }

    /**
     * Gets airport longitude
     * @return longitude
     */ 
    double Node::getLongitude() {
        return longitude_;
    }

    /**
     * Gets airport latitude
     * @return latitude
     */ 
    double Node::getLatitude() {
        return latitude_;
    }


    void Node::setId(int id) {
        id_ = id;
    }


    void Node::setName(std::string name) {
        name_ = name;
    }

   void Node::getLongitude(double longitude) {
        longitude_ = longitude;
    }

    void Node::setLatitude(double latitude) {
        latitude_ = latitude;
    }

    /**
     * Compares two airports
     * 
     * @return true if two airports have the same name and id
     */
    bool Node::operator ==(const Node& other) {
        
        return (this -> id_ == other.id_ && this -> name_ == other.name_);
    }

    /**
     * Adds a route that leaves this airport
     * @param id destination airport id
     * @param 
     */
     void Node::addRoute(int id, Edge route) {
         outgoing.insert(id, route);
    }

    map<int, Edge> Node::getOutgoing() {
        return outgoing;
    }
}