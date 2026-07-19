#include <iostream>
#include <memory>
#include <queue>
#include <vector>

struct Node {
  int val;
  std::unique_ptr<Node> lnode;
  std::unique_ptr<Node> rnode;
  Node(int x):val(x){};
};

std::vector<int> BFS(Node *root_node) {
  std::queue<Node *> Q;
  std::vector<int> result_node;

  Q.push(root_node);
  while(!Q.empty()){
    Node *cur = Q.front();
    Q.pop();
    result_node.push_back(cur->val);
    if(cur->lnode.get() != nullptr){ Q.push(cur->lnode.get()); }
    if(cur->rnode.get() != nullptr){ Q.push(cur->rnode.get());  }
  };
  return result_node;
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
  std::vector<int> result = BFS(root.get());
  for(int x :result){
    std::cout << x;
  };
  return 0;
}
