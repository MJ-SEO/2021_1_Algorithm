// 프로그램명: Algorithm Analysis Homework 1
// 주      제: heap자료구조를 이용한 priority queue
// 작  성  자: 21600343 서명준 
// 작  성  일: 3/7 ~ 3/19

#include <iostream>

using namespace std;

typedef struct{
    float key;
    char* name;
} heap_t;             // Key와 name값을 저장하기 위한 구조체 선언

int index = 1;        // heap의 indexing을 위한 전역변수 index 선언
heap_t min_heap[32];  // 위에서 선언한 구조체의 array 

void display_menu(){
        cout << "\n************MENU**************" << "\n";
        cout << "I : Insert new element into queue" << "\n";
        cout << "D : Delete element with smallest key from queue" << "\n";
        cout << "C : Decrease key of element in queue" << "\n";
        cout << "P : Print out all element in queue" << "\n";
        cout << "Q : Quit" << "\n";
} // 메뉴출력함수

void swap(heap_t* a, heap_t* b){  // heap 노드의 위치를 서로 바꾸기 위한 swap 함수
    heap_t temp = *a;
    *a = * b;
    *b = temp;
}

void insert_heapify(heap_t* h, int idx){ // heap에 노드를 넣을때, heapify 해주는 함수
    if(idx == 1) return;
    
    if(h[idx/2].key > h[idx].key){
        swap(h[idx/2], h[idx]);
        idx = idx/2;
        insert_heapify(min_heap, idx); // 부모가 Insert된 노드 보다 작을 경우
	return;			       // 재귀적으로 idx==1(root node)일떄까지 탐색
    }    
    else{
        return;
    }
}

int min_node(int a, int b){  // delete_heapify함수에서 child중 key값이 작은 child를 찾기위한 함수
    if(min_heap[a].key <= min_heap[b].key) return a; 
    else return b;
}

void delete_heapify(heap_t* h, int idx){
    if(idx >= index/2) return;
    int lc = idx*2;
    int rc = idx*2+1;
    int smaller_idx = min_node(lc, rc);   // child중 더 작은 key값을 갖는 노드를 반환 
 
    if(h[smaller_idx].key < h[idx].key){  // 만일 더 작은 child가 부모노드보다 작다면, 
        swap(h[smaller_idx], h[idx]);	  
        delete_heapify(min_heap, smaller_idx); // 재귀적으로 더 작은 노드와 부모노드를 swap
    }
    else{
        return;
    }
}

int strlen(char* name){  // 아래 Insert_node()함수에서 name의 validity를 확인하기 위한 함수
	int strlen = 0;
	while(name[strlen] != '\0'){
		strlen++;
	}
	return strlen;
}  

void insert_node(){  // 노드의 name과 key값을 입력받은 후, 위의 insert_hepify함수를 호출
    char* name = (char*)malloc(sizeof(char)*100); 
    float key;
    cout << "Enter name of element: " << " "; 
    cin >> name;
    if(strlen(name) > 10){
	    cout << "Invalid input\n";
	    return;                    // 입력받은 name이 10자가 넘어갈경우invalid input
    }
    min_heap[index].name = name;
    cout << "Enter key value of element: " << " ";
    cin >> key;
    if(key < 0.0 || key > 100.0){
	    cout << "Invalid input\n";
	    return;			// 입력받은 key가 범위를 벗어날 경우 invalid input
    }
    min_heap[index].key = key;

    insert_heapify(min_heap, index);
    index++; // heap의 indexing 수정

    cout << "New element [" << name << ", " << key << "] is inserted" << endl;
}

void delete_node(){ // heap array의 마지막에 있던 노드를 root노드로 옮긴 후 위의 delete_heapify 함수를 호출
    if(index == 1) {
	    cout << "Heap is empty\n";
	    return;
    }
    cout << "[" << min_heap[1].name << ", " << min_heap[1].key << "]" << "is deleted" << "\n";
    min_heap[1] = min_heap[index-1];
    cout << "[DEBUG] arr[1]: " << min_heap[1].name << "\n";
    delete_heapify(min_heap, 1); // root노드로부터 재귀적으로 heapify
    index--;                  
}

void decrease_node(){ // 수정하고자 하는 index와 key값을 입력받아 수정한 후 heapify함수 호출
    if(index == 1){
	    cout << "Heap is empty\n";
	    return;
    }
    int idx;
    float old_key;
    float new_key;
    cout << "Enter index of element: " << " ";
    cin >> idx;
    if(idx <1 || idx>=index){          // 입력받은 index가 범위를 벗어날 경우 Invalid index
    	cout << "Invalid index\n";
	return;
    } 
    cout << "Enter new key value: " << " ";
    cin >> new_key;
    if(new_key < 0.0 || new_key > 100.0){
	    cout << "Invalid input\n";
	    return;			// 입력받은 key가 범위를 벗어날 경우 invalid input
    }

    old_key = min_heap[idx].key;
    if(new_key > old_key){              // 새로운 key값이 기존 key값보다 큰 경우 Invalid input
	cout << "New_key must be smalloer than Old_key\n";
	return;
    }
    min_heap[idx].key = new_key;
    
    insert_heapify(min_heap, idx);

   /*
    if(new_key < old_key){
        insert_heapify(min_heap, idx);
    }
    else if(new_key > old_key){
        delete_heapify(min_heap, idx);
    }
    else{
        return;
    }
    */
}

void display_heap(){ // 전역변수 index에따라 현재 heap array에 있는 값을 출력
    for(int i=1; i<index; i++){
        cout << "[" << min_heap[i].name << ", " << min_heap[i].key << "]" << " ";
    }
    cout << "\n";
}


int main(){
    char* op = (char*)malloc(sizeof(char)*100);
    for(int i=0; i<32; i++){
	min_heap[i].key = 150.0;
    }
    while(1){  // Q혹은 q가 입력될때까지 opeation을 반복 수행
        display_menu();
        cout << "\nChoose menu: " << " ";
	cin >> op;
        if(strlen(op) == 1 && (op[0] == 'Q' || op[0] == 'q')) break;
        else if(strlen(op) == 1 && (op[0] == 'I' || op[0] == 'i')) insert_node();
        else if(strlen(op) == 1 && (op[0] == 'D' || op[0] == 'd')) delete_node();
        else if(strlen(op) == 1 && (op[0] == 'C' || op[0] == 'c')) decrease_node();
        else if(strlen(op) == 1 && (op[0] == 'P' || op[0] == 'p')) display_heap();
        else cout << "Invalid operation" << "\n";
    }

    cout << "Thank you. Bye!" << "\n";

    return 0;
}
