#include <iostream>
#include <algorithm>

using namespace std;

int item[1000][3];
int knap[105][100500];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	int items, W;
	cin >> items >> W;

	for(int i=1; i<=items; i++){
		int w, v;
		cin >> w >> v;
		item[i][0] = i;
		item[i][1] = w;
		item[i][2] = v;
	}

	for(int i=1; i<=items; i++){
		for(int j=1; j<=W; j++){
			if(j >= item[i][1]){
				if(item[i][2] + knap[i-1][j-item[i][1]] > knap[i-1][j]){
					knap[i][j] = knap[i-1][j-item[i][1]] + item[i][2];
				}	
				else{	
					knap[i][j] = knap[i-1][j];
				}
			}
			else{
				knap[i][j] = knap[i-1][j];
			}
		}
	}

	for(int i=0; i<=items; i++){
		for(int j=0; j<=W; j++){
			cout << knap[i][j] << " ";
		}
		cout << "\n";
	}


	cout << knap[items][W] << "\n";
	return 0;
