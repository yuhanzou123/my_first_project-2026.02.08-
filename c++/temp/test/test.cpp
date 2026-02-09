#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int main(){
     int L,load=0,ans=0;
     cin>>L;
     for(int i =2;;i++){

        bool is_prime=1;
        for(int j =2;j*j<=i;j++)
if(i%j==0){
is_prime=0;
break;

}
if(!is_prime) continue;
if(load+i>L) break;
cout<<i<<endl;
load+=i;
ans++;


        }
        cout<<ans<<endl;
        return 0;
     }  


   
