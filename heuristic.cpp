#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <iostream>
#include <sstream>

using namespace std;

// Function to calculate barycenter values
vector<int> barycenterHeuristic(const vector<int>& fixedVertices, const vector<int>& permutedVertices, const vector<pair<int, int>>& edges) {
    unordered_map<int, vector<int>> adjacencyList;
    for (const auto& v : permutedVertices) {
        adjacencyList[v] = vector<int>();
    }
    for (const auto& edge : edges) {
        if (adjacencyList.find(edge.second) != adjacencyList.end()) {
            adjacencyList[edge.second].push_back(edge.first);
        }
    }

    unordered_map<int, double> barycenters;
    for (const auto& vertex : permutedVertices) {
        if (!adjacencyList[vertex].empty()) {
            double sum = 0;
            for (const auto& neighbor : adjacencyList[vertex]) {
                sum += find(fixedVertices.begin(), fixedVertices.end(), neighbor) - fixedVertices.begin();
            }
            barycenters[vertex] = sum / adjacencyList[vertex].size();
        } else {
            barycenters[vertex] = -1;
        }
    }

    vector<int> sortedVertices = permutedVertices;
    sort(sortedVertices.begin(), sortedVertices.end(), [&barycenters](int a, int b) {
        return barycenters[a] < barycenters[b];
    });

    return sortedVertices;
}

struct Input
{
    vector<pair<int, int>> edges;
    int movable;
    int fixed;
};
Input inputGraphEdges()
{
    int num_vertices, n0, n1;
    vector<pair<int, int>> edges;
    string line;

    while (getline(cin, line))
    {
        if (line.empty() || line[0] == 'c')
            continue;

        if (line[0] == 'p')
        {
            istringstream iss(line);
            string discard;
            iss >> discard >> discard >> n0 >> n1;
            continue;
        }

        istringstream iss(line);
        int u, v;
        iss >> u >> v;
        edges.emplace_back(u, v);
    }

    Input in;
    in.edges = edges;
    in.fixed = n0;
    in.movable = n1;
    return in;
}

int main() {
    Input i = inputGraphEdges();

    vector<int> fixedVertices;
    for(int a=1 ; a<= i.fixed ; a++)
        fixedVertices.push_back(a);

    vector<int> permutedVertices;
    for(int a=i.fixed+1 ; a<= i.movable + i.fixed ; a++)
        permutedVertices.push_back(a);

    vector<pair<int, int>> edges = i.edges;

    vector<int> initialOrder = barycenterHeuristic(fixedVertices, permutedVertices, edges);

    for(auto i : initialOrder)
        cout<<i<<endl;
}