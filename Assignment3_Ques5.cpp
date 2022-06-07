#include <iostream>
#include <vector>
using namespace std;

class BIT{
    int size;
    vector <long long int> vec;
    public: BIT(int n){
        size =n;
        for(int i=0; i<=n; i++)  vec.push_back(0);
        for(int i=1; i<=n; i++){
            long long int k;
            cin>>k;
            RangeUpdate(i,i,k);
        }
    }
    
    long long int LSB(int i){
        return i&(-i);
    }
    
    long long int prefixSum(int i){
        long long int sum =0;
        while(i>0){
            sum += vec[i];
            i -= LSB(i);     // Equivalent to : i &= ~LSB(i)
        }
        return sum;
    }
    
    public: long long int Sum(int i, int j){
        return prefixSum(j) - prefixSum(i-1);
    }
    
    void Add(int i, long long int k){
        while(i<vec.size()){
            vec[i]+=k;
            i+=LSB(i);
        }
    }
    
    public: void RangeUpdate(int i, int j, long long int k){
        Add(i, k);
        Add(j+1, -k);
    }
    
};

int main() {
	// your code goes here
	
	int n, q;
	cin>>n>>q;
	BIT tree(n);
	for(int i=0; i<q; i++){
	    int a;
	    cin>>a;
	    if(a==1){
	        int b, c, d; cin>>b>>c>>d;
	        tree.Add(b,d);
	        tree.Add(c+1,-d);
	    }else{
	        int b; cin>>b;
	        cout<<tree.Sum(1,b)<<endl;
	    }
	}

	return 0;
}
