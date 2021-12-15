
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

int main() {
    std::cout << "Reached line " << __LINE__ << std::endl;
    FlightGraph graph("graph/airports.dat", "graph/routes.dat");
    PNG canvas;
    std::vector<Drawable*> lines;
    std::vector<Drawable*> circles;
    std::cout << "Reached line " << __LINE__ << std::endl;
    HSLAPixel linecolor(0, 1, 0);
    canvas.resize(3600, 1800);
    std::cout << "Reached line " << __LINE__ << std::endl;
    std::unordered_map<int, int> nodecol = graphcoloring(graph);
    int colnum = 1;
    for (int i = 1; i <= 14110; i++) {
        if ((graph.airports).find(i) == (graph.airports).end())
            continue;
        if (colnum < nodecol[i])
            colnum = nodecol[i];
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
    std::unordered_map<int, int> nodesize = betweennesscentrality(graph);
    for (int i = 1; i <= 14110; i++) {
        if ((graph.airports).find(i) == (graph.airports).end())
            continue;
        for (auto it = (graph.edges[i]).begin(); it != (graph.edges[i]).end(); it++) {    
            int start = it->getSource();
            int end =   it->getDestination();
            int startx = int(10*(graph.airports[start].getLongitude()) + 1800);
            int starty = int(10*(graph.airports[start].getLatitude()) + 900);
            int endx = int(10*(graph.airports[end].getLongitude()));
            int endy = int(10*(graph.airports[end].getLatitude()));
            Drawable* line = new Line(Vector2(startx, starty), Vector2(endx, endy), linecolor);
            lines.push_back(line);
            std::cout << "running betweeness" << std::endl;
        }
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
    for (int i = 1; i <= 14110; i++) {
        if ((graph.airports).find(i) == (graph.airports).end())
            continue;
        int centerx = int(10*(graph.airports[i].getLongitude()) + 1800);
        int centery = int(10*(graph.airports[i].getLatitude()) + 900);
        int radius = 2*nodesize[i];
        double huediff = 360 / (colnum + 1);
        int fac = (nodecol[i]/2) - 1;
        double hue;
        if (nodecol[i] % 2 == 0)
            hue = 180 + fac*huediff;
        else
            hue = fac*huediff;
        Drawable* circle = new Circle(Vector2(centerx, centery), HSLAPixel(hue, 1, 0.5), radius);
        circles.push_back(circle);
    }
    std::cout << "Reached line " << __LINE__ << std::endl;
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
    std::cout << "Reached line " << __LINE__ << std::endl;
    canvas.writeToFile("graph_drawing.png");
    std::cout << "Reached line " << __LINE__ << std::endl;
    return 0;
}