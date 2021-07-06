// 프로그램명: Algorithm Analysis Homework 6
// 주      제: Find all pair shortest path via Dijkstra and Floyd algorithm 
// 작  성  자: 21600343 서명준
// 작  성  일: 5/22 ~ 6/11

/* Reference list
 * (1). 강의 슬라이드 Chpater 24,25 Shortest Paths
 * (2). 다익스트라 알고리즘 참고 Blog: https://blog.encrypted.gg/918?category=773649
 * (3). 플로이드 알고리즘 참고 Blog: https://blog.encrypted.gg/917?category=773649
 * (4). 다익스트라 알고리즘 문제 https://www.acmicpc.net/problem/1753i
 * (5). stoi 함수구현 Blog: https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=milennium9&logNo=20194036012
 */

/* Comment
 1. According to homework description, it read input file name "hw6_data", not "hw6_data.txt".
 2. Run times of each algorithm was very small, so I computed a runtime via millisecond. 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstring>
#include <utility>
#include <queue>
#include <ctime>
#include <iomanip>

using namespace std;
using pii = pair<int, int>;

const int INF = 1e9+10;	

vector<pii> adj_list[31]; 
string itocity[31];
int f_map[31][31];
int d_map[31][31];	// 그래프를 모델링 하기위한 변수들

bool myStoi(const string& str, int& result){	// String을 Int값으로 변환해주는 함수
	string::const_iterator i = str.begin();
	if (i == str.end())
		return false;

	bool negative = false;

	if (*i == '-'){
		negative = true;
		++i;
		if (i == str.end())
			return false;
	}
	result = 0;

	for (; i != str.end(); ++i)
	{
		if (*i < '0' || *i > '9')
			return false;
		result *= 10;
		result += *i - '0';
	}

	if (negative){
		result = -result;
	}
	return true;
}

int getLine(const char *name){	// 파일의 line(node의수)를 구하기 위한 함수.
	int nodes=0;
	ifstream fp;
	fp.open(name);
	if(fp.is_open()){
		while(1){
			char temp;
			fp.get(temp);
			if(fp.eof()) break;
			if(temp == '\n') nodes++;
		} 
		fp.close();
	}
	else{
		cout << "File failed\n";
		exit(1);
	}
	return nodes-1;
}

int find_negative_edge(int nodes){	// negative edge의 여부를 탐색하는 함수.
	for(int i=0; i<nodes; i++){
		for(int j=0; j<nodes; j++){
			if(f_map[i][j] < 0){
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	int nodes;
	nodes = getLine("hw6_data");	// 위의 getLine함수를 이용해 노드의 수를 구하기
	ifstream fp;
	fp.open("hw6_data");

	if(fp.is_open()){	// 1. Read input file
		string temp;
		for(int i=0; i<nodes; i++){
			fp >> temp;
			itocity[i] = temp;
		}

		for(int i=0; i<nodes; i++){ // 2. Create 2D-array and adjacency list for a given  graph
			for(int j=0; j<nodes+1; j++){
				fp >>temp;
				int num;
				if(j==0) continue;
				d_map[i][j-1] = INF;	// Dijkstra를 위한 2D-array 초기화
				if(temp == "INF"){
					num = INF;
					f_map[i][j-1] = num; 
				}
				else{
					if(!myStoi(temp,num)) cout << "Cannot Convert\n";
					f_map[i][j-1] = num; // Floyd를 위한 2D-array 초기화
					if(num!=0)
						adj_list[i].push_back({num, j-1}); // Dijkstra를 위한 adjacency list

				}
			}
		}
		fp.close();
	}
	else{
		cout << "File failed\n";
		exit(1);
	}

	// 3. Dijkstra's Algorithm Implementation.
	int n_flag = find_negative_edge(nodes);	// negarive weighted edge 여부 확인
	
	if(n_flag == 0){
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		clock_t d_start = clock();
		for(int i=0; i<nodes; i++){	// |V|번 반복
			d_map[i][i] = 0;
			pq.push({d_map[i][i], i});
			while(!pq.empty()){	// Priority queue를 이용해 각 노드별 최단거리 를 d_map array에 저장
				auto cur = pq.top(); pq.pop();
				int dist = cur.first;
				int idx = cur.second;
				if(d_map[i][idx] != dist) continue;
				for(auto e : adj_list[idx]){
					int cost = e.first;
					int nidx = e.second;
					if(d_map[i][nidx] > dist + cost){
						d_map[i][nidx] = dist + cost;
						pq.push({d_map[i][nidx], nidx});
					}
				}
			}
		}
		clock_t d_end = clock();
		double d_time = (double)(d_end-d_start)/CLOCKS_PER_SEC * 1000 ;
	
		// Dijkstra Algorithm 결과 출력
		cout << "===================================Dijkstra==================================\n";
		cout << "It took " << d_time << " milliseconds to compute shortest path between cities with\nDijkstra's algorithm as follows\n";	

		cout << "          ";
		for(int i=0; i<nodes; i++)
			cout << itocity[i] << " ";
		cout << "\n";
		for(int i=0; i<nodes; i++){
			cout.setf(ios::left);
			cout << setw(10) << itocity[i];
			for(int j=0; j<nodes; j++){
				cout << setw(7) << d_map[i][j];
			}
			cout << "\n";
		}
		cout << "=============================================================================\n\n";
	}
	else{	// negative weighted edge가 존재하는 경우
		cout << "===================================Dijkstra==================================\n";
		cout << "There is(are) negative weight edge(s)!! \nDijkstra's Algorithm does not allow negative weight edge\n";
		cout << "=============================================================================\n\n";
	}
	

	// 4. Floyd Algorithm Implementation.	
	if(n_flag == 0){
		clock_t f_start = clock();
		for(int i=0; i<nodes; i++){
			for(int j=0; j<nodes; j++){
				for(int k=0; k<nodes; k++){
					f_map[j][k] = min(f_map[j][k], f_map[j][i] + f_map[i][k]);
				}
			}
		}	// for문을 돌며 f_map array 최적화
		clock_t f_end = clock();
		double f_time = (double)(f_end - f_start)/CLOCKS_PER_SEC * 1000;
		CL
		// Floyd Algotirhm 결과출력
		cout << "===================================Floyd=====================================\n";
		cout << "It took " << f_time << " milliseconds to compute shortest path between cities with\nFloyd algorithm as follows\n";	
		cout << "          ";
		for(int i=0; i<nodes; i++)
			cout << itocity[i] << " ";
		cout << "\n";
		for(int i=0; i<nodes; i++){
			cout << setw(10) << itocity[i];
			for(int j=0; j<nodes; j++){
				cout << setw(7) << f_map[i][j];
			}
			cout << "\n";
		}
		cout << "=============================================================================\n";
	}
	else{	// negative weighted cycle이 존재하는 경우
		cout << "===================================Floyd=====================================\n";
		cout << "There is(are) negative weight ctcle(s)!! \nFloyd Algorithm does not allow negative weight cycle\n";
		cout << "=============================================================================\n";
	}
	return 0;
}
