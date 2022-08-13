#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;  //parent pointer
    std::vector<Node *> children; //a list of children

    //constructor
    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

//naive solution written by instructor
int naive(int n, std::vector<Node> &nodes){
	int maxheight = 0;
	for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    		int height = 0;
    		for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      			height++;
    		maxheight = std::max(maxheight, height);
 	}	
	return maxheight;

}


// Breadth-First Search (reference from discussion in leetcode 559. maximum depth of N-ary tree)
int Calculate(std::vector<Node> &nodes){
	int depth  = 0;     //keep track of the max depth of the tree

	std::queue<Node> q;   //create queue to store nodes
	
	//O(n)
	for(int i = 0; i<nodes.size(); i++){
		if(nodes[i].parent == NULL)     //find the root of the tree
			q.push(nodes[i]);     //push the root into the queue 
	}
	//break after q becomes empty
	while(!q.empty()){
		int count = q.size();
		//break after count reaches -1
		while(count --){
			Node n = q.front();  //return the front of the queue
			q.pop();
			//go through the children list and push it into queue
			for(int i = 0; i < n.children.size(); i++){  
				q.push(*n.children[i]);
			}
		}
		depth++;	
	
	}
	return depth;
}



int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  
  //read each parent index and build tree
  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    // if parent_index = -1 -> root
    nodes[child_index].key = child_index;

  }

  // Replace this code with a faster implementation
  int maxheight = Calculate(nodes); 
    
  std::cout << maxheight << std::endl;

  return 0;
}

int main (int argc, char **argv)
{

// Allow larger stack space
#if defined(__unix__) || defined(__APPLE__)
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
