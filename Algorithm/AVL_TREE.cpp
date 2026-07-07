#include <algorithm>
#include <iostream>
#include <ostream>
#include <queue>
#include <vector>

struct TreeNode{
  int val;
  TreeNode *lnode = nullptr;
  TreeNode *rnode = nullptr;
  int height = 0;
  TreeNode(int x):val(x){};
};

static std::deque<TreeNode*> parents;

void update_height(TreeNode* root){
  if (root == nullptr) {
    root->height = -1;
  }
  int left_child_h = root->lnode ? root->lnode->height : -1;
  int right_child_h = root->rnode ? root->rnode->height : -1;
  root->height = std::max(left_child_h , right_child_h) + 1 ;
}

TreeNode* rightRotation(TreeNode *cur_node) {
  TreeNode *child_node = cur_node->lnode;
  TreeNode *grand_child = child_node->rnode;
  child_node->rnode = cur_node;
  cur_node->lnode = grand_child;
  update_height(cur_node);
  update_height(child_node);
  return child_node;
}

//calculate the balance factor from the root node
int _balance_factor(TreeNode *cur_node) {
  if (cur_node == nullptr) {
    return -1;
  }

  int l_child_h = cur_node->lnode ? cur_node->lnode->height +1 : 0;
  int r_child_h = cur_node->rnode ? cur_node->rnode->height +1 : 0;

  return l_child_h - r_child_h;
}

// balance the root of tree
void balance_tree(std::vector<TreeNode*>parents) {
  for (TreeNode* &node : parents) {
    if (_balance_factor(node) > 1) {
        std::cout << node->val <<std::endl;
    }    
  }
}

//insert node and keep balance
void insert(TreeNode *root,int x) {
  TreeNode *node = new TreeNode(x);
  parents.clear();
  while (true) {
    int mode = x < root->val ? 0 : 1;
    if (root == nullptr) {
      return;
    };
    parents.push_front(root);
    if (x < root->val && root->lnode == nullptr) {
      root->lnode = node;
      //      parents.push_front(root);
      break;
    } else if(x > root->val && root->rnode == nullptr){
      root->rnode = node;
      //      parents.push_front(root);
      break;      
    } else if(mode == 0){
      //      parents.push_front(root);
      root = root->lnode;
    } else {
      //      parents.push_front(root);
      root = root->rnode;
    }
  };

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
  insert(root,1);
  for (TreeNode* &node : parents) {
    update_height(node);
  }
  std::deque<TreeNode *> parent_nodes;
  
  for (TreeNode* &node : parents) {
    if (_balance_factor(node) > 1) {
      parent_nodes.push_back(node);
    }
  }
  
  for (int i =0 ; i < parent_nodes.size();i++) {
    TreeNode *non_balance_node = parent_nodes[i];
    TreeNode *father_non_balance_node = (i +1 <parent_nodes.size()) ? parent_nodes[i+1] : nullptr;
    if (father_non_balance_node) {
      father_non_balance_node->lnode = rightRotation(non_balance_node);
//std::cout << "non-balance:"<< non_balance_node->val;
//std::cout << "height:" << non_balance_node->height;
//std::cout << "father:"<< father_non_balance_node->val;
//std::cout << "factor:" << _balance_factor(non_balance_node)  << "\n" ;
    }else{;
      non_balance_node = rightRotation(non_balance_node);
      root = non_balance_node;
    }
  }
  auto r = BFS(root);
  for (TreeNode* &node : r) {
    std::cout << node->val << ";height: " << node->height << "\n" ;
  };
  return 0;    
}
