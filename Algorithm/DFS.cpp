#include <iostream>
#include <memory>

struct Node {
  int val;
  std::unique_ptr<Node> lnode;
  std::unique_ptr<Node> rnode;
  Node(int x) : val(x) {};
};

void DFS(Node *root_node) {
  if (root_node == nullptr)
    return;
  DFS(root_node->lnode.get());
  DFS(root_node->rnode.get());
  std::cout << root_node->val;
}

int main() {
  auto root = std::make_unique<Node>(0);
  root->lnode = std::make_unique<Node>(1);
  root->rnode = std::make_unique<Node>(2);
  root->lnode->lnode = std::make_unique<Node>(3);
  root->lnode->rnode = std::make_unique<Node>(4);
  root->rnode->lnode = std::make_unique<Node>(5);
  root->rnode->rnode = std::make_unique<Node>(6);
  root->lnode->lnode->lnode = std::make_unique<Node>(7);
  root->lnode->lnode->rnode = std::make_unique<Node>(8);
  root->lnode->rnode->lnode = std::make_unique<Node>(9);
  DFS(root.get());
  return 0;
}
