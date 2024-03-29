#include <iostream>
#include "graph.h"

using namespace std;
const double DOUBLE_MAX = 99999999.0;

/**
 * Default Constructor
 */
Graph::Graph() {
    // Set pointers to nullptr
    adjacencyLists = nullptr;
    extractedVertices = nullptr;
    relaxedVertices = nullptr;
    predecessor = nullptr;
    distance = nullptr;

    // Initialize all other class instance variables
    source = 0;
    numVertices = 0;
    numEdges = 0;
    graphTraversed = false;
    fullTraversal = false;
    isDirected = false;
}

/**
 * Destructor
 */
Graph::~Graph() {
    // Delete memory allocated to arrays
    delete extractedVertices;
    delete relaxedVertices;
    delete predecessor;
    delete distance;

    // Free individual adjacency lists
    for (int i = 0; i < numVertices; i++) {
        delete[] adjacencyLists[i];
    }

    // Free the vector of adjacency lists
    delete[] adjacencyLists;
}

/**
 * loadGraph(string&, string&)
 * @param filename
 * @param direction
 * @return bool
 */
bool Graph::loadGraph(const string& filename, const string& direction) {

    // Open the input file
    ifstream file(filename);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        printf("Failed to open the graph file.\n");
        return false;
    }

    // Read the first line from the file
    string line;
    getline(file, line);

    // Check if the first line is successfully read
    if (line.empty()) {
        printf("Input file is empty.\n");
        return false;
    }

    // Parse the first line to get the number of vertices and edges
    istringstream iss(line);
    int n = 0;
    int m = 0;

    if (iss >> n >> m) {
        numVertices = n + 1;
        numEdges = m;

        // Allocate memory for adjacencyLists
        adjacencyLists = new Edge*[numVertices];

        for (int i = 0; i < numVertices; i++){
            adjacencyLists[i] = nullptr;
        }

        // Allocate memory for extractedVertices, relaxedVertices, predecessor, and distance
        extractedVertices = new double[numVertices];
        relaxedVertices = new double[numVertices];
        predecessor = new int[numVertices];
        distance = new double[numVertices];

        for (int i = 0; i < numVertices; i++) {
            extractedVertices[i] = -1;
            relaxedVertices[i] = -1;
        }
    }

    else {
        printf("Invalid format for the first line in the input file.\n");
        return false;
    }

    // Close the file and reopen it to read the content again
    file.close();

    file.open(filename);

    // Check if the file is successfully reopened
    if (!file.is_open()) {
        printf("Failed to reopen the graph file.\n");
        return false;
    }

    // Read the first line again to skip it
    getline(file, line);

    // Loop through the remaining lines to read edges and build adjacency lists
    while (getline(file,line)) {
        double weight;
        int edgeId, startNode, endNode;
        istringstream iss(line);

        // Parse the line to get edge information
        if (iss >> edgeId >> startNode >> endNode >> weight) {
            startNode++;
            endNode++;

            // Check if node IDs are valid
            if (startNode > numVertices || endNode > numVertices || startNode < 1 || endNode < 1) {
                printf("Invalid node IDs in the input file.\n");
                return false;
            }

            // Create a new edge
            Edge* edge = new Edge;
            edge->destination = endNode;
            edge->weight = weight;

            // Add edge to the adjacency list
            if (adjacencyLists[startNode] == nullptr)
                adjacencyLists[startNode] = new Edge[numEdges];

            int j = 0;
            // Find the next available slot in the adjacency list
            while (adjacencyLists[startNode][j].destination != 0) {
                j++;
            }

            // Add the edge to the list
            adjacencyLists[startNode][j] = *edge;

            // If the graph is undirected, add the reverse edge
            if (direction == "undirected") {
                Edge* reverseEdge = new Edge;
                reverseEdge->destination = startNode;
                reverseEdge->weight = weight;

                if (adjacencyLists[endNode] == nullptr)
                    adjacencyLists[endNode] = new Edge[numEdges];

                j = 0;
                // Find the next available slot in the adjacency list
                while (adjacencyLists[endNode][j].destination != 0) {
                    j++;
                }

                // Add the reverse edge to the list
                adjacencyLists[endNode][j] = *reverseEdge;

                // Deallocate memory for the reverse edge
                delete reverseEdge;
            }

            // Deallocate memory for the edge
            delete edge;
        }
        else {
            printf("Invalid format for edge in the input file.\n");
            return false;
        }
    }

    // Set the graph direction
    isDirected = (direction == "directed");

    // Close the file
    file.close();

    return true;
}

/**
 * rundijkstra(int, int, int)
 * @param newSource
 * @param destination
 * @param flag
 */
void Graph::runDijkstra(int newSource, int destination, int flag) {

    // Initialize variables and data structures
    int n = numVertices;
    source = newSource;
    graphTraversed = true;
    fullTraversal = true;

    // Create arrays and data structures for Dijkstra's algorithm
    bool* extracted = new bool[n];

    // Populate extracted arr, vertices
    for (int i = 0; i < n; i++) {
        extracted[i] = false;
        extractedVertices[i] = -1;
        relaxedVertices[i] = -1;
        predecessor[i] = -1;
        distance[i] = DOUBLE_MAX;
    }

    // Mark the source as extracted
    extracted[source] = true;

    // Initialize the MinHeap data structure
    minHeap.init(n);
    distance[source] = 0;
    minHeap.push(0, source);

    // If flag is set, print initial insertion
    if (flag == 1) {
        printf("Insert vertex %d, key=%12.4f\n", source, distance[source]);
    }

    // Main Dijkstra's algorithm loop
    while (!minHeap.empty()) {
        // Extract the minimum distance vertex from the MinHeap
        int u = minHeap.pop();

        // Mark the vertex as extracted
        extracted[u] = true;
        extractedVertices[u] = distance[u];

        // If flag is set, print deletion of vertex
        if (flag == 1) {
            printf("Delete vertex %d, key=%12.4f\n", u, distance[u]);
        }

        // If the destination is reached, exit the loop
        if (u == destination) {
            break;
        }

        // Loop through the adjacency list of the current vertex
        if (adjacencyLists[u] != nullptr) {
            int j = 0;
            while (adjacencyLists[u][j].destination != 0) {
                // Extract neighbor information
                int v = adjacencyLists[u][j].destination;
                double w = adjacencyLists[u][j].weight;

                // If the neighbor is not extracted and relaxation is possible
                if (!extracted[v] && distance[u] + w < distance[v]) {
                    // Perform relaxation
                    double oldDistance = distance[v];
                    distance[v] = distance[u] + w;
                    predecessor[v] = u;
                    relaxedVertices[v] = distance[v];

                    // If flag is set, print decrease key operation
                    if (oldDistance != DOUBLE_MAX && flag == 1)
                        printf("Decrease key of vertex %d, from %13.4f to%13.4f\n", v, oldDistance, distance[v]);

                    // Push the neighbor into the MinHeap
                    minHeap.push(distance[v], v);

                    // If flag is set, print insertion of vertex
                    if (flag == 1)
                        printf("Insert vertex %d, key=%12.4f\n", v, distance[v]);
                }
                j++;
            }
        }
    }

    // Handle vertices left in MinHeap after the main loop
    while (!minHeap.empty()) {
        int u = minHeap.pop();
        if (extracted[u] == false) {
            fullTraversal = false;
        }
    }
    // Deallocate memory for extracted array
    delete[] extracted;
}

/**
 * writePath()
 * @param s
 * @param d
 */
void Graph::writePath(int s, int d) {
    // Check if the graph has been traversed
    if (!graphTraversed) {
        cout << "Error: no path computation done" << endl;
        return;
    }

    // Check for valid source-destination pair
    if (s != source || d < 1 || d >= numVertices) {
        cout << "Error: invalid source destination pair" << endl;
        return;
    }

    // Case 1: Shortest s-d path is computed
    if (extractedVertices[d] != -1) {
        // Create an array to store the path
        int *path = new int[numVertices];
        int current = d;
        int pathSize = 0;

        // Reconstruct the path
        while (current != s) {
            path[pathSize] = current;
            current = predecessor[current];
            pathSize++;
        }

        path[pathSize] = s;

        // Print the shortest path
        cout << "Shortest path: ";
        for (int i = pathSize; i >= 0; i--) {
            cout << path[i] << " ";
            cout << endl;

            // Print the path weight
            printf("The path weight is: %12.4f\n", distance[d]);

            // Deallocate memory for the path array
            delete[] path;
        }
    }
    // Case 2: s-d path computed but not known if it's the shortest
    else if (relaxedVertices[d] != -1) {
        // Create an array to store the path
        int *path = new int[numVertices];
        int current = d;
        int pathSize = 0;

        // Reconstruct the path
        while (current != s) {
            path[pathSize] = current;
            current = predecessor[current];
            pathSize++;
        }

        path[pathSize] = s;

        // Print the path not known to be the shortest
        cout << "Path not known to be shortest: ";
        for (int i = pathSize; i >= 0; i--) {
            cout << path[i] << " ";
        }
        cout << endl;

        // Print the path weight
        printf("The path weight is: %12.4f\n", distance[d]);

        // Deallocate memory for the path array
        delete path;
    }

    // Case 3: No s-d path computed, and no min-heap operations were printed
    else if (!fullTraversal) {
        cout << "No " << s << "-" << d << " path has been computed, yet." << endl;
    }

    // Case 4: Entire graph has been traversed, and d is not in extracted or relaxed
    else {
        cout << "No " << s << "-" << d << " path exists." << endl;
    }
}


/**
 * printAdjacencyLists()
 */
void Graph::printAdjacencyLists() {

    for (int v = 0; v < numVertices; v++) {
        cout << "Adjacency list for vertex " << v << ": ";

        // Check if the adjacency list for the current vertex exists
        if (adjacencyLists[v] != nullptr) {
            int j = 0;

            // Loop through each edge in the adjacency list
            while (adjacencyLists[v][j].destination != 0) {
                // Print the destination vertex and edge weight
                cout << "(" << adjacencyLists[v][j].destination << ", " << adjacencyLists[v][j].weight << ")" << endl;
                // Move to the next edge in the list
                j++;
            }
        }

        // Print the predecessor value for the current vertex
        cout << "Predecessor: " << predecessor[v] << endl;
    }
}
