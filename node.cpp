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
    Node(int id, string name, double longitude, double latitude) {
        id_ = id;
        name_ = name;
        longitude_ = longitude;
        latitude_ = latitude;
    }

    bool Node::operator ==(const Node& other) {
        // Returns true if two airports have the same name and id
        return (this -> id_ == other.id_ && this -> name_ == other.name_);
    }
}