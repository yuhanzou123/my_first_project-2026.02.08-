#include<iostream>
using namespace std;
int main(){
int k,n,w;
cin>>k>>n>>w;
int i =k*(w+1)*w/2;
if(i>n)cout<<i-n;
else if(i<=n)cout<<0;
return 0;
}