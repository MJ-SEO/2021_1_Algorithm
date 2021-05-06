#include <iostream>

using namespace std;

typedef struct{
    float key;
    char* name;
} heap_t;

int index = 1;
heap_t min_heap[31];

void display_menu(){
        cout << "\n************MENU**************" << "\n";
        cout << "I : Insert new element into queue" << "\n";
        cout << "D : Delete element with smallest key from queue" << "\n";
        cout << "C : Decrease key of element in queue" << "\n";
        cout << "P : Print out all element in queue" << "\n";
        cout << "Q : Quit" << "\n" << endl;
}

void swap(heap_t* a, heap_t* b){
    heap_t temp = *a;
    *a = * b;
    *b = temp;
}

void insert_heapify(heap_t* h, int idx){
    if(idx == 1) return;
    
    if(h[idx/2].key > h[idx].key){
        swap(h[idx/2], h[idx]);
        idx = idx/2;
        insert_heapify(min_heap, idx);
        return;        
    }    
    else{
        return;
    }
}

int min_node(int a, int b){
    if(min_heap[a].key <= min_heap[b].key) return a; 
    else return b;
}

void delete_heapify(heap_t* h, int idx){
    if(idx >= index) return;
    int lc = idx*2;
    int rc = idx*2+1;
    int smaller_idx = min_node(lc, rc);    
 
    if(h[smaller_idx].key < h[idx].key){
        swap(h[smaller_idx], h[idx]);
        delete_heapify(min_heap, smaller_idx);
    }
    else{
        return;
    }
}

void insert_node(){
    char* name = (char*)malloc(sizeof(char)*10); 
    float key;

    cout << "DEBUG now index: " << index << "\n";

    cout << "Enter name of element: " << endl; 
    cin >> name;
    min_heap[index].name = name;
  
    cin >> key;
    cout << "Enter key value of element: " << endl;
    min_heap[index].key = key;

    insert_heapify(min_heap, index);
    index++;

    cout << "New element [" << name << ", " << key << "] is inserted" << endl;
}

void delete_node(){
    cout << "[" << min_heap[1].name << ", " << min_heap[1].key << "]" << "is deleted" << "\n";
    min_heap[1] = min_heap[index-1];
    cout << "[DEBUG] arr[1]: " << min_heap[1].name << "\n";
    delete_heapify(min_heap, 1);
    index--;                  
}

void decrease_node(){
    int idx;
    float old_key;
    float new_key;
    cout << "Enter index of element: " << endl;
    cin >> idx;
    cout << "Enter new key value: " << endl;
    cin >> new_key;

    old_key = min_heap[idx].key;
    cout << "[DEBUG] old_key: " << old_key << "\n";
    min_heap[idx].key = new_key;
    cout << "[DEBUG] new_key: " << new_key << " " << min_heap[idx].key << "\n";

    if(new_key < old_key){
        insert_heapify(min_heap, idx);
    }
    else if(new_key > old_key){
        delete_heapify(min_heap, idx);
    }
    else{
        return;
    }
}

void display_heap(){
    cout << "DEBUG IN, index: " << index << "\n";
    for(int i=1; i<index; i++){
        cout << "[" << min_heap[i].name << ", " << min_heap[i].key << "]" << " ";
    }
    cout << "\n";
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    char op;

    for(int i=0; i<31; i++){
	min_heap[i].key = 150.0;
    }
    
    while(1){
        display_menu();
        cin >> op;
        if(op == 'Q' || op == 'q'){
            cout << "Choose menu: " << op << "\n";
            break;
        }
        else if(op == 'I' || op == 'i'){
            cout << "Choose menu: " << op << "\n";
            insert_node();
        }
        else if(op == 'D' || op == 'd'){
            cout << "Choose menu: " << op << "\n";
            delete_node();
        }
        else if(op == 'C' || op == 'c'){
            cout << "Choose menu: " << op << "\n";
            decrease_node();
        }
        else if(op == 'P' || op == 'p'){
            cout << "Choose menu: " << op << "\n";
            display_heap();
        }
        else{
            cout << "Invalid operation" << "\n";
        }
    }

    cout << "Thank you. Bye!" << "\n";

    return 0;
}
