#include <algorithm>
#include <deque>
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

int height(TreeNode *node) {
  //空节点高度为-1,叶子节点高度为0
  return node == nullptr ? -1 : node->height;  
}

void update_height(TreeNode* root){
  root->height = std::max(height(root->lnode) , height(root->rnode)) + 1 ;
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

TreeNode* leftRotaion(TreeNode *cur_node){
  TreeNode *child_node = cur_node->rnode;
  TreeNode *grand_child = child_node->lnode;
  child_node->lnode = cur_node;
  cur_node->rnode = grand_child;
  update_height(cur_node);
  update_height(child_node);
  return child_node;
}

//calculate the balance factor from the root node
int _balance_factor(TreeNode *cur_node) {
  if (cur_node == nullptr) {
    return 0;
  }
  return height(cur_node->lnode) - height(cur_node->rnode);
}

// balance the root of tree
void balance_tree(std::deque<TreeNode*>parents) {
  for (TreeNode* &node : parents) {
    if (_balance_factor(node) > 1) {
        std::cout << node->val <<std::endl;
    }    
  }
}

//insert node and keep balance
void insert(TreeNode *root,int x) {
  TreeNode *node = new TreeNode(x);
  //  parents.clear();
  while (true) {
    int mode = x < root->val ? 0 : 1;
    if (root == nullptr) {
      return;
    };
    //    parents.push_front(root);
    if (x < root->val && root->lnode == nullptr) {
      root->lnode = node;
      update_height(root);
      //      parents.push_front(root);
      break;
    } else if(x > root->val && root->rnode == nullptr){
      root->rnode = node;
      update_height(root);
      //      parents.push_front(root);
      break;      
    } else if(mode == 0){
      update_height(root);
      //      parents.push_front(root);
      root = root->lnode;
    } else {
      update_height(root);
      //      parents.push_front(root);
      root = root->rnode;
    }
  };

}

//
TreeNode* rotate(TreeNode* node) {
  int _balanceFactor = _balance_factor(node);
  if (_balanceFactor >1) {
    if (_balance_factor(node->lnode) < 0) {
      node->lnode = leftRotaion(node->lnode);
      return rightRotation(node);
    }else {
      return rightRotation(node);
    }
  }
  if (_balanceFactor < -1) {
    if (_balance_factor(node->rnode) > 0) {
      node->rnode = rightRotation(node->rnode);
      return leftRotaion(node);
    }else {
      return leftRotaion(node);
    }
  }
  return node;
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
  insert(root, 4);
  insert(root,3);
  insert(root, 2);
 for (TreeNode* &node : parents) {
   rotate(node);
 }

  std::deque<TreeNode *> parent_nodes;
  
  for (TreeNode* &node : parents) {
    if (_balance_factor(node) > 1) {
      parent_nodes.push_back(node);
      node = rotate(node);
    }
  }

//for (int i =0 ; i < parent_nodes.size();i++) {
//TreeNode *non_balance_node = parent_nodes[i];
//TreeNode *father_non_balance_node = (i +1 <parent_nodes.size()) ? parent_nodes[i+1] : nullptr;
//if (father_non_balance_node) {
//father_non_balance_node->lnode = rightRotation(non_balance_node);
////std::cout << "non-balance:"<< non_balance_node->val;
////std::cout << "height:" << non_balance_node->height;
////std::cout << "father:"<< father_non_balance_node->val;
////std::cout << "factor:" << _balance_factor(non_balance_node)  << "\n" ;
//}else{;
//non_balance_node = rightRotation(non_balance_node);
//root = non_balance_node;
//}
//}
  balance_tree(parent_nodes);
  auto r = BFS(root);
  for (TreeNode* &node : r) {
    std::cout << node->val << ";height: " << node->height << "\n" ;
  };
  return 0;    
}
