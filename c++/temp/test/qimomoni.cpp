#include <iostream>
#include <iomanip>
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
struct  zifu
{
	string c;
	int b[256]={0};
};
struct  zifu1
{   
	string c1;
	int a[256]={0};
	int sum=0;
};
struct ing{
	char mak;
	int in;
};
bool cmp(zifu1& z1,zifu1& z2){
	return z1.c1.size()<z2.c1.size();
}
bool cmp1(ing& i1,ing& i2){
	if(i1.in!=i2.in){
		return i1.in>i2.in;
	}
	else return i1.mak<i2.mak;
	
}
int main(){
	int n;
	cin>>n;
	while(n--){
string t,s;
cin>>t;
cin>>s;
zifu m;
m.c=t;
vector<zifu1> v;
for(int i=0;i<t.size();i++){
	m.b[t[i]]++;
}
for(int i=0;i<s.size();i++){
	for(int j=0;j<=i;j++){
    string s1=s.substr(j,i-j+1);
	zifu1 s2;
	s2.c1=s1;
	v.push_back(s2);
	}
}
for(int i=0;i<v.size();i++){
	for(int j=0;j<v[i].c1.size();j++){
       v[i].a[v[i].c1[j]]++;
	}
}
bool flag=true;
vector<zifu1> qt;
for(int i=0;i<v.size();i++){
	
	for(int j=0;j<256;j++){
		if(v[i].a[j]<m.b[j]){
			flag=false;
			break;
		}
	}
	if(flag){
		qt.push_back(v[i]);
	}
	flag=true;
}
if(!qt.empty()){
	sort(qt.begin(),qt.end(),cmp);
	cout<<qt[0].c1<<endl;
}
else{
	int se[256]={0};
	for(int i=0;i<s.size();i++){
		se[s[i]]++;
	}
	vector<ing> l(s.size());
	for(int i=0;i<s.size();i++){
		l[i].mak=s[i];
		l[i].in=se[l[i].mak];
	}
sort(l.begin(),l.end(),cmp1);
for(int i=0;i<l.size();i++){
cout<<l[i].mak;
}
cout<<endl;
}

}
}
