#include <stdio.h>
#include <stdlib.h>
// Insertion, deletion, searching and rotation operations on an AVL tree

// AVL Tree node 
struct AVLNode {
	int key; // value
	struct AVLNode* left; // left child
	struct AVLNode* right; // right child 
	int height; 
};

// Function to create a new node
struct AVLNode* createNode(int key){
	struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
	
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // New node is initially added at leaf
	
	return node; 
}

// Function to get maximum 
int max(int a, int b){
	return (a > b)? a : b;
}

// Function to get minimum
int minValueNode(struct AVLNode* node){
	struct AVLNode* current = node;
	while(current->left != NULL){ // We look at the left side since minimum
		current = current->left;
	}
	return current;
}

// Function to get height of the node
int getHeight(struct AVLNode* node){
	if(node == NULL){
		return 0;
	}
	
	return node->height;
}

// Function to get balance factor of a node
int getBalanceFactor(struct AVLNode* node){
	if(node == NULL){
		return 0;
	}	
	
	return getHeight(node->left) - getHeight(node->right);
}

// Right rotation function
struct AVLNode* rightRotate(struct AVLNode* unbalancedNode){
	struct AVLNode* leftChild = unbalancedNode->left; // left child of the unbalancednode
	struct AVLNode* leftRight= leftChild->right; // right child of the left child
	
	// Perform rotation
	leftChild->right = unbalancedNode; // clockwise so unbalancedNode(nasa taas) becomes the left child's (na ngayong nasa taas na) right child
	unbalancedNode->left = leftRight; //  orig left child's right becomes middle node's left child
	
	// Update heights (max() to know which child is taller, left or right, dahil kung ano mas mahaba yun ang binibilang)
	unbalancedNode->height = max(getHeight(unbalancedNode->left), getHeight(unbalancedNode->right)) + 1; // +1 to count also the current node sa height
	leftChild->height = max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1; // +1 to count also the current node sa hieght
	
	return leftChild; // New root of the subtree after rotation
}

// Left rotation function
struct AVLNode* leftRotate(struct AVLNode* unbalancedNode){
	struct AVLNode* rightChild = unbalancedNode->right; // right child of the unbalancednode
	struct AVLNode* rightLeft = rightChild->left; // left child of the right child
	
	// Perform rotation
	rightChild->left = unbalancedNode; // counterclockwise so unbalancednode(nasa taas) becomes the right child's (na ngayong nasa taas na) left child
	unbalancedNode->right = rightLeft; // orig right child's left child becomes middle node's right child
	
	// Update heights
	unbalancedNode->height = max(getHeight(unbalancedNode->left), getHeight(unbalancedNode->right)) + 1;
	rightChild->height = max(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;
	
	return rightChild; 
}

// Function to insert a key into AVL tree
struct AVLNode* insert(struct AVLNode* node, int key){
	
	// Perform standard BST insertion
	if(node == NULL){
		return createNode(key);
	}
	
	if(key < node->key){ 
		node->left = insert(node->left, key); // Go left and insert there
	} else if(key > node->key){
		node->right = insert(node->right, key); // Go right and insert there
	} else{
		return node; // Equal keys are not allowed in BST
	}
	
	// Update height of this ancestor node
	node->height = 1 + max(getHeight(node->left), getHeight(node->right)); // height = 1 + height of tallest child
	
	// Get BF of the ancestor node to check if it's unbalanced
	int balance = getBalanceFactor(node);
	
	// If unbalanced, do the four (4) rotations
	if(balance > 1 && key < node->left->key){ // LL heavy so right rotate
		return rightRotate(node);
	} else if(balance < -1 && key > node->right->key){ // RR heavy so left rotate
		return leftRotate(node);
	} else if(balance > 1 && key > node->left->key) { // LR rotation, left then right rotate
		node->left = leftRotate(node->left);
		return rightRotate(node);
	} else if(balance < -1 && key < node->right->key){ // RL rotation, right then left rotate
		node->right = rightRotate(node->right); 
		return leftRotate(node);
	}
	
	// Return unchanged node pointer if balanced.
	return node;
}

// Search function
int search(struct AVLNode* root, int key){
	if(root == NULL){
		return 0;
	} else if (root->key == key){ 
		return 1;
	} else if(key < root->key){  
		return search(root->left, key); // Go left until key is found
	} else if(key > root->key){ 
		return search(root->right, key); // Go right until key is found
	}
}

// Deletion function
struct AVLNode* deleteNode(struct AVLNode* root, int key){
	if(root == NULL){ 
		return root;
	}
	
	if(key < root->key){
		root->left = deleteNode(root->left, key); // Calls itself to access/go to the left subtree
	} else if(key > root->key){
		root->right = deleteNode(root->right, key); // Calls itself to access/go to the right subtree
 	} else {
 		if(root->left == NULL || root->right == NULL){ // Means that we only have the root node
 			struct AVLNode* temp = root->left ? root->left : root->right; // puts either the left child or right child in temp
 			
 			if(temp == NULL){ // If temp have no value, meaning no left or right child, then
 				temp = root;  // we put the root inside the null, then
 				root = NULL;  // make root null
			} else{
				*root = *temp;
			}
			 
			free(temp); // Delete the temp or the root
		} else {  // If left or right child exists
		 	struct AVLNode* temp = minValueNode(root->right); // We find the smallest val from the right subtree to replace the root
		 	
		 	root->key = temp->key; // Replace the root with the smallest val from right subtree
			root->right = deleteNode(root->right, temp->key); // Since we replaced the root with the smallest, we have two of that value now
															  // one on the root and one on the leaf, so we look for that temp->key again then delete it.
	 	}
	 	
		if(root == NULL){  // If wala na natira
	 		return root;		
		} 
		
		// Update the heiht 
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		
		// Check the balance again
		int balance = getBalanceFactor(root);
		
		// If unbalanced, do the four (4) rotations
		if(balance > 1 && key < getBalanceFactor(root->left) >= 0){ // LL heavy 
			return rightRotate(root);
		} else if(balance < -1 && getBalanceFactor(root->right) <= 0){ // RR heavy
			return leftRotate(root);
		} else if(balance > 1 && getBalanceFactor(root->left) < 0) { // LR rotation
			root->left= leftRotate(root->left);
			return rightRotate(root);
		} else if(balance < -1 && getBalanceFactor(root->right) > 0){ // RL rotation
			root->right = rightRotate(root->right); 
			return leftRotate(root);
		}           
		            
		// Return unchanged root pointer if balanced.
		return root;
	}
}

// Function to traverse using in-order traversal
void inOrder(struct AVLNode* root){
	if(root != NULL){
		inOrder(root->left);
		printf("%d", root->key);
		inOrder(root->right);
	}
}

// Main function
int main(){
	
	struct AVLNode* root = NULL;
	
	// Insert nodes
	root = insert(root, 1);
	root = insert(root, 2);
	root = insert(root, 4);
	root = insert(root, 5);
	root = insert(root, 6);
	root = insert(root, 3);	
	
	printf("Inorder traversal: ");
	inOrder(root);
	
	printf("\nDeleting 4...\n");
	root = deleteNode(root, 4);
	inOrder(root);
	
	printf("\nSearch 6 [1-found, 0-not found] = %d\n", search(root, 6));
	
	return 0;
}
