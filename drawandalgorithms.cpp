
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
#include "algorithms.h"

#include "lab_inheritance/PNG.h"
#include "lab_inheritance/HSLAPixel.h"

#include "lab_inheritance/line.h"
#include "lab_inheritance/drawable.h"
#include "lab_inheritance/vector2.h"
#include "lab_inheritance/shape.h"
#include "lab_inheritance/circle.h"
#include "lab_inheritance/triangle.h"
#include "lab_inheritance/rectangle.h"
#include "lab_inheritance/color.h"

#include <unistd.h>

using cs225::PNG;
using cs225::HSLAPixel;
using std::vector;
//this function draws a graph
int main() {
    std::cout << "Reached line " << __LINE__ << std::endl;
    // create graph and canvas
    FlightGraph graph("graph/trairports.dat", "graph/routes.dat");
    PNG canvas;
    // routes will be lines, airports will be circles
    std::vector<Drawable*> lines;
    std::vector<Drawable*> circles;
    std::cout << "Reached line " << __LINE__ << std::endl;
    HSLAPixel linecolor(0, 1, 0);
    canvas.resize(4000, 2000);
    std::cout << "Reached line " << __LINE__ << std::endl;
    // graph coloring is used to color the circles
    std::unordered_map<int, int> nodecol = graphcoloring(graph);
    int colnum = 1;

    std::unordered_map<int, Node>::iterator it1;
    for (it1 = graph.airports.begin(); it1 != graph.airports.end(); it1++) {
        if (colnum < nodecol[it1 -> first])
            colnum = nodecol[it1 -> first];
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
    // betweenness centrality is used to determine node size
    std::unordered_map<int, int> nodesize = betweennesscentrality(graph);

    std::unordered_map<int, std::vector<Edge>>::iterator it2;
    // for each edge, create a line with a start and endpoints determined by longitude and latitude
    for (it2 = graph.edges.begin(); it2 != graph.edges.end(); it2++) {
        for (auto it = (it2 -> second).begin(); it != (it2 -> second).end(); it++) {    
            int start = it->getSource();
            int end =   it->getDestination();
            int startx = int(10*((graph.airports[start].getLongitude()) + 180) + 200);
            int starty = int(10*((graph.airports[start].getLatitude()) + 90) + 100);
            int endx = int(10*((graph.airports[end].getLongitude()) + 180) + 200);
            int endy = int(10*((graph.airports[end].getLatitude()) + 90) + 100);
            Drawable* line = new Line(Vector2(startx, starty), Vector2(endx, endy), linecolor);
            lines.push_back(line);
            std::cout << "running betweeness" << std::endl;
        }
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
    std::unordered_map<int, Node>::iterator it3;
    // for each airport, create a circle with size determined by betweenness centrality and color determined by graph coloring
    for (it3 = graph.airports.begin(); it3 != graph.airports.end(); it3++) {
        int centerx = int(10*((it3 -> second.getLongitude()) + 180) + 200);
        int centery = int(10*((it3 -> second.getLatitude()) + 90) + 100);
        int radius = int(2*((nodesize[it3 -> first])/1000 + 1));
        // separate colors by as much as possible
        double huediff = 360 / (colnum + 1);
        int fac = (nodecol[it3 -> first]/2) - 1;
        double hue;
        // adjacent colors should be as different as possible for legibility
        if (nodecol[it3 -> first] % 2 == 0)
            hue = 180 + fac*huediff;
        else
            hue = fac*huediff;
        Drawable* circle = new Circle(Vector2(centerx, centery), HSLAPixel(hue, 1, 0.5), radius);
        circles.push_back(circle);
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
    // draw and then delete all lines and circles
    while (!lines.empty()) {
        std::cout << "Reached line " << __LINE__ << std::endl;
        lines.back()->draw(&canvas);
        delete lines.back();
        lines.pop_back();
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
    while (!circles.empty()) {
        circles.back()->draw(&canvas);
        delete circles.back();
        circles.pop_back();
    }  
    //write canvas to image
    std::cout << "Reached line " << __LINE__ << std::endl;
    canvas.writeToFile("graph_drawing.png");
    std::cout << "Reached line " << __LINE__ << std::endl;
    return 0;
}