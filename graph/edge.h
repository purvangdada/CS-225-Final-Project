#pragma once
#include <string>
/**
 * Use the routes between airports as the edges of the graph
 */
class Edge {
    public:
        // Construct an edge without a weight
        Edge();
        Edge(int source, int destination);
        
        // Construct an edge with a distance as the weight
        Edge(int source, int destination, double distance);

        // Setters and Getters
        int getSource();
        int getDestination();
        double getDistance();
        void setDistance(double distance);

        bool operator==(const Edge& other) const;
        bool operator<(const Edge& other) const;
    private:
        int source_; //ID of source airport
        int destination_; //ID of destination airport
        double distance_; //Distance between source and destination
};