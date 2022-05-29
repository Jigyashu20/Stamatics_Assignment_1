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

void recur_SCC(graph &gh,int s, vector<int> &low, vector<int> &id,  vector<bool> &inStack, stack<int> & st, int &count, vector<int> &ans){
    static int time = 0;
    st.push(s);     // updating the recursion stack
    id[s]=low[s]=++time;
    inStack[s] = true;   //mark element present in recursion stack
    for(auto u: gh.adj[s]){
        if(id[u]==-1){          // if not visited then recurse
            recur_SCC(gh, u, low, id, inStack, st, count , ans);
            low[s] = min(low[s], low[u]);       // update the low link value as min of two
        } 
        else{
            if(inStack[u]){
                low[s] = min(low[s], id[u]);
            }
        }
    }
    
    int w=0;
    if (low[s] == id[s]) {      // condition for an element to be 1st element of a SCC 
		while (st.top() != s){ 
			w =st.top(); 
			ans[w] = count; 
			inStack[w] = false; 
			st.pop(); 
		} 
		w = st.top(); 
		ans[w] = count;         // assign same value to all elements of a SCC
		inStack[w] = false;         // remove from recursion calll stack
		st.pop(); 
		count++;
	} 
    
    
}

void Print(vector <int> &v, int count){
    cout<<count<<endl;
    for(int x:v)
    cout<<x<<" ";
    cout<<endl;
}

void SCC(graph &gh){
    vector<int> id(gh.V, -1), low(gh.V, -1), ans(gh.V, -1);
    int count =1;
    stack<int> s;
    vector<bool> inStack(gh.V, false);
    for(int i=0; i<gh.V; i++){
        if(id[i]==-1)
        recur_SCC(gh, i, low, id, inStack, s, count, ans);
    }
    Print(ans, --count);
}

int main(){
    int n,m;
    cin>>n>>m;
    graph gh(n,m);
    SCC(gh);
	return 0;
}
