> a non-linear data struct
# Binary Tree
## General Technical Terms
|    Terms    |                           explanation                            |
| :---------: | :--------------------------------------------------------------: |
|  root node  |                   the top node of binary tree                    |
|  leaf node  |                   the node have no child node                    |
|    edge     |                  the pointer to link two nodes                   |
|   degree    |                    the number of child nodes                     |
|    level    |             increase from root node that level is 1              |
| tree height | the number of edges from root node to maximum distance leaf node |
|    depth    |        the number of edges from root node to current node        |
| node height |    the number of edges from maximum leaf node to current node    |

## The types of Binary Trees
1. perfect binary tree
	- all levels have filled
	- all of the leaf nodes' degrees is zero. The other nodes' degrees is 2
	- if the number of all of the nodes satisfy the formula which is $2^{h+1}-1$, and *h* is the tree height
2. complete binary tree
	- all of the lowest-level's nodes have arranged from left to right
	- assume *h* is tree height, *n* is the number of the nodes of lowest level, if the lowest-level's nodes not satisfy the formula which is $n=2^h$
3. full binary tree 
	- all of nodes have two child nodes expect leaf nodes 
4. balanced binary tree
	- assume $d$ is Height difference of any node that left child-tree height subtract right child-tree height satisfy $\lvert d \rvert \le 1$

## Binary Tree Degradation
while all nodes points left node or right node, which is a link

# Binary Tree traversal
1. level-order traversal (level-by-level)
	- base on breadth-first search algorithm
	```algorithm
		fun BFS(RootNode)
			create Q queue of node
			push RootNode into Q
			
			create value list V
			while Q is not NONE:
				Node = Q.front()
				if Node->lNode != nullptr:
					push lNode into Q
				if Node->rNode != nullptr:
					push rNode into Q
			return V
	```
	> BFS use queue which is a data struct follow FIFO rule
	
1. pre/in/post-order traversal
	- base on depth-first search algorithm
	```algorithm
		fun DFS(RootNode)
		
	```
	> DFS follow 