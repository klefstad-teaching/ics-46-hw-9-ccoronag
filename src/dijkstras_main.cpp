#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("../src/small.txt", G);
    // cout << "done filling up graph" << endl;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    // cout << "done getting the distances" << endl;
    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> shortest = extract_shortest_path(distances, previous, i);
        cout << "done extracting from distances" << endl;
        print_path(shortest, 0);
    }
}