// 프로그램명: Algorithm Analysis Homework 4           
// 주      제: Greedy, Dynamic Programmin, Branch & Bound 알고리즘을 이용한 Knapsack problem 풀이
// 작  성  자: 21600343 서명준               
// 작  성  일: 4/27 ~ 5/12 

/* Reference list
   (1). 강의 slice chapter 16 - Knapsack Problem
   (2). 백준 12865번 문제 평범한 배낭 https://www.acmicpc.net/problem/12865
   (3). C++ 랜덤함수 난수생성기 https://arer.tistory.com/10
   (4). B&B algorithm 참고 https://www.geeksforgeeks.org/implementation-of-0-1-knapsack-using-branch-and-bound/
   (5). C++ 출력형태 정리 https://blog.naver.com/PostView.nhn?blogId=lyw94k&logNo=220848917877
   (6). C++ vector 사용법 https://www.geeksforgeeks.org/vector-erase-and-clear-in-cpp/
   (7). C++ STL(priortiry queue) 사용법https://developingbear.tistory.com/58
   (8). C++ 파일 입출력 https://mintyu.github.io/cpp12/
*/

// Comment - My program works for all of algorithms(Greedy, DP, B&B)

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <tuple>
#include <utility>
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;

int n_items[8] = {100, 1000, 2000, 4000, 6000, 8000, 10000, 12000}; 
int result[8][6];  // 결과 출력을 위한 배열
vector <pair<double, int>> result;
vector <pair<int, int>> item_table;   // item의 정보를 저장하기 위한 vector

bool cmp(pair<int, int> a, pair< int, int> b){				
	return (double)b.second/b.first < (double)a.second/a.first;	
}						// 배낭안의 item들을 정렬하기 위한 함수

void show_result(){	// 결과를 출력하기 위한 함수
	ofstream fout("text.txt");
	cout << "Result(Processing time in miliseconds / Maximum benefit value)\n";
	fout << "Result(Processing time in miliseconds / Maximum benefit value)\n";
	cout << "                               Greedy               DP                B&B\n";
	fout << "                               Greedy               DP                B&B\n";
	for(int i=0; i<8; i++){
		cout << "Number of Items(" << n_items[i] << ")    ";
		fout << "Number of Items(" << n_items[i] << ")    ";
	        if(i<1){
		       	cout << "  ";
			fout << "  ";
		}
		else if(i<6){
		       	cout << " ";	
			fout << " ";
		}
		int flag = 0;
		for(int j=0; j<6; j++){
			cout.setf(ios::left);
			fout.setf(ios::left);
			cout << setw(9) << result[i][j];
			fout << setw(9) << result[i][j];
			if(j%2 == 0){
			       	cout << "/";
				fout << "/";
			}
		}
		cout << "\n";
		fout << "\n";
	}
}

void show_table(int items){	// item_table의 내용을 확인하기 위한 디버깅용  함수
	for(int k=0; k<items; k++){
		cout << k+1 << " " << item_table[k].first << " " << item_table[k].second ;
		cout << "\n";
	}
}

double greedy(int num_items, int max_weight, int idx){	// Greedy algorithm
	clock_t start = clock();
//	cout << "=============Greedy==============\n";
//	show_table(num_items);
	int weight_sum = 0;
	double optimal = 0;

	for(int i=0; i<num_items; i++){
		if((weight_sum + item_table[i].first <= max_weight)){
			optimal += item_table[i].second;
			weight_sum += item_table[i].first;
		}
		else{
			optimal += (double)(max_weight-weight_sum)/item_table[i].first * item_table[i].second;
			break;
		}
	}	//	알고리즘 구현 부분, main함수에서 item정렬 후 greedy알고리즘 적용
	
	result[idx][1] = (double)optimal; 	
	clock_t end = clock();	
	return	(double)(end - start)/CLOCKS_PER_SEC * 1000;
}

double DP(int num_items, int max_weight, int idx){	// Dynamic Progrmming
	clock_t start = clock();
//	cout << "===============DP================\n";
//	show_table(num_items);
	int **knap = (int**)malloc(sizeof(int*) * num_items+1);
	for(int i=0; i<3; i++){
		knap[i] = (int*)malloc(sizeof(int) * max_weight +1);
	}

	for(int i=0; i<=max_weight ; i++){
		knap[0][i] = 0;
	}
		
	for(int i=1; i <= num_items; i++){
		if(i>2){	// 실제 사용될 메모리만을 할당 및 사용하지 않는 메모리 free
			knap[i] = (int*)malloc(sizeof(int) * max_weight+1);
			free(knap[i-3]);
		}
		knap[i][0] = 0;
		for(int j=1; j <= max_weight; j++){
			if(j >= item_table[i-1].first){
				if(item_table[i-1].second + knap[i-1][j-item_table[i-1].first] > knap[i-1][j]){
					knap[i][j] = item_table[i-1].second + knap[i-1][j-item_table[i-1].first];
				}
				else{
					knap[i][j] = knap[i-1][j];
				}
			}
			else{
				knap[i][j] = knap[i-1][j];
			}
		}
	}	// DP알고리즘, 수업 PPT참조

	for(int i= num_items-2; i<=num_items; i++){
		free(knap[i]);
	}
	free(knap);

//	cout << "DP result: " << knap[num_items][max_weight] << "\n";
	result[idx][3] = (double)knap[num_items][max_weight];

	clock_t end = clock();	
	return (double)(end - start)/CLOCKS_PER_SEC * 1000;
}

struct node_t{
	int level;
	int benefit;
	int weight;
	double bound;
};	// B&B 알고리즘을 위한 Struct 선언

struct cmp2{
	bool operator()(node_t &a, node_t& b){
		return b.bound > a.bound;
	}
};	// priority que의 정렬기준을 위한 함수 Reference(7) 참조

double get_bound(node_t node, int node_number, int num_items, int max_weight){	// bound 값 구하기
	int weight_sum = 0;
	double optimal = 0;
	int i=0, j=0;

	optimal = node.benefit;
	weight_sum = node.weight;
	
	for(int i=node.level+1; i<num_items; i++){
		if((weight_sum + item_table[i].first <= max_weight)){
			optimal += item_table[i].second;
			weight_sum += item_table[i].first;
		}
		else{
			optimal += (double)(max_weight-weight_sum)/item_table[i].first * item_table[i].second;
			break;
		}
	}	// 그리디와 같은 알고리즘
	return optimal;
}

void show_node(node_t n){	// node의 상태를 보여주는 디버깅용 함수
	cout << "DEBUG node: "<< n.weight << " " << n.benefit << " " << n.bound << "\n";
}

double branch_bound(int num_items, int max_weight, int idx){	// Branch and Bound
//	cout << "==============B&B===============\n";
//	show_table(num_items);
	clock_t start = clock();
	int max_benefit = 0;
		
	priority_queue<node_t, vector<node_t>, cmp2> pq; // priority que 사용 Reference(7)참조
	node_t init;
	init.level = -1, init.benefit = 0, init.weight = 0; 
	init.bound = get_bound(init, init.level, num_items, max_weight);
	pq.push(init);	// 초기 노드 선언 및 push(enqueue)

	node_t new_node;;
	while(!pq.empty()){
		node_t pro_node = pq.top(); pq.pop();
		if(pro_node.bound > max_benefit){ 
			new_node.level = pro_node.level+1;
			new_node.weight = pro_node.weight + item_table[new_node.level].first;
			new_node.benefit = pro_node.benefit + item_table[new_node.level].second;
			// N 번째 노드를 넣는 경우(left)
		
			if (new_node.weight <= max_weight && new_node.benefit > max_benefit){
				max_benefit = max(new_node.benefit, max_benefit);
			}

			new_node.bound = get_bound(new_node, new_node.level, num_items, max_weight);
			if(new_node.bound > max_benefit && new_node.weight <= max_weight){
				pq.push(new_node);
			}
			
			// N번째 노드를 넣지 않는 경우(right)	
			new_node.weight = pro_node.weight;
			new_node.benefit = pro_node.benefit;
			new_node.bound = get_bound(new_node, new_node.level, num_items, max_weight);
			if(new_node.bound > max_benefit && new_node.weight <= max_weight){
				pq.push(new_node);
			}
		}
	}	// B&B 알고리즘, 강의 PPT 및 Reference(4)참조

//	cout << "BB result: " << max_benefit << "\n";
	result[idx][5] = (double)max_benefit;
	
	clock_t end = clock();
	return (double)(end - start)/CLOCKS_PER_SEC * 1000;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int)time(NULL));

	for(int i=0; i<8; i++){		// itme수 100 부터 12000 까지 총8번 시행
		int items = n_items[i];	
		int max_weight = n_items[i] * 40;
		for(int j=0; j<items; j++){
			item_table.push_back({(rand()%100) + 1, (rand()%300) + 1});
		}	// 위에서 선언한 vector table에 값 삽입 
		
//		result[i][2] = DP(items, max_weight, i);
		sort(item_table.begin(), item_table.end(), cmp); // Greedy, B&B를 위한 sorting
						   // 각 item의 value/weight를 기준으로 soring 
		result[i][0] = greedy(items, max_weight, i);
		result[i][4] = branch_bound(items, max_weight, i);

		item_table.erase(item_table.begin(), item_table.end());
	}
	show_result();	
	return 0;
}

