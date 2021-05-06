#include <iostream>

using namespace std;

int result;

int some(int n, int m){
	if(n==1 || m==1) return 1;
	else return some(n, m-1) + some(n-1, m) + some(n-1, m-1);
}

int main(){
	cin.tie(0);
	int a, b;
	cin >> a >> b;

	result = some(a,b);

	cout << "Result: " << result << "\n";
	return 0;
}
