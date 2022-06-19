#include <bits/stdc++.h>
using namespace std;

// Define edge with vertices a,b and weight=cost 
class edge{
    public:
        int a, b;
        long long int cost;         
        edge(int x, int y, long long int c){
            a = x;
            b = y;
            cost = c;
        }
};
 
// vector e stores all the edges of graph 
vector<edge> e;
int v =0;

// returns maximum value  
long long maxi(long long int a){
    if(INT_MIN>a) return INT_MIN;
    return a;
    
}
 
// Prints the output 
void Print(int x, int n, vector<int> &p){
    if (x == -1)
        cout << "NO";
    else{
        int y = x;
        for (int i=0; i<n; ++i)
            y = p[y];
 
        vector<int> path;
        for (int cur=y; ; cur=p[cur]){
            path.push_back (cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse (path.begin(), path.end());
 
        cout << "YES"<<endl;
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i]+1 << ' ';
    }
    cout<<endl;
}

void solve(int n){
    int m = e.size();       // number of edges in graph
    vector<long long int> d (n, 0);     //distance array/vector
    vector<int> p (n - 1);      //parent vector
    int x;
    for (int i=0; i<n; ++i){
        x = -1;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INT_MAX)
                if (d[e[j].b] > d[e[j].a] + e[j].cost){
                    d[e[j].b] = maxi(d[e[j].a] + e[j].cost);
                    p[e[j].b] = e[j].a;
                    x = e[j].b;
                }
    }
    Print(x, n, p);
 
}
 
int main(){
	int n, m;
	cin>>n>>m;
	for(int i=0; i<m; i++){
	    int a, b;
	    long long int c;
	    cin>>a>>b>>c;
	    edge ed(a-1, b-1, c);           //Pass 1-based input as 0-based
	    e.push_back(ed);
	}
	
	solve(n);
	return 0;
}