#include <iostream>
#include <vector>
using namespace std;

class BIT{
    int size;
    vector <long long int> vec;
    public: BIT(int n){
        size =n;
        for(int i=0; i<=n; i++) vec.push_back(0);
        for(int i=1; i<=n; i++){
            long long int k;
            cin>>k;
            Add(i,k);
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
    
    public: void setVal(int i, int k){
        long long int val = Sum(i,i);
        Add(i, k-val);
    }
    
};

int main() {
	// your code goes here
	
	int n, q;
	cin>>n>>q;
	BIT tree(n);
	for(int i=0; i<q; i++){
	    int a, b, c;
	    cin>>a>>b>>c;
	    if(a==1){
	        tree.setVal(b,c);
	    }else{
	        cout<<tree.Sum(b,c)<<endl;
	    }
	}

	return 0;
}
