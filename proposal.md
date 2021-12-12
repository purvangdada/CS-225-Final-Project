CS 225 Data Structures
Final Project Proposal (thm2-pdada2-tinreyd2-muthuga2)

Leading Question: 
Our team has decided to utilize the Open Flights dataset. We are hoping to use our algorithms to better understand the relationship between various airports. Through our use of the algorithms to find the betweenness centrality and graph coloring, we will be able to discover which airports are the most popular and how these airports connect with one another.

Dataset Acquisition and Processing: 
We plan to use the planes.dat and routes.dat for the project. We discovered that these datasets are most relevant when it comes to finding out how different airports interact with each other. These datasets also best complement the graph algorithms we plan to use to show the relationship between a said number of airports.

Graph Algorithms:
The graph algorithms we plan to use for the project include Betweenness Centrality and Graph Coloring. These algorithms will take in the airports as the input nodes, and the flights between them as the input edges. Betweenness centrality will also use the distances between the airports to weight the graph. Betweenness centrality will produce an output graph that represents how necessary an airport is in connecting flights in the shortest paths. Graph coloring will produce an output graph that shows which airports have directly linking flights and which do not and require interconnecting flights. Since for betweenness centrality we essentially have to travel over every edge for each vertex pair in order to find the shortest path, and there are a number of vertex pairs equal to number of vertices squared minus the number of vertices, I would expect a time complexity around O((V^2)E). Though this is not exact because some edges may not be travelled while other edges may be travelled over multiple times for any given shortest path calculation. For graph coloring, each vertex will be examined once along with each of its edges, which I would expect to result in a time complexity around O(V+2E).

Timeline:
The first thing we must do is acquire and process our data set so that we can access and manipulate it with our algorithms. It is our goal to have done this by November 20. It is then our goal to have successfully implemented a BFS traversal of this data by November 29, so it is done before the mid-project check-in, and also have gotten started on our algorithms at this point, at least having a solid understanding of how we will implement them. We will hope to then implement our betweenness centrality and graph coloring algorithms over the next two weeks, doing whichever we determine to be simpler first so that we have more time to tackle the more complex algorithm.
