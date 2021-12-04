#include "edge.h"

namespace flightMaps{
    /**
     * Constructs an edge with no weight
     * 
     * @param source Where the flight comes from
     * @param destination Where the flight is going
     */
    Edge::Edge(int source, int destination) {
        source_ = source;
        destination_ = destination;
    }

    /**
     * Constructs an edge with a weight
     * 
     * @param source Where the flight comes from
     * @param destination Where the flight is going
     * @param distance The distance between source and destination used as a weight
     */
    Edge::Edge(int source, int destination, double distance) {
        source_ = source;
        destination_ = destination;
        distance_ = distance;
    }
    /**
     * Gets source of route
     * @return source
     */
    int Edge::getSource() {
        return source_;
    }

    /**
     * Gets destination of route
     * @return destination
     */
    int Edge::getDestination() {
        return destination_;
    }

    /**
     * Gets distance of route
     * @return distance
     */
    double Edge::getDistance() {
        return distance_;
    }

    /**
     * Sets distance of route
     * @param distance
     */
    void Edge::setDistance(double distance) {
        distance_ = distance;
    }

    /**
     * Overloads == operator
     * @return true if source and destination are the same, false otherwise
     */ 
    bool Edge::operator==(Edge& other) const {
        return source_ == other.source_ && destination_ == other.destination_; 
    }

    /**
     * Overlaods < operator for comparing with other edges
     * @return true if this distance is less than the other edge's distance
     */ 
    bool operator<(const Edge& other) const {
        return distance_ < other.distance_;
    }
}