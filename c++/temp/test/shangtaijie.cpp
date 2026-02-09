#include<iostream>
//#include"judge.h"
using namespace std;
bool prime(int a) {
	for (int i = 2; i * i <= a; i++) {
		if (a % i == 0) {
			return 0;
		}

	}
	return 1;
}
bool plalindrome(int a) {
	int b = a;
	int res = 0;
	while (b > 0) {
		res = res * 10 + b % 10;
		b /= 10;
	}
	if (res == a)
		return 1;
	else return 0;
}
int main() {
	int a;
	cin >> a;
	cout<<prime(a)<<plalindrome(a);
	
}