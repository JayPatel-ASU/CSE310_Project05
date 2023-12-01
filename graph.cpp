#include "graph.h"
#include "minheap.h"

using namespace std;
const double DOUBLE_MAX = 99999999.0;

/**
 *
 */
Graph::Graph() {
    // Constructor implementation
    // set pointers to nullptr
    // set variables to default values
    // Initialize numVertices, numEdges, and isDirected
}

/**
 *
 */
Graph::~Graph() {
    // Destructor implementation
    // deallocate memory for arrays
    // Free individual adjacency lists
    // Free the vector of adjacency lists
}

/**
 *
 * @param filename
 * @param direction
 * @return
 */
bool Graph::loadGraph(const string& filename, const string& direction) {
    /*
    // Open the input file
    file = open(filename)

    // Check if the file is successfully opened
    if file is not open
        print "Failed to open the graph file."
        return false

    // Read the first line from the file
    line = readLine(file)

    // Check if the first line is successfully read
    if not line
        print "Input file is empty."
        return false

    // Parse the first line to get the number of vertices and edges
    iss = createStringStream(line)
    n, m = 0, 0
    if iss >> n >> m
        numVertices = n + 1
        numEdges = m

        // Allocate memory for adjacencyLists
        adjacencyLists = new Edge*[numVertices]
        for i from 0 to numVertices - 1
            adjacencyLists[i] = null

        // Allocate memory for extractedVertices, relaxedVertices, predecessor, and distance
        extractedVertices = new double[numVertices]
        relaxedVertices = new double[numVertices]
        predecessor = new int[numVertices]
        distance = new double[numVertices]
        for i from 0 to numVertices - 1
            extractedVertices[i] = -1
            relaxedVertices[i] = -1

    else
        print "Invalid format for the first line in the input file."
        return false

    // Close the file and reopen it to read the content again
    close(file)
    file = open(filename)

    // Check if the file is successfully reopened
    if file is not open
        print "Failed to reopen the graph file."
        return false

    // Read the first line again to skip it
    readLine(file)

    // Loop through the remaining lines to read edges and build adjacency lists
    for each line in file
        edgeId, startNode, endNode, weight = 0, 0, 0, 0
        iss = createStringStream(line)

        // Parse the line to get edge information
        if iss >> edgeId >> startNode >> endNode >> weight
            startNode++
            endNode++

            // Check if node IDs are valid
            if startNode > numVertices or endNode > numVertices or startNode < 1 or endNode < 1
                print "Invalid node IDs in the input file."
                return false

            // Create a new edge
            edge = new Edge
            edge.destination = endNode
            edge.weight = weight

            // Add edge to the adjacency list
            if adjacencyLists[startNode] is null
                adjacencyLists[startNode] = new Edge[numEdges]

            j = 0
            // Find the next available slot in the adjacency list
            while adjacencyLists[startNode][j].destination is not 0
                j++

            // Add the edge to the list
            adjacencyLists[startNode][j] = edge

            // If the graph is undirected, add the reverse edge
            if direction is "undirected"
                reverseEdge = new Edge
                reverseEdge.destination = startNode
                reverseEdge.weight = weight

                if adjacencyLists[endNode] is null
                    adjacencyLists[endNode] = new Edge[numEdges]

                j = 0
                // Find the next available slot in the adjacency list
                while adjacencyLists[endNode][j].destination is not 0
                    j++

                // Add the reverse edge to the list
                adjacencyLists[endNode][j] = reverseEdge

                // Deallocate memory for the reverse edge
                delete reverseEdge

            // Deallocate memory for the edge
            delete edge

        else
            print "Invalid format for edge in the input file."
            return false

    // Set the graph direction
    isDirected = (direction is "directed")

    // Close the file
    close(file)

    return true

    */
}

void Graph::runDijkstra(int newSource, int destination, int flag) {
    /*
    // Initialize variables and data structures
    n = numVertices
    source = newSource
    graphTraversed = true
    fullTraversal = true

    // Create arrays and data structures for Dijkstra's algorithm
    extracted = new bool[n]
    for i = 0 to n-1
        extracted[i] = false
        extractedVertices[i] = -1
        relaxedVertices[i] = -1
        predecessor[i] = -1
        distance[i] = DOUBLE_MAX

    // Mark the source as extracted
    extracted[source] = true

    // Initialize the MinHeap data structure
    minHeap.init(n)
    distance[source] = 0
    minHeap.push(0, source)

    // If flag is set, print initial insertion
    if flag == 1
        print "Insert vertex ", source, ", key=", distance[source]

    // Main Dijkstra's algorithm loop
    while minHeap is not empty
        // Extract the minimum distance vertex from the MinHeap
        u = minHeap.pop()

        // Mark the vertex as extracted
        extracted[u] = true
        extractedVertices[u] = distance[u]

        // If flag is set, print deletion of vertex
        if flag == 1
            print "Delete vertex ", u, ", key=", distance[u]

        // If the destination is reached, exit the loop
        if u == destination
            break

        // Loop through the adjacency list of the current vertex
        if adjacencyLists[u]
            j = 0
            while adjacencyLists[u][j].destination != 0
                // Extract neighbor information
                v = adjacencyLists[u][j].destination
                w = adjacencyLists[u][j].weight

                // If the neighbor is not extracted and relaxation is possible
                if not extracted[v] and distance[u] + w < distance[v]
                    // Perform relaxation
                    oldDistance = distance[v]
                    distance[v] = distance[u] + w
                    predecessor[v] = u
                    relaxedVertices[v] = distance[v]

                    // If flag is set, print decrease key operation
                    if oldDistance != DOUBLE_MAX and flag == 1
                        print "Decrease key of vertex ", v, ", from ", oldDistance, " to ", distance[v]

                    // Push the neighbor into the MinHeap
                    minHeap.push(distance[v], v)

                    // If flag is set, print insertion of vertex
                    if flag == 1
                        print "Insert vertex ", v, ", key=", distance[v]

                j++

    // Handle vertices left in MinHeap after the main loop
    while minHeap is not empty
        u = minHeap.pop()
        if extracted[u] is false
            fullTraversal = false

    // Deallocate memory for extracted array
    delete[] extracted

    */
}

void Graph::writePath(int s, int d) {
    /*
    // Check if the graph has been traversed
    if graphTraversed is false
        print "Error: no path computation done"
        return

    // Check for valid source-destination pair
    if s is not equal to source or d is less than 1 or d is greater than or equal to numVertices
        print "Error: invalid source destination pair"
        return

    // Case 1: Shortest s-d path is computed
    if extractedVertices[d] is not equal to -1
        // Create an array to store the path
        path = new int[numVertices]
        current = d
        pathSize = 0

        // Reconstruct the path
        while current is not equal to s
            path[pathSize] = current
            current = predecessor[current]
            pathSize++

        path[pathSize] = s

        // Print the shortest path
        print "Shortest path: "
        for i from pathSize to 0
            print path[i], " "
        print newline

        // Print the path weight
        print "The path weight is: ", distance[d]

        // Deallocate memory for the path array
        delete[] path

    // Case 2: s-d path computed but not known if it's the shortest
    else if relaxedVertices[d] is not equal to -1
        // Create an array to store the path
        path = new int[numVertices]
        current = d
        pathSize = 0

        // Reconstruct the path
        while current is not equal to s
            path[pathSize] = current
            current = predecessor[current]
            pathSize++

        path[pathSize] = s

        // Print the path not known to be the shortest
        print "Path not known to be shortest: "
        for i from pathSize to 0
            print path[i], " "
        print newline

        // Print the path weight
        print "The path weight is: ", distance[d]

        // Deallocate memory for the path array
        delete[] path

    // Case 3: No s-d path computed, and no min-heap operations were printed
    else if fullTraversal is false
        print "No ", s, "-", d, " path has been computed, yet."

    // Case 4: Entire graph has been traversed, and d is not in extracted or relaxed
    else
        print "No ", s, "-", d, " path exists."
    */
}

void Graph::printAdjacencyLists() {
    /*
    // Loop through each vertex in the graph
    for v from 0 to numVertices - 1
        print "Adjacency list for vertex " + v + ": "

        // Check if the adjacency list for the current vertex exists
        if adjacencyLists[v] is not null
            j = 0

            // Loop through each edge in the adjacency list
            while adjacencyLists[v][j].destination is not 0
                // Print the destination vertex and edge weight
                print "(" + adjacencyLists[v][j].destination + ", " + adjacencyLists[v][j].weight + ") "

                // Move to the next edge in the list
                j++

        // Print the predecessor value for the current vertex
        print "Predecessor: " + predecessor[v]

        // Move to the next line for the next vertex
        print newline
    */
}