#include <bits/stdc++.h>
using namespace std;

class edge{
    public:
    int to, cost;
    edge(int x, int y){
        to = x;
        cost = y;
    }
};

class Graph{
    public:
    int V, E;
    vector<vector<edge>> e;
    Graph(int x, int y){
        V = x;
        E = y;
        e.resize(x);
        for(int i=0; i<y; i++){
            int a, b, c;
            cin>>a>>b>>c;
            a--; b--;
            edge ed(b,c);
            e[a].push_back(ed);
        }
    }
};

void solve(Graph &g){
    int n = g.V;
    vector<long long int> dist(n, LLONG_MAX), min_len(n, LLONG_MAX), max_len(n, LLONG_MIN), route(n,0);
    set<pair<long long int,int>> s;
    s.insert({0, 0});
    dist[0] = min_len[0] = max_len[0] = 0;
    route[0] = 1;
    while(s.empty()==false){
        int v = s.begin()->second;
        s.erase(s.begin());
        for (auto ed : g.e[v]) {
            int to = ed.to;
            int len = ed.cost;
            if (dist[v] + len < dist[to]) {
                s.erase({dist[to], to});
                route[to] = route[v];
                dist[to] = dist[v] + len;
                s.insert({dist[to], to});
                min_len[to] = min_len[v]+1;
                max_len[to] = max_len[v]+1;
            }else if(dist[v] + len == dist[to]){
                route[to]+=route[v];
                route[to] %= 1000000007;
                min_len[to] = min(min_len[to], min_len[v]+1);
                max_len[to] = max(max_len[to], max_len[v]+1);
            }
        }
    }
    
    cout<<dist[n-1]<<" "<<(route[n-1]%1000000007)<<" "<<min_len[n-1]<<" "<<max_len[n-1]<<endl;
}

int main() {
	int n, m;
	cin>>n>>m;
	Graph g(n,m);
	solve(g);
	return 0;
}
