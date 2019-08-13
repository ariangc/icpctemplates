/*
	Mininum XOR-Pair on an array in O(n)
	Trie-based Implementation
*/


#define INT_SIZE 32
 
struct TrieNode{
    int value;
    TrieNode * Child[2];
};
 
TrieNode * getNode(){
    TrieNode * newNode = new TrieNode;
    newNode->value = 0;
    newNode->Child[0] = newNode->Child[1] = NULL;
    return newNode;
}

void insert(TrieNode *root, int key){
    TrieNode *temp = root;
 
    for (int i = INT_SIZE-1; i >= 0; i--){
        bool current_bit = (key & (1<<i));
 
        if (temp->Child[current_bit] == NULL)
            temp->Child[current_bit] = getNode();
 
        temp = temp->Child[current_bit];
    }
 
    temp->value = key ;
}
 
int  minXORUtil(TrieNode * root, int key){
    TrieNode * temp = root;
 
    for (int i=INT_SIZE-1; i >= 0; i--){

        bool current_bit = ( key & ( 1<<i) );

        if (temp->Child[current_bit] != NULL)
            temp = temp->Child[current_bit];

        else if(temp->Child[1-current_bit] !=NULL)
            temp = temp->Child[1-current_bit];
    }
    return key ^ temp->value;
}

int minXOR(int arr[], int n){
    int min_xor = INT_MAX;

    TrieNode *root = getNode();
    insert(root, arr[0]);

    for (int i = 1 ; i < n; i++){
        min_xor = min(min_xor, minXORUtil(root, arr[i]));
        insert(root, arr[i]);
    }
    return min_xor;
}

int main(){
    int arr[] = {9, 5, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << minXOR(arr, n) << endl;
    return 0;
}
