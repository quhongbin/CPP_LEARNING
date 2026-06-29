#include <algorithm>
#include <iostream>
#include <list>
#include <ostream>
#include <queue>
#include <vector>

struct TreeNode{
  int val;
  TreeNode *lnode = nullptr;
  TreeNode *rnode = nullptr;
  int height;
  TreeNode(int x):val(x){};
};

TreeNode* rightRotation(TreeNode *cur_node) {
  if (cur_node->lnode) {
    TreeNode *child_node = cur_node->lnode;
    cur_node->lnode = nullptr;
    child_node->rnode = cur_node;
    return child_node;
  };
  return nullptr;
}

//calculate the balance factor from the root node
int _balance_factor(TreeNode *cur_node) {
  if (cur_node == nullptr) {
    return -2;
  }

  int l_child_h = cur_node->lnode ? cur_node->lnode->height + 1 : -1;
  int r_child_h = cur_node->rnode ? cur_node->rnode->height + 1 : -1;

  return l_child_h - r_child_h;
}

void update_height(TreeNode* root){
  if (root == nullptr) {
    root->height = -1;
  }
  int left_child_h = root->lnode ? root->lnode->height : -1;
  int right_child_h = root->rnode ? root->rnode->height : -1;
  root->height = std::max(left_child_h , right_child_h) + 1 ;
}


//insert node and keep balance
void insert(TreeNode *root,int x) {
  TreeNode *node = new TreeNode(x);
  std::list<TreeNode*> parents;
  while (true) {
    int mode = x < root->val ? 0 : 1;
    if (root == nullptr) {
      return;
    };
 
    if (x < root->val && root->lnode == nullptr) {
      root->lnode = node;
      update_height(root);
      break;
    } else if(x > root->val && root->rnode == nullptr){
      root->rnode = node;
      update_height(root);
      break;      
    } else if(mode == 0){
      parents.push_front(root);
      root = root->lnode;
    } else {
      parents.push_front(root);
      root = root->rnode;
    }
  }
  for (TreeNode* &node : parents) {
    update_height(node);
  }
  for (TreeNode* &node : parents) {
    if (_balance_factor(node) > 1) {
      node->lnode = rightRotation(node);
    }    
  }
}

std::vector<TreeNode*> BFS(TreeNode *root){
  std::queue<TreeNode*> Q;
  std::vector<TreeNode*> result;
  Q.push(root);
  while (!Q.empty()) {
    TreeNode *cur_node = Q.front();
    Q.pop();
    result.push_back(cur_node);
    if (cur_node->lnode != nullptr) {
      Q.push(cur_node->lnode);
    }
    if (cur_node->rnode != nullptr) {
      Q.push(cur_node->rnode);
    }
  };
  return result;
}

int main() {
  TreeNode *root = new TreeNode(5);
  insert(root, 3);
  insert(root, 2);
  auto r = BFS(root);
  for (TreeNode* node : r) {
    std::cout << node->val << ";height: " << node->height << "\n" ;
  };
  return 0;    
}
