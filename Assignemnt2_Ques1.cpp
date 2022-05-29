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
				vector<int> b;            // adding V vertices to graph
				adj.push_back(b);
			}
            for(int i=0; i<E; i++){
                int x, y;
                cin>>x>>y;                // adding E edges to graph
                x--; y--;
                adj[x].push_back(y);
            }
		}

};

bool rec_sort(graph &gh, int s, vector<bool> & visited, vector <bool> &inStack, stack <int> &st){
    visited[s] = true;
    inStack[s]=true;
    for(auto x: gh.adj[s]){
        if(!visited[x] && rec_sort(gh, x, visited,inStack, st))
        return true;
        else if(inStack[x]==true) return true;
    }
    inStack[s] = false;
    st.push(s);
    return false;
}

void Print(stack<int> &s){      // prints the vertices in topological order
    while(s.empty()==false){
        int x = s.top();
        s.pop();
        cout<<x+1<<" ";
    }
    cout<<endl;
}

void topological_sort(graph &gh){
    vector <bool> visited(gh.V, false);   // vector to check if node is already visited or not
    vector <bool> inStack(gh.V, false);    // vector to check if node is already in recursion stack
    stack <int> st;     // stack to store elements in topologicaal order
    bool flag = false;
    for(int i=0; i<gh.V; i++){
        if(!visited[i]) {
        flag = rec_sort(gh,i , visited, inStack, st);       //check if there is a topo. order poss or not by checking cycles in it
        if(flag)    break;      // break the loop if graph has one or more cycle
        }
    }
    if(flag) cout<<"IMPOSSIBLE";        //topological order not poss if there a cycle in graph
    else Print(st);     // Print elements in topological order
}

int main(){
    int n,m;    //n= number of vertices and m = number of edges
    cin>>n>>m;
    graph gh(n,m);    // initializing graph
    topological_sort(gh);
	return 0;
}
