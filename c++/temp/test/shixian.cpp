# include "judge.h"
# include <iostream>
using namespace std;
int main()
{
	int cnt1=0, cnt2=0, a;
	while(cin>>a)
	{
		if (prime(a))
			cnt1++;
		
		if (plalindrome(a))
			cnt2++;
	}
	cout<<cnt1<<" "<<cnt2<<endl;
	
	return 0;
}