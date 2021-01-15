#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#define MAX_TREE_HT 100
using namespace std;

//Huffman Tree node
struct MinHeapNode
{
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

//Min heap node
struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

//it allocates new min heap
//for given character and frequency
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp
        = (struct MinHeapNode*)malloc
          (sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

//used to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array
        = (struct MinHeapNode**)malloc(minHeap->
                                       capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

//function to swap two min heap
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

//function to create a standard min heap from array
void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->
            freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->
            freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

//function to check if size of heap is one or not
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
        = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

//function to insert new node to min heap
void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

//function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

//function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout<< arr[i];

    cout<<"\n";
}

//function to check if node is a leaf
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

//Creates a min heap of capacity
//equal to size and inserts all character of
//data[] in min heap. Initially size of
//min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}


//function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap))
    {

        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

//function that prints huffman code from root of huffman tree
void printCodes(struct MinHeapNode* root, int arr[], int top)

{

    if (root->left)
    {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root))
    {

        cout<< root->data <<": ";
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size)

{
    // Construct Huffman Tree
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
}

void string_char_frequency()
{
    char c_arr[30];
    int freq[26];
    int i = 0;
    int j = 0;
    char ch;
    cout<<"Enter character (! to exit): \n";
    cout<<"\nEnter character : ";
    cin>>c_arr[i];
    ch = c_arr[i];
    i++;
    cout<<"\nEnter frequency of "<<ch<<" : ";
    cin>>freq[j];
    j++;
    while(ch != '!'){
        cout<<"\nEnter character : ";
    cin>>c_arr[i];
    ch = c_arr[i];
    i++;
    if(ch == '!'){
        break;
    }
    cout<<"\nEnter frequency of "<<ch<<" : ";
    cin>>freq[j];
    j++;
    }
    char arr[i-1];
    int f[j-1];
    for(int k = 0; k<(i-1);k++){
        arr[k] = c_arr[k];
        f[k] = freq[k];
    }
    //huffman
    cout<<"\n"<<"code to be transferred after zipping"<<endl;
    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, f, size);

}


int main()
{

    string_char_frequency();
    return 0;

}
