#include <algorithm>
#include <iostream>
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

int _balance_factor(TreeNode *cur_node) {
  if (cur_node == nullptr) {
    return -2;
  }

  int l_child_h = cur_node->lnode ? cur_node->lnode->height : -1;
  int r_child_h = cur_node->rnode ? cur_node->rnode->height : -1;

  return l_child_h - r_child_h;
}

TreeNode *balance_tree(TreeNode *cur_node) {
  int bf = _balance_factor(cur_node);
  TreeNode *root = cur_node;
  if (bf == 2) {
    TreeNode *non_bal_child = rightRotation(cur_node);
  }
  return nullptr;
}

int update_height(TreeNode* root){
  if (root == nullptr) {
    return 0;
  }
  int left_child_h = root->lnode ? root->lnode->height : -1;
  int right_child_h = root->rnode ? root->rnode->height : -1;
  return std::max(left_child_h,right_child_h) + 1;  ;
}

void insert(TreeNode *root,int x) {
  TreeNode *node = new TreeNode(x);
  while (true) {
    int mode = x < root->val ? 0 : 1;
    if (root == nullptr) {
      return;
    };
    
    if (x < root->val && root->lnode == nullptr) {
      root->lnode = node;
      root->height = update_height(root);
      break;
    } else if(x > root->val && root->rnode == nullptr){
      root->rnode = node;
      root->height = update_height(root);
      break;      
    } else if(mode == 0){
      root->height = update_height(root);
      root = root->lnode;
    } else {
      root->height = update_height(root);
      root = root->rnode;
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
