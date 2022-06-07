#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Union_Find{
    public:
    int V;
    vector<int> p, size, rank;
    Union_Find(int v){
        V = v;
        for(int i=0; i<=v; i++){
            p.push_back(i);
            size.push_back(1);          //initializing DSu with size 1 and rank 0
            rank.push_back(0);
        }
    }
    int Find(int v){
        if(v==p[v]) return v;   // return if it is it's own parent
        return p[v] = Find(p[v]);    // recursively shorten the depth by assigning parents of parent to it
    }


    void UnionByRank(int u, int v){
        int a = Find(u);
        int b = Find(v);
        if(a!=b){
            if(rank[a]>rank[b]) swap(a,b);      //append smaller ranked set
            p[a] = b;
            if(rank[a]==rank[b]) rank[b]++;  
        }
    }
    void UnionBySize(int u, int v){
        int a = Find(u);
        int b = Find(v);
        if(a!=b){
            if(size[a]>size[b]) swap(a,b);
            p[a] = b;           // append smaller sized set
            size[b] += size[a];         // increment the size
        }
    }
};

int main(){
    int n,q;
    cin>>n>>q;
    Union_Find Set(n);
    for(int i=0; i<q; i++){
        string s;
        int u, v;
        cin>>s>>u>>v;
        if(s=="union") Set.UnionByRank(u,v);
        else{
            if(Set.Find(u)==Set.Find(v)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    
    return 0;
}