// 프로그램명: Algorithm Analysis Homework 4           
// 주      제: Greedy, Dynamic Programmin, Branch & Bound 알고리즘을 이용한 Knapsack problem 풀이
// 작  성  자: 21600343 서명준               
// 작  성  일: 4/27??? ~ 5/12 

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
// #include <file>

using namespace std;

int result[8][6];
int n_items[8] = {100, 1000, 2000, 4000, 6000, 8000, 10000, 12000};

int item_table[12010][3];
int knap[2010][80010] = {0};

bool cmp(pair<int, double> a, pair<int, double> b){
	return b.second < a.second;
}

void show_result(){        // print result
	cout << "Result(Processing time in miliseconds / Maximum benefit value)\n";
	cout << "                          Greedy         DP          B&B\n";
	for(int i=0; i<8; i++){
		cout << "Number of Items(" << n_items[i] << ")    "; 
		int flag = 0;
		for(int j=0; j<6; j++){
			if(j%2 == 0 && j!=0) cout << "     ";
			cout << result[i][j];
			if(j%2 == 0) cout << "/";
		}
		cout << "\n";
	}
}

void show_table(int items){
	for(int k=0; k<=items; k++){
		for(int m=0; m<3; m++){
			cout << item_table[k][m] << " " ;
		}
		cout << "\n";
	}
}

int greedy(int n_items, int max_weight, int idx){
	clock_t start = clock();
	int item_arr[n_items];
	int weight_sum = 0;
	int optimal = 0;

	vector<pair<int, double>> temp;
	for(int i=1; i<=n_items; i++){
		temp.push_back({i, (double)item_table[i][2]/item_table[i][1]});	
	}
	
	sort(temp.begin(), temp.end(), cmp);

	for(int i=0; i<5; i++){
		cout << temp[i].first << " " << temp[i].second  << "\n";
	}


	for(int i=0; i<n_items; i++){	
		if(weight_sum < max_weight){
			optimal += item_table[temp[i].first][2];
			weight_sum += item_table[temp[i].first][1];
		}
		else if(weight_sum == max_weight){
			break;
		}
		else{
			optimal += (max_weight-weight_sum) * item_table[temp[i].first][2];
			break;
		}
	}
	
	result[idx][1] = optimal; 	
	clock_t end = clock();
	return (int)end-start;
}

int DP(int n_items, int max_weight, int idx){
	clock_t start = clock();
/*	int **knap = (int**)malloc(sizeof(int*) * n_items + 10);
	for(int i=0; i<n_items; i++){
		knap[i] = (int*)malloc(sizeof(int) * max_weight + 10);
	}	
*/
	for(int i=1; i<= n_items; i++){
		for(int j=1; j<= max_weight; j++){
			if(j >= item_table[i][1]){
				if(item_table[i][2] + knap[i-1][j-item_table[i][1]] > knap[i-1][j]){
					knap[i][j] = knap[i-1][j-item_table[i][1]] + item_table[i][2];
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
	
	result[idx][3] = knap[n_items][max_weight];

/*	for(int i =0; i < n_items; i++){
		free(knap[i]);
	} 
	free(knap); */
	clock_t end = clock();
	return (int)end-start;
}

int branch_bound(int n_items, int max_weight, int idx){
	clock_t start = clock();
	
	
	clock_t end = clock();
	return (int)end-start;
}


int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int)time(NULL));

	for(int i=0; i<1; i++){
		int items = n_items[i];
		int max_weight = n_items[i] * 40;
		cout << "[DEBUG] items, max: " << items << " " << max_weight << "\n";
		for(int j=1; j<=items; j++){
			item_table[j][0] = j;                // item index
			item_table[j][1] = (rand()%100) + 1; // item weight with random
			item_table[j][2] = (rand()%300) + 1; // item value with random
		} // TODO pair or tuple

//		show_table(items);
		result[i][0] = greedy(items, max_weight, i);
		result[i][2] = DP(items, max_weight, i);
//		result[i][4] = branch_bound(items, max_weight, i);
	}

	show_result();	
	return 0;
}

/* Reference list
   (1). 강의 slice chapter 16 - Knapsack Problem
   (2). 백준 12865번 문제 평범한 배낭 https://www.acmicpc.net/problem/12865
   (3). C++ 랜덤함수 난수생성기 https://arer.tistory.com/10
   */
