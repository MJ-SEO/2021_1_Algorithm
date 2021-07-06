#include <iostream>
#include <algorithm>

using namespace std;

int n, m;

int main(){
	cin.tie(0);
	cin >> n >> m;
	
	int dp[n+1][m+1];
	
	for(int i=n; i>=1; i--){
		dp[i][1] = 1;
		
	
	for(int i=m; i>=1; i--){
		dp[1][i] = 1;
	}

	for(int i=2; i<=n; i++){
		for(int j=2; j<=m; j++){	
			dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1]; 
		}
	}

	cout << "Result: " << dp[n][m] << "\n";
	return 0;
}

