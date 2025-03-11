#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.resize(numVertices, -1);
    
    distances[source] = 0;
    previous[source] = -1;


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap; // pair<weight, vertex>
    minHeap.push(pair{0, source});

    while(!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();
        if (visited[u]) {continue;}
        visited[u] = true;
        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push(pair{distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    stack<int> initial_result;
    vector<int> result;
    for (int i = destination; i != -1; i = previous[i]) {
        initial_result.push(i);
    }

    while (!initial_result.empty()) {
        result.push_back(initial_result.top());
        initial_result.pop();
    }
    return result;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v) {
        cout << vertex << ' ';
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}