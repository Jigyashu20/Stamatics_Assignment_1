#include <bits/stdc++.h>
using namespace std;
class graph{
	public:
		int V, E ;   // number of vertices and edges in graph
		vector<vector<int>> adj;   // adjacency list representation of graph
		graph(int v, int e){
			V = v;
            E = e;
			for(int i=0; i<V; i++){
				vector<int> b;            // adding initial V vertices to graph
				adj.push_back(b);
			}
            for(int i=0; i<E; i++){
                int x, y;
                cin>>x>>y;                // adding initial E edges to graph
                x--; y--;
                adj[x].push_back(y);
            }
		}

};

void rec_sort(graph &gh, int s, vector<bool> & visited, vector <int> &st){
    visited[s] = true;
    for(auto x: gh.adj[s]){
        if(!visited[x] )
        rec_sort(gh, x, visited, st);      
    }
    st.push_back(s);
}

void Print(vector<int> &prev, int n){
    if(n==0){      // when curr poss is source
        cout<<n+1<<" ";
        return;
    }
    Print(prev, prev[n]);
    cout<<n+1<<" ";
    
}

vector<int> DFS(graph &gh){
    vector <bool> visited(gh.V, false);
    vector <int> vec;
    for(int i=0; i<gh.V; i++){
        if(!visited[i]) {
        rec_sort(gh,i , visited, vec);
        }
    }
    return vec;
}

void max_Dist(graph &gh, int source, int destination){
    vector <bool> visited(gh.V, false);
    vector <int> dist_max(gh.adj.size(),INT_MIN), prev_max(gh.V, -1);  // stores max distance and the node from where we rrives at curr node

    vector<int> vec = DFS(gh);
    dist_max[source] = 0;
    int k = gh.V-1;
    while(k>=0){
        int v=vec[k];
        for(int x:gh.adj[v]){
            if(dist_max[v]+1>dist_max[x]){
                dist_max[x] = dist_max[v]+1;                // take max of prev distance and new distance
                prev_max[x]=v;
            }
        }
        k--;
    }

    int a = dist_max[destination]+1;
    if(a<1) cout<<"IMPOSSIBLE"<<endl;
    else{
        cout<<a<<endl;
        Print(prev_max, destination);
        cout<<endl;
    } 
}

void min_Dist(graph &gh, int source, int destination){
    vector <bool> visited(gh.V, false);
    vector <int> dist_min(gh.V,INT_MAX), prev_min(gh.V, -1);

    vector<int> vec = DFS(gh);
    dist_min[source] = 0;
    int k = gh.V-1;
    while(k>=0){
        int v=vec[k];
        for(int x:gh.adj[v]){
            if(dist_min[v]+1<dist_min[x]){
                dist_min[x] = dist_min[v]+1;
                prev_min[x]=v;
            }
        }
        k--;
    }
    
    int a = dist_min[destination]+1;
    if(a<1) cout<<"IMPOSSIBLE"<<endl;
    else{                                    //min_dis
        cout<<a<<endl;
        Print(prev_min, destination);
        cout<<endl;
    } 
}

void CountPaths(graph &gh, int source, int destination){
    vector<int> vec = DFS(gh);   // topo_order of nodes
    vector<int> ans(gh.V, 0);
    ans[destination] = 1;
    for(int u:vec){
        for(int v:gh.adj[u])             //no. of paths
        ans[u] += ans[v];
    }
    cout<<ans[source]<<endl;
}

int main(){
    int n,m;
    cin>>n>>m;
    graph gh(n,m);
    int u=0, v = n-1;    // let source to be 1st and destination to be last node 
    max_Dist(gh, u, v);
    // min_Dist(gh, u, v);
    // CountPaths(gh, u, v);
	return 0;
}
