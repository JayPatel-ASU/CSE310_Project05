
#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Extract graph filename and direction from command-line arguments
    string graphFilename = argv[1];
    string direction = argv[2];

    // Create an instance of the Graph class
    Graph* graph = new Graph();

    // Load the graph from the specified file
    if (!graph->loadGraph(graphFilename, direction)) {
        cout << "Failed to load the graph.\n";
        return 1;
    }

    // Process queries until the "stop" query is received
    while (true) {
        // Read the next query from the user

        string query;
        cin >> query;

        // Check the type of query
        if (query == "find") {
            // Read source, destination, and flag from user
            source, destination, flag = readInput()

            // Run Dijkstra's algorithm on the graph
            graph.runDijkstra(source, destination, flag)
        }

        //
        else if (query == "write"){
            // Read action, source, and destination from user
            action, source, destination = readInput()

            // Write the path based on the action
            graph.writePath(source, destination)
        }

        else if (query == "stop") {
            // Exit the program
            return 0;
        }

        else {
            // Invalid query, print an error message
            cout << "Invalid query. Please use 'find', 'write', or 'stop'.";
        }
    }

    return 0;
}
