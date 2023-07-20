#include <iostream>
using namespace std;
 
class BinaryNode {
    int data;
    BinaryNode *left, *right;
    
 
public:
    
    // Default constructor.
    BinaryNode();
 
    // Parameterized constructor.
    BinaryNode(int);
 
    // Insert function.
    BinaryNode* Insert(BinaryNode*, int);
 
    // Inorder traversal.
    void Inorder(BinaryNode*);

    //Find minimum
    BinaryNode* BSTMinimum(BinaryNode* v);
    //Insert
    BinaryNode* BSTInsert(BinaryNode* u, BinaryNode* v);
};
 
// Default Constructor definition.
BinaryNode ::BinaryNode()
    : data(0)
    , left(NULL)
    , right(NULL)
{
}
 
// Parameterized Constructor definition.
BinaryNode ::BinaryNode(int value)
{
    data = value;
    left = right = NULL;
}
 
// Insert function definition.
BinaryNode* BinaryNode ::Insert(BinaryNode* root, int value)
{
    if (!root) {
        // Insert the first node, if root is NULL.
        return new BinaryNode(value);
    }
 
    // Insert data.
    if (value > root->data) {
        // Insert right node data, if the 'value'
        // to be inserted is greater than 'root' node data.
 
        // Process right nodes.
        root->right = Insert(root->right, value);
    }
    else if (value < root->data){
        // Insert left node data, if the 'value'
        // to be inserted is smaller than 'root' node data.
 
        // Process left nodes.
        root->left = Insert(root->left, value);
    }
 
    // Return 'root' node, after insertion.
    return root;
}
BinaryNode* BinaryNode::BSTInsert(BinaryNode* u, BinaryNode* v) {
    if(v == nullptr)
    {
        return new BinaryNode(u->data);
    }
    else if(u->data < v->data) 
    {
        v->left = BSTInsert(u, v->left);
    }
    else
    {
        v->right = BSTInsert(u, v->right);
    }
    return v;
}
// Inorder traversal function.
// This gives data in sorted order.
void BinaryNode ::Inorder(BinaryNode* root)
{
    if (!root) {
        return;
    }
    Inorder(root->left);
    cout << root->data << endl;
    Inorder(root->right);
}

BinaryNode* BinaryNode::BSTMinimum(BinaryNode* v) {
    while(v->left != nullptr)
    {
        v = v->left;
    }
    cout << v->data << endl;
    return v;
}
 
// Driver code
int main()
{
    BinaryNode b, *root = NULL;
    root = b.Insert(root, 50);
    b.Insert(root, 30);
    b.Insert(root, 20);
    b.Insert(root, 40);
    b.Insert(root, 70);
    b.Insert(root, 60);
    b.Insert(root, 80);
 
    b.Inorder(root);
    cout << endl;
    b.BSTMinimum(root);
    cout << endl;

    BinaryNode *u = new BinaryNode(55);
    b.BSTInsert(u, root);
    b.Inorder(root);
    return 0;
}