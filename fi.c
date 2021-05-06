#include <stdio.h>

long long dp[50];

void dp_fi(int n){
	dp[0] = 0; 
	dp[1] = 1;

	for(int i=2; i<=n; i++){
		dp[i] = dp[i-1] + dp[i-2];
	}

	printf("%lld", dp[n]);
}

int main(){
	long long res;

	int n;
	scanf("%d", &n);

	dp_fi(n);
}
