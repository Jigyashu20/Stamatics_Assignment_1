#include <bits/stdc++.h>
using namespace std;
class graph{
	public:
		int V, E ;   // number of vertices and edges in graph
		vector<vector<int>> adj;   // adjacency list representation of graph
		vector<vector<int>> adj_t;   // transpose of adjacency list representation of graph
		graph(int v, int e){
			V = 2*v;
            E = 2*e;
			for(int i=0; i<V; i++){
				vector<int> b;            // adding initial V vertices to graph
				adj.push_back(b);
				adj_t.push_back(b);
			}
            for(int i=0; i<e; i++){
                int x, y;
                string s1, s2;
                cin>>s1>>x>>s2>>y;                // adding initial E edges to graph
                x--; y--;
                x*=2; y*=2;
                if(s1 == "-") x+=1;         // any node from 0-(n-1) is at 2*k and its negative at (2*k +1)
                if(s2 == "-") y+=1;
                int neg_x = x^1, neg_y = y^1;       //find index of negative x and y
                adj[neg_x].push_back(y);
                adj[neg_y].push_back(x);        // setting adj list
                adj_t[x].push_back(neg_y);
                adj_t[y].push_back(neg_x);// setting transpose of adj
            }
		}

};


void topo_sort(graph &gh, int s, vector <bool> &visited, vector<int> &topological_order){
    visited[s] = true;
    for(int x: gh.adj[s]){
        if(!visited[x])
        topo_sort(gh, x, visited, topological_order);
    }
    topological_order.push_back(s);
}

void component_assign(graph &gh, int j, int s, vector<int> &comp){
    comp[s] = j;
    for(int x: gh.adj_t[s]){
        if(comp[x]==-1)
        component_assign(gh, j, x, comp);
    }
}

void Print(vector<bool> &Ans){
    for(int i=0; i<Ans.size(); i++){
        if(!Ans[i])
        cout<<'-'<<" ";
        else
        cout<<'+'<<" ";
    }
    cout<<endl;
}

void SAT_2(graph &gh){
    int n = gh.V;
    vector<int> topological_order, comp(n, -1);  // vectors to store topo_order and component number
    vector <bool> visited(n, false), ans(n/2, false);  // vectors to track visit of a node and whether to assign true or false to a topping
    for(int i=0; i<n; i++){
        if(!visited[i]){
            topo_sort(gh, i, visited, topological_order);
        }
    }
    for(int i=0, j=0; i<n; i++){
        int v = topological_order[n-i-1];
        if(comp[v]==-1)
        component_assign(gh, j++, v, comp);
    }

    for(int i=0; i<n; i+=2){
        if(comp[i]==comp[i+1]){     // x and negation of x can't be equal, so impossible in this case
            cout<<"IMPOSSIBLE"<<endl;
            return;
        }else{
            ans[i/2] = comp[i]>comp[i+1];  
        }
    }
    Print(ans);
    
}


int main(){
    int n,m;
    cin>>n>>m;    // input number of vertices = 2*m , and number of edges 2*n
    graph gh(m,n);
    SAT_2(gh);
	return 0;
}
