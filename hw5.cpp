// 프로그램명: Algorithm Analysis Homework 5
// 주      제: Transposed adjaency graph
// 작  성  자: 21600343 서명준
// 작  성  일: 5/16 ~ 5/28

/* Reference list
 * (1). c++ 파일 입출력 Blog: https://blockdmask.tistory.com/322 
 * (2). Transpose matrix Blog: https://inhwascope.tistory.com/59
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

int adj_array[21][21];
int trans_array[21][21];
vector<int> adj_list[21];
vector<int> trans_list[21];

char itoc(int n){	// 배열의 int 값을 알파벳으로 전환해주는 함수(0~20) >> (A ~ T)
	char temp;
	temp = 'A'+ n;
	return temp;
}			

int getLine(const char *name){	// 파일의 line(node의 수)를 구하기 위한 함수.
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

void transpose(int nodes){	// 기존 인접행렬, 리스트의 Transposed graph를 구하는 함수.
	for(int i=0; i<nodes; i++){
		for(int j=0; j<nodes; j++){
			trans_array[j][i] = adj_array[i][j];
		}
	}	

	for(int i=0; i<nodes; i++){
		for(int j=0; j<nodes; j++){
			if(trans_array[i][j] == 1){
				trans_list[i].push_back(j);
			}
		}
	}	
	
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	int nodes;
	nodes = getLine("hw5_data.txt");	// 위의 getLine함수를 이용해 노드의 수를 구하기

	ifstream fp;
	fp.open("hw5_data.txt");

	if(fp.is_open()){	// file open확인
		int x = 0;
		int y = 0;
		while(!fp.eof()){	// file이 끝날떄까지 반복
			char temp;
			fp.get(temp);
			if(isdigit(temp)){	// file속 character가 숫자이면
				if(y == nodes) {// y값(x좌표)가 노드의 수와 같아지면 다음 row로 이동
					x++;
					y = 0;
				}
				adj_array[x][y] = temp - 48;	
				if(temp - 48 == 1){
					adj_list[x].push_back(y);
				}	
				y++;		// 인접행렬, 리스트에 값 추가 후 y값(x좌표) +1
			}
		} 
		fp.close();
	}
	else{
		cout << "File failed\n";
		exit(1);
	}

	cout << "======Original adjlist=======\n";

	
	for(int i=0; i<nodes; i++){
		for(int j=0; j<nodes; j++){
			cout << adj_array[i][j] << " ";
		}
		cout << "\n";
	}
	
	cout << "=============================\n";

	for(int i=0; i<nodes; i++){
		cout << itoc(i) << ": ";
		for(int j=0; j<adj_list[i].size(); j++){
			if(j != adj_list[i].size()-1)
				cout << "[" << itoc(adj_list[i][j]) << "]" << "->";
			else
				cout << "[" << itoc(adj_list[i][j]) << "]" << " ";

		}
		cout << "\n";
	}	// Original 인접리스트 출력 

	transpose(nodes);	// transpose 진행

	cout << "======Transposed adjlist=======\n";
	
	for(int i=0; i<nodes; i++){
		for(int j=0; j<nodes; j++){
			cout << trans_array[i][j] << " ";
		}
		cout << "\n";
	}
	
	cout << "=============================\n";
	
	for(int i=0; i<nodes; i++){
		cout << itoc(i) << ": ";
		for(int j=0; j<trans_list[i].size(); j++){
			if(j != trans_list[i].size()-1)
				cout << "[" << itoc(trans_list[i][j]) << "]" << "->";
			else
				cout << "[" << itoc(trans_list[i][j]) << "]" << " ";

		}
		cout << "\n";
	}	// Transposed 인접리스트 출력

	return 0;
}

