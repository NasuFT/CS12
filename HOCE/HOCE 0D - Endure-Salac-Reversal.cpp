#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *reverse(Node *head) {
    Node *current_node = head;
    vector<Node*> nodes;
    nodes.push_back(current_node);

    while(current_node->next != nullptr) {
        current_node = current_node->next;
        nodes.push_back(current_node);
    }

    for(unsigned int i = nodes.size() - 1; i >= 1; i--) {
        nodes[i]->next = nodes[i - 1];
    }

    nodes[0]->next = nullptr;

    return nodes[nodes.size() - 1];
}

int main() {

}