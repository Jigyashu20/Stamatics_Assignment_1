#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    int V, E;
    vector<vector<int>> dist, p;
    Graph(int x, int y){
        V = x;
        E = y;
        dist.resize(x);
        p.resize(x);
        for(int i=0; i<x; i++){
            dist[i].insert(dist[i].begin(), x, INT_MAX);
            p[i].insert(p[i].begin(), x, -1);
        }
        for(int i=0; i<y; i++){
            int a, b, c;
            cin>>a>>b>>c;
            a--; b--;
            dist[a][b] = min(c, dist[a][b]);
            p[a][b] = b;
        }
    }
};

void constructPath(Graph &g, int u,int v){
    // If there's no path between
    // node u and v, simply return
    // an empty array
    if (g.p[u][v] == -1)
        return ;
 
    // Storing the path in a vector
    while (u != v) {
        cout<<u<<" ";
        u = g.p[u][v];
    }
    cout<<u<<" ";
}

void edit(Graph &g, int u, int v, int decrement){
    for(int i=0; i<g.V; i++){
        for(int j=0; j<g.V; j++){
            // if there is an edge uv in path from i to j then update the dist
            if(g.dist[i][u] != INT_MAX && g.p[u][j] == v) g.dist[i][j] -= decrement;
        }
    }
}

// solve for distance and path matrices using floyd warshall method
void solve(Graph &g){
   for(int k=0; k<g.V; k++)
   for(int i=0; i<g.V; i++)
   for(int j=0; j<g.V; j++){
       if (g.dist[i][k] < INT_MAX && g.dist[k][j] < INT_MAX)
                if(g.dist[i][j]> g.dist[i][k] + g.dist[k][j]){
                    g.dist[i][j]= g.dist[i][k] + g.dist[k][j];
                    g.p[i][j] = g.p[i][k];
                }
   }
}

int main() {
	int n, m;
	cin>>n>>m;      //no. of vertices and edges
	Graph g(n,m);
	solve(g);    // solving for distance and path matrices
    cout<<"Enter the vertices of edge and it's new weight"<<endl;
    int u, v, w;
    cin>>u>>v>>w;
	// constructPath(g, u, v);          // prints the SSSP between two vertices u and v
    // cout<<g.dist[x][y];              // outputs distance between x and y before update
    edit(g, u, v, g.dist[u][v]-w);                   //Changes the weight of an edge
    // cout<<g.dist[x][y];              // outputs distance between x and y after update
	return 0;
}