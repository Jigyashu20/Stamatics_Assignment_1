#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Union_Find{
    public:
    int V;
    vector<int> p, size;
    vector<pair<int, pair<int, int>>> vec;
    Union_Find(int v, int q){
        V = v;
        for(int i=0; i<=v; i++){
            p.push_back(i);   //initially parent of each vertex is the vertex itself
            size.push_back(1);     //initial size =1
        }
        int a,b,w;
        for(int i=0; i<q; i++){
            cin>>a>>b>>w;
            vec.push_back({w, {a,b}});   // input edges with weight
        }
        sort(vec.begin(), vec.end());   // sorting wrt weight of edges
    }

    int Find(int v){
        if(v==p[v]) return v;
        return p[v] = Find(p[v]);
    }
    void UnionBySize(int u, int v){
        int a = Find(u);
        int b = Find(v);
        if(a!=b){
            if(size[a]>size[b]) swap(a,b);
            p[a] = b;
            size[b] += size[a];
        }
    }
    long long int Minimum_Span(){
        long long int weight=0;
        for(int i=0; i<vec.size(); i++){
            int a = vec[i].second.first, b = vec[i].second.second;
            // cout<<2;
            if((Find(a))!=(Find(b))){   // if two vertices are in diff set, take a union
                UnionBySize(a,b);
                weight += vec[i].first;
            }
            if((size[Find(a)])==V  || V==(size[Find(b)])) break;
        }
    return weight;
  }
};

int main(){
    int n,q;
    cin>>n>>q;
    Union_Find Set(n, q);
    cout<<Set.Minimum_Span();    
    return 0;
}