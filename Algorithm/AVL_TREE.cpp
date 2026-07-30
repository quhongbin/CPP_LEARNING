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

static std::deque<TreeNode**> parents;

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

TreeNode* rotate(TreeNode* node);

// balance the root of tree
void balance_tree(std::deque<TreeNode*>parents) {
  for (TreeNode* &node : parents) {
    if (_balance_factor(node) > 1 ||_balance_factor(node) < -1) {
        std::cout << node->val <<std::endl;
    }    
  }
}

//insert node and keep balance
void insert(TreeNode *&root,int x) {
  TreeNode **link = &root;
  // **link -> *link
  parents.clear();

  while (*link != nullptr) {
    if (x == (*link)->val) {
      return;
    }

    parents.push_front(link);
    // **link = lnode || rnode
    if (x < (*link)->val) {
      link = &((*link)->lnode);
    } else {
      link = &((*link)->rnode);
    }
  }

  *link = new TreeNode(x);

  // 从插入位置的父节点开始向上更新，并直接替换原始树中的指针
  for (TreeNode **parent_link : parents) {
    update_height(*parent_link);
    *parent_link = rotate(*parent_link);
  }
}

// delete node and refresh the tree by double pointer
TreeNode* del (TreeNode *node,int x) {
  if (node == nullptr) {
    return nullptr;
  };
  if (x < node->val) {
    node->lnode = del(node->lnode, x);
  }else if (x > node->val) {
    node->rnode = del(node->rnode, x);
  }else {
    if (node->lnode == nullptr || node->rnode == nullptr) {
      TreeNode *child = node->lnode != nullptr ? node->lnode : node->rnode;
      if (node == nullptr) {
        delete node;
	return nullptr;
      }else {
        delete node;
	node = child;
      }
    }else {
      TreeNode *tempNode = node->rnode;
      while (tempNode != nullptr) {
	tempNode = tempNode->lnode;
      }
      int tempNodeVal = tempNode->val;
      tempNode->rnode = del(tempNode->rnode, tempNode->val);
      tempNode->val = tempNodeVal;
    }
  }
  update_height(node);
  node =rotate(node);
  return node;
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
  TreeNode *root = new TreeNode(10);
  insert(root, 30);
  insert(root, 20);
  insert(root, 40);
  root = del(root, 10);  
  auto r = BFS(root);
  for (TreeNode* &node : r) {
    std::cout << node->val << ";height: " << node->height << "\n" ;
  };
  return 0;    
}
