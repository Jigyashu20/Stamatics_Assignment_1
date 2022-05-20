#include <bits/stdc++.h>
using namespace std;
class graph{
	public:
		int V ;
		vector<vector<int>> v;
		graph(int a){
			V = a;
			for(int i=0; i<V; i++){
				vector<int> b;
				v.push_back(b);
			}
		}
		
		void addEdge(int a, int b){
		    v[b].push_back(a);
		    v[a].push_back(b);
		}
		
		void addVertex(){
		    vector<int> vertex;
		    v.push_back(vertex);
		}
};

// 11111111111111111111111
void DFStime1(graph const &graph, int s, vector<bool> &discovered,vector<pair<int,int>> & tInOut, int &time){
    tInOut[s].first = ++time;
    discovered[s] = true;
    for (int i: graph.v[s]){
        if (!discovered[i]){
            DFStime1(graph, i, discovered, tInOut, time);
        }
    }
    tInOut[s].second = ++time;
    
    
}

void DFStime(graph const &graph, int s, vector<bool> &discovered,vector<pair<int,int>> & tInOut, int &time){
    for(int j=0; j<graph.v.size(); j++){
        if(!discovered[j]){ 
            int k=-1;
            DFStime1(graph, j, discovered, tInOut, k);}
    }
}

string typeTree(graph const &graph, int u, int v){
    int n = graph.v.size();
    vector<bool> discovered (n, false);
    vector<pair<int,int>> tInOut(n);
    int time = -1;
    DFStime(graph, 0, discovered, tInOut, time);
    if(tInOut[u].first < tInOut[v].first && tInOut[u].second > tInOut[v].second) return "Tree Edge";
    else if(tInOut[u].first > tInOut[v].first && tInOut[u].second < tInOut[v].second) return "Back Edge";
    else return "None";
}

// 2222222222222222222222222222
void BFS(graph &ab, int s, vector<int> &dist){
	vector<bool> visited(ab.v.size(), false); 
	queue<int>  q;
	dist[s] = 0;
	
	visited[s] = true; 
	q.push(s); 

	while(q.empty()==false){ 
		int u = q.front(); 
		q.pop();
		 
		for(int v: ab.v[u]){
		    if(visited[v]==false){
		        dist[v]=dist[u]+1;
		        visited[v]=true;
		        q.push(v);
		    }
		} 
	} 
} 

// 3333333333333333333333333333333333333
void connectedId1(graph &ab, int s, vector<int> &dist, int &id, vector<bool> &visited){
    queue<int>  q;
	dist[s] = id;
	visited[s] = true; 
	q.push(s); 
	while(q.empty()==false){ 
		int u = q.front(); 
		q.pop();
		 
		for(int v: ab.v[u]){
		    if(visited[v]==false){
		        dist[v]=id;
		        visited[v]=true;
		        q.push(v);
		    }
		} 
	} 
	id++;
}

void connectedId(graph &ab, vector<int> &dist, int id){
	vector<bool> visited(ab.v.size(), false); 
	for(int i=0; i<ab.v.size(); i++){
	    if(visited[i]==false)
	    connectedId1(ab, i, dist, id, visited);
	}
} 

// 444444444444444444444444444444444
bool DFSRec(graph &ab, int s, vector<bool> &visited, int parent){ 	
    visited[s]=true;    
    for(int u:ab.v[s]){
        if(visited[u]==false){
            if(DFSRec(ab, u,visited,s)==true)
                {return true;}}
        else if(u!=parent)
            {return true;}
    }
    return false;
	}

bool DFS(graph &ab){
    vector<bool> visited(ab.v.size(), false);
		
    for(int i=0;i<ab.v.size();i++){
        if(visited[i]==false)
            if(DFSRec(ab, i,visited,-1)==true)
                return true;
    }
    return false;
}

// 5555
int DFS5(graph const &gh, int s, vector<bool> visited, vector<int> &arrival,int parent, int &time, map<int, int> &bridges){
    arrival[s] = ++time;         // set the arrival time of vertex `s`
    visited[s] = true;      // mark vertex as visited
    int t = arrival[s];     // initialize `t` with the arrival time of vertex `s`
 
    
    for (int w: gh.v[s]){       // (s, w) forms an edge
        if (!visited[w]){       // if `w` is not visited
            t = min(t, DFS5(gh, w, visited, arrival, s, time, bridges));
        }
        
        else if (w != parent){      // if `w` is visited, and `w` is not a parent of `v`
            // If vertex `w` is already visited, there is a back edge starting
            // from `v`. Note that as visited[u] is already
            // true, arrival[u] is already defined
            t = min(t, arrival[w]);
        }
    }
    // if the value of `t` remains unchanged, i.e., it is equal
    // to the arrival time of vertex `v`, and if `v` is not the root node,
    // then (parent[v] —> v) forms a bridge
    if (t == arrival[s] && parent != -1){
        bridges.insert({s,parent});
    }
    return t;       // return the minimum arrival time
}

map<int , int> findBridges(graph const &gh, int n){
    // to keep track of whether a vertex is visited or not
    vector<bool> visited(n);
 
    // stores arrival time of a node in DFS
    vector<int> arrival(n);
 
    int start = 0, parent = -1, time = 0;
 
    map<int , int> bridges;
 
    // As the given graph is connected, DFS will cover every node
    DFS5(gh, start, visited, arrival, parent, time, bridges);
 
    return bridges;
}

void printEdges(map<int, int> const &edges){
    for (auto const &edge: edges) {
        cout << '(' << edge.first << ", " << edge.second << ") ";
    }
}
// 5555

int main(){
	int n=10;
// 	cin>>n;
	graph gh(n);
// 	gh.addEdge(0,1); 
	gh.addEdge(1,2); 
	gh.addEdge(2,3); 
	gh.addEdge(0,2); 
// 	gh.addEdge(1,3);
// gh.addEdge(0,2);
// gh.addEdge(8,0);
// gh.addEdge(8,4);
// gh.addEdge(1,5);
gh.addEdge(5,3);
gh.addEdge(2,4);
gh.addEdge(4,3);
	
// 	bool cycle = DFS(gh);
	
// 	vector<int> v(gh.v.size(), -1);
// 	BFS(gh, 0, v);
	
// 	vector<int> id(gh.v.size(), -1);
// 	connectedId(gh, id, 1);
// vector<bool> discovered (n, false);
// vector<pair<int,int>> tInOut(n);
// int time = -1;
// DFStime(gh, 0, discovered, tInOut, time);
// cout<<typeTree(gh, 5, 6)<<endl;
// cout<<typeTree(gh, 1, 6)<<endl;
// cout<<typeTree(gh, 7,3)<<endl;


// 55555555
auto bridges = findBridges(gh, gh.v.size());
printEdges(bridges);
// 5555555

// for(int i=0; i<n; i++){
//     cout<<tInOut[i].first<<" "<<tInOut[i].second<<endl;
// }
	
// 	cout<<cycle<<endl;
// 	for(int i=0; i<id.size(); i++){
// 	    cout<<id[i]<<" ";
// 	}
	return 0;
}
