
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <queue>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <limits>

#include "graph/flightGraph.h"
#include "graph/node.h"
#include "graph/edge.h"

using std::vector;

// helper function for betweenness centrality
// finds the shortest path between two nodes
// then increments the betweenness centrality value for each airport
// that is between the source and destination in the shortest path
void shortestpathhelper(FlightGraph graph, int sourceid, int destid, std::unordered_map<int, int> & bcval) {
    // initialize priority queue for traveling through the graph
    std::queue<int> priority;
    // need map for the distance for each node from the source node
    // and the previous node in its current shortest path to the destination
    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;
    // initialize all distances to infinity except start, which is zero
    std::unordered_map<int, Node>::iterator it;
    for (it = graph.airports.begin(); it != graph.airports.end(); it++) {
        dist[it -> first] = std::numeric_limits<double>::infinity();
    }
    dist[sourceid] = 0;
    priority.push(sourceid);
    int curnode;
    int neighbor;
    // must use while loop to find all paths from source, in order to find shortest one
    while (!priority.empty()) {
        curnode = priority.front();
        priority.pop();
        if (curnode != destid){
            // for each adjacent airport
            for (size_t i = 0; i < graph.edges[curnode].size(); i++) {
                neighbor = (graph.edges[curnode])[i].getDestination();
                double newdist = (graph.edges[curnode])[i].getDistance() + dist[curnode];
                // if the current route is shorter than whatever previous route distance was found
                // then update the distance and previous and push the destintiation on to the priority queue
                // only adding to the queue if it is the current shortest path should both
                // prevent cycles and ensure all routes are accounted for
                if (newdist < dist[neighbor]) {
                    dist[neighbor] = newdist;
                    prev[neighbor] = curnode;
                    priority.push(neighbor);
                }
            }
        }
    }
    // if the two nodes are connected, now go through the prev map from the
    // destination to the source and increment betweenness centrality for the path nodes
    if (dist[destid] < std::numeric_limits<double>::infinity()) {
        curnode = prev[destid];
        while (curnode != sourceid) {
            bcval[curnode] = bcval[curnode] + 1;
            curnode = prev[curnode];
        }
    }
}

// betweenness centrality algorithm
// betweeenness centrality labels each node of a graph
// by how many shortest paths between an two nodes in the graph
// go through each node
std::unordered_map<int, int> betweennesscentrality(FlightGraph graph) {
    // initialize each node's betweenness centrality value to zero
    std::unordered_map<int, int> bcval;
    std::unordered_map<int, Node>::iterator it;
    for (it = graph.airports.begin(); it != graph.airports.end(); it++) {
        bcval[it -> first] = 0;
    }
    // iterate through every pair of nodes to find its shortest path
    // so betweenness centrality values can be increased
    std::unordered_map<int, Node>::iterator it1;
    for (it1 = graph.airports.begin(); it1 != graph.airports.end(); it1++) {
        std::unordered_map<int, Node>::iterator it2;
        for (it2 = graph.airports.begin(); it2 != graph.airports.end(); it2++) {
            if (it1 -> first != it2 -> first)
                shortestpathhelper(graph, it1 -> first, it2 -> first, bcval);
        }
    }
    return bcval;
}

// helper function for color graphing
// finds the lowest valued color possible for the given node
// based on its neighbors/ colors
// colors are represented by integers
// the lowest-valued being 1
// and the highest being the number of total colors used to color the graph
void nodecolorhelper(FlightGraph graph, int curnode, std::unordered_map<int, int> & colorval) {
    // initialize queue of all neighboring nodes
    std::queue<int> colorqueue;
    std::queue<int> tempcolorqueue;
    for (size_t i = 0; i < graph.edges[curnode].size(); i++) {
        colorqueue.push((graph.edges[curnode])[i].getDestination());
    }
    for (size_t i = 0; i < graph.edgesbydest[curnode].size(); i++) {
        colorqueue.push((graph.edgesbydest[curnode])[i].getSource());
    }
    bool change = 1;
    // initialize current node's color to the lowest value, 1
    colorval[curnode] = 1;
    // look at the color of every neighbor node
    // if any match the current node's color
    // increase the node's color value by 1
    // if the current node's color is changed at any point
    // the neighbors' color values must be looked through again
    // until the current node's color does not match any neighbor's color
    // while also being as low as possible
    while (change == 1){
        change = 0;
        while (!colorqueue.empty()) {
            if (colorval[curnode] == colorval[colorqueue.front()]) {
                colorval[curnode] = colorval[curnode] + 1;
                colorqueue.pop();
                change = 1;
            }
            else {
                tempcolorqueue.push(colorqueue.front());
                colorqueue.pop();
            }
        }
        while (!tempcolorqueue.empty()) {
            colorqueue.push(tempcolorqueue.front());
            tempcolorqueue.pop();
        }
    }

}

// graph coloring algorithm
// graph coloring gives each node in a graph a color
// where every adjacent node does not share a color
// this algorithm hopes to do this with as few colors as possible
// but that is not guaranteed
std::unordered_map<int, int> graphcoloring(FlightGraph graph) {
    // initialize color values for every node to zero
    // this is not a valid color value
    std::unordered_map<int, int> colorval;
    std::unordered_map<int, Node>::iterator it;
    for (it = graph.airports.begin(); it != graph.airports.end(); it++) {
        colorval[it -> first] = 0;
    }
    //will move through nodes and determine curnode using BFS algorithm written by Purvang
    //code needed here...
    std::cout << "Reached line " << __LINE__ << std::endl;
    vector<int> BFTvec = graph.BFT(1);
    std::cout << "Reached line " << __LINE__ << std::endl;
    std::cout << "BFTvec size is  " << BFTvec.size() << std::endl;
    for (unsigned i = 0; i < BFTvec.size(); i++) {
        int curnode = BFTvec[i];
        std::cout << "i =  " << i << std::endl;
        nodecolorhelper(graph, curnode, colorval);

    }
    // find the valid color value for each node
    std::cout << "Reached line " << __LINE__ << std::endl;
    

    return colorval;
}