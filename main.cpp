#include <iostream>

using namespace std;

template <typename T, int Order>
class Node{
public:
    int numberOfKeys;
    T *keysInNode;
    int order;
    bool isleaf;
    Node **children;

    Node(bool isLeaf){
        numberOfKeys=0;
        isleaf=isLeaf;
        keysInNode = new T[Order-1];
        children = new Node*[Order];
        for (int i = 0; i < Order; i++) {
            children[i] = NULL;
        }

    }
    void Print();
    ~Node() {
        delete[] keysInNode;
        delete[] children;
    }
};

template <typename T, int Order>

class BTree{
private:
    Node<T, Order> *root;

    void InsertInCorrectPlace( Node<T, Order> *node,T value);
    bool isFull(Node<T, Order> *node);
    void splitNode(Node<T, Order> *parent, int FullChildIndex, Node<T, Order> *fullChild);
    void PreOrderPrint(Node<T, Order> *node, int depth);

public:
    BTree(){
        root=NULL;
    }
    void Insert(T value);
    void Print();
    ~BTree() {
        delete root;
    }
};

template <typename T, int Order>
void BTree<T,Order>:: Insert(T value) {
    if (root==NULL) {
        root = new Node<T,Order>(true);
        root->keysInNode[0]=value;
        root->numberOfKeys=1;
    }
    else {
            InsertInCorrectPlace(root,value);
            if (isFull(root)) {
                Node<T,Order> *temp = new Node<T,Order>(false);
                temp->children[0]=root;
                splitNode(temp,0,root);
                root=temp;
            }
        }

    }


template <typename T, int Order>
void BTree<T,Order>:: InsertInCorrectPlace( Node<T,Order> *node,T value) {
    int i = node->numberOfKeys - 1;
    if (node->isleaf) {
        while (i>=0 && node->keysInNode[i]>value) {
            node->keysInNode[i + 1] = node->keysInNode[i];
            i--;
        }
        node->keysInNode[i + 1] = value;
        node->numberOfKeys++;
    }else {
        while(i>=0 && node->keysInNode[i]>value){
            i--;
        }
        i++;
        InsertInCorrectPlace(node->children[i], value);
        if (isFull(node->children[i])) {
            splitNode(node, i, node->children[i]);
        }

    }
}
template <typename T, int Order>
bool BTree<T,Order>::isFull(Node<T,Order> *node){
    if (node->numberOfKeys == Order) {
            return true;
    }
    return false;
}

template <typename T, int Order>
void BTree<T,Order>::splitNode(Node<T,Order> *parent, int FullChildIndex, Node<T,Order> *fullChild) {
    int middle=Order/2;
    Node<T,Order> *leftPart=new Node<T,Order>(fullChild->isleaf);
    Node<T,Order> *rightPart=new Node<T,Order>(fullChild->isleaf);
    leftPart->numberOfKeys=Order-middle -1 ;
    for (int i=0;i<leftPart->numberOfKeys;i++) {
        leftPart->keysInNode[i]=fullChild->keysInNode[i];
    }
    rightPart->numberOfKeys=Order-middle -1;
    for (int i=0;i<rightPart->numberOfKeys;i++) {
        rightPart->keysInNode[i]=fullChild->keysInNode[i+middle+1];

    }
    if(!fullChild->isleaf){
        for(int i= 0;i<=middle;i++){
            leftPart->children[i]=fullChild->children[i];
        }
        for(int i = 0;i<=middle;i++) {
            rightPart->children[i]=fullChild->children[i + middle + 1];
        }
    }
    for (int i=parent->numberOfKeys;i>FullChildIndex;i--) {
        parent->keysInNode[i]=parent->keysInNode[i-1];
        parent->children[i+1]=parent->children[i];
    }
    parent->keysInNode[FullChildIndex]=fullChild->keysInNode[middle];
    parent->children[FullChildIndex]=leftPart;
    parent->children[FullChildIndex+1]=rightPart;
    parent->numberOfKeys++;

}

template <typename T, int Order>
void BTree<T,Order>::PreOrderPrint(Node<T,Order> *node, int depth) {
    if (node == NULL) return;

    for (int i = 0; i < node->numberOfKeys; i++){
        if (i==0) {
            cout<<string(depth, ' ');
        }
        if (i==node->numberOfKeys-1) {
            cout<<node->keysInNode[i];
        }else {
            cout<<node->keysInNode[i]<<",";
        }

    }
    cout<<endl;
    for (int i = 0; i <= node->numberOfKeys; i++) {
        PreOrderPrint(node->children[i], depth+1);
    }
}
template <typename T, int Order>
void BTree<T,Order>::Print() {
    if (root != NULL) {
        PreOrderPrint(root,0);
    } else {
        cout<<"Empty"<<endl;
    }
}
int main()
{
    BTree<int,3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print();
    /*
    1,4
      0
      2,3
      5
    */
    // BTree t(5);
    cout<<"////////////////"<<endl;
    BTree<char,5> t;
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print();
        /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */
    return 0;
}



