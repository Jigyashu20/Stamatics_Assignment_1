// #include <iostream>
// #include <vector>
// #include <set>
// using namespace std;
 
// typedef pair<int, int> Edge;
 
// class Graph{
// public:
//     // a vector of vectors to represent an adjacency list
//     vector<vector<int>> adjList;
 
//     // Graph Constructor
//     Graph(vector<Edge> const &edges, int n)
//     {
//         // resize the vector to hold `n` elements of type `vector<int>`
//         adjList.resize(n);
 
//         // add edges to the undirected graph
//         for (auto &edge: edges)
//         {
//             adjList[edge.first].push_back(edge.second);
//             adjList[edge.second].push_back(edge.first);
//         }
//     }
// };
 
// // Perform DFS on the graph starting from vertex `v` and find
// // all bridges in the process
// int DFS(Graph const &graph, int v, vector<bool> visited, vector<int> &arrival,int parent, int &time, auto &bridges){
//     // set the arrival time of vertex `v`
//     arrival[v] = ++time;
 
//     // mark vertex as visited
//     visited[v] = true;
 
//     // initialize `t` with the arrival time of vertex `v`
//     int t = arrival[v];
 
//     // (v, w) forms an edge
//     for (int w: graph.adjList[v])
//     {
//         // if `w` is not visited
//         if (!visited[w]) {
//             t = min(t, DFS(graph, w, visited, arrival, v, time, bridges));
//         }
//         // if `w` is visited, and `w` is not a parent of `v`
//         else if (w != parent)
//         {
//             // If vertex `w` is already visited, there is a back edge starting
//             // from `v`. Note that as visited[u] is already
//             // true, arrival[u] is already defined
//             t = min(t, arrival[w]);
//         }
//     }
 
//     // if the value of `t` remains unchanged, i.e., it is equal
//     // to the arrival time of vertex `v`, and if `v` is not the root node,
//     // then (parent[v] —> v) forms a bridge
//     if (t == arrival[v] && parent != -1) {
//         bridges.insert({parent, v});
//     }
 
//     // return the minimum arrival time
//     return t;
// }
 
// set<Edge> findBridges(Graph const &graph, int n){
//     // to keep track of whether a vertex is visited or not
//     vector<bool> visited(n);
 
//     // stores arrival time of a node in DFS
//     vector<int> arrival(n);
 
//     int start = 0, parent = -1, time = 0;
 
//     set<Edge> bridges;
 
//     // As the given graph is connected, DFS will cover every node
//     DFS(graph, start, visited, arrival, parent, time, bridges);
 
//     return bridges;
// }
 
// void printEdges(auto const &edges){
//     for (auto const &edge: edges) {
//         cout << '(' << edge.first << ", " << edge.second << ") ";
//     }
// }
 
// // 2–edge connectivity in a graph
// int main(){
//     // vector of graph edges
//     vector<Edge> edges = {
//         {0, 2}, {1, 2}, {2, 3}, {2, 4}, {3, 4}, {3, 5}
//     };
 
//     // total number of nodes in the graph (0 to 6)
//     int n = 10;
 
//     // build a graph from the given edges
//     Graph graph(edges, n);
 
//     // find and print bridges
//     auto bridges = findBridges(graph, n);
 
//     if (bridges.size() != 0) {
//         cout << "Bridges are "; printEdges(bridges);
//     } else {
//         cout << "Graph is 2– Connected";
//     }
 
//     return 0;
// }

#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main(){
    multimap <int,int> m;
    m.insert(pair<int,int>(1,2));
    m.insert(pair<int,int>(3,2));
    m.insert(pair<int,int>(2,1));
    m.insert(pair<int,int>(3,1));
    m.insert(pair<int,int>(6,4));
    m.insert(pair<int,int>(6,5));
    m.insert(pair<int,int>(6,7));
    m.insert(pair<int,int>(6,1));
    m.insert(pair<int,int>(3,0));

    auto it = m.equal_range(3);
	for(auto itr = it.first ; itr!=it.second; itr++)
    cout<<itr->first<<" "<<itr->second<<endl;
    return 0;
}