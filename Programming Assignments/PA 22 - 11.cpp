#include <iostream>

using namespace std;

class BinaryTreeNode {
    public:
        char data;
        BinaryTreeNode* left_subtree;
        BinaryTreeNode* right_subtree;
        BinaryTreeNode(int);
};

void visit(BinaryTreeNode *t) {

}

void preorder_traversal(BinaryTreeNode *root) {
    if(root == nullptr) return;
    visit(root);
    if(root->left_subtree != nullptr) preorder_traversal(root->left_subtree);
    if(root->right_subtree != nullptr) preorder_traversal(root->right_subtree);
}

int main() {

}