#include <iostream>
#include <vector>
#include <string>

// #include <bits/stdc++.h>
using namespace std;


class dsu{
public:    
    int n;
    vector<int> a, rank, size;
        dsu(int v){
            n = v; 
            a.resize(n); rank.resize(n); size.assign(n, 1);
            for(int i=0;i<n;i++){
                rank[i] = 1; a[i] = i;
            }
        }

        int Find(int v){
            if(v==a[v]) return v;
            return a[v] = Find(a[v]);
        }

        void UnionByRank(int u, int v){
        u = Find(u);
        v = Find(v);
        if(u!=v){
            if(rank[u]==rank[v]) rank[v]++;
            if(rank[u]>rank[v]) swap(u,v);
            a[u] = v;
            size[v] += size[u];
            
        }
    }

};

struct Edge{
int x, y;
};

struct query{
string s;
int x,y;
};


int main(){

    int n,m,k;
    cin>>n>>m>>k;
    Edge edge[m+1];
    query qt[k+1];
    for(int i=0;i<m;i++) cin>>edge[i].x>>edge[i].y ;    // input and store all edges
    for(int i=0;i<k;i++) cin>>qt[i].s>>qt[i].x>>qt[i].y;    // input and store all querries

    dsu dt(n);
    vector<string> ans;

    for(int i=(k-1);i>=0;i--){
        string qy=qt[i].s;
        int x=qt[i].x;
        int y=qt[i].y;      //traverse querries in reverse order as atlast all vertices are in diff sets
        x--,y--;
        if(qy=="ask"){
            if(dt.Find(x)==dt.Find(y)){
                ans.push_back("YES");

            }else{
                ans.push_back("NO");
            }
        }else{

            dt.UnionByRank(x,y);
        }
    }

    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]<<endl;
    }

return 0;
}
