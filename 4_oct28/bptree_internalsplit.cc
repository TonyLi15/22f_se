#include "bptree.h"
#include <sys/time.h>

int mid = (int)ceil(N/2);
int midd = (int)ceil((N+1)/2);

struct timeval cur_time(void){
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}

void print_tree_core(NODE *n){
	printf("["); 
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]); 
		printf("%d", n->key[i]); 
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void print_tree(NODE *node) {
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

void
print_temp(TEMP t)
{
	int i;
	
	for (i = 0; i < t.nkey; i++) {
		printf("[%p]", t.chi[i]);
		printf("%d", t.key[i]);
	}
	printf("[%p]\n", t.chi[i]);
}


NODE *alloc_leaf(NODE *parent){
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;
	return node;
}

NODE *alloc_internal(NODE *parent){
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = false;
	node->parent = parent;
	node->nkey = 0;
	return node;
}

//function for insert_in_parent
NODE *alloc_root(NODE *leftchild, int key, NODE *rightchild){
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = false;
	node->parent = NULL;
	
	node->key[0] = key;
	node->chi[0] = leftchild;
	node->chi[1] = rightchild;
	
	node->nkey = 1;
	
	return node;
}

NODE *find_leaf(NODE *node, int key){
	int kid;
	
	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}
	
	return find_leaf(node->chi[kid], key);
}

NODE *insert_in_leaf(NODE *leaf, int key, DATA *data){
	int i;
	if (key < leaf->key[0]) {
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i] = leaf->chi[i-1] ;
			leaf->key[i] = leaf->key[i-1] ;
		} 
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}
	else {
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}
		for (int j = leaf->nkey; j > i; j--) {
			leaf->chi[j] = leaf->chi[j-1] ;
			leaf->key[j] = leaf->key[j-1] ;
		}
		
		//Assignment 1: leaf insert
		leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}
	leaf->nkey++;
	
	return leaf;
}

//function for leaf split
void insert_in_temp(TEMP *temp, int key, void *ptr){
	int i;
	if (key < temp->key[0]) {
		for (i = temp->nkey; i > 0; i--) {
			temp->chi[i] = temp->chi[i-1] ;
			temp->key[i] = temp->key[i-1] ;
		}
		temp->key[0] = key;
		temp->chi[0] = (NODE *)ptr;
	}
	else {
		for (i = 0; i < temp->nkey; i++) {
			if (key < temp->key[i]) break;
		}
		for (int j = temp->nkey; j > i; j--) {
			temp->chi[j] = temp->chi[j-1] ;
			temp->key[j] = temp->key[j-1] ;
		}
		temp->key[i] = key;
		temp->chi[i] = (NODE *)ptr;
	}
	temp->nkey++;
}

//function for leaf split
void copy_to_temp(TEMP *temp, NODE *node){
	int i;
	bzero(temp, sizeof(TEMP));
	for (i = 0; i < (N-1); i++) {
		temp->chi[i] = node->chi[i];
		temp->key[i] = node->key[i];
	} temp->nkey = N-1;
	temp->chi[i] = node->chi[i];
}

//function for leaf split
void reset(NODE *node){
	for (int i = 0; i < N-1; i++) {
		node->key[i] = 0;
	}
	for (int i = 0; i < N; i++) {
		node->chi[i] = NULL;
	}
	node->nkey = 0;
}

void copy_from_temp_to_left(TEMP temp, NODE *left){
	for (int i = 0; i < (int)ceil(N/2); i++) {
		left->key[i] = temp.key[i];
		left->chi[i] = temp.chi[i];
		left->nkey++;
	}
}

void copy_from_temp_to_right(TEMP temp, NODE *right){
	for (int i = (int)ceil(N/2); i < N; i++) {
		right->key[i - (int)ceil(N/2)] = temp.key[i];
		right->chi[i - (int)ceil(N/2)] = temp.chi[i];
		right->nkey++;
	}
}

void copy_from_temp_to_left_parent(TEMP *temp, NODE *left_parent){
	for (int i = 0; i < (int)ceil((N+1)/2); i++) {
		left_parent->key[i] = temp->key[i];
		left_parent->chi[i] = temp->chi[i];
		left_parent->nkey++;
	}
	left_parent->chi[(int)ceil((N+1)/2)] = temp->chi[(int)ceil((N+1)/2)];
}

void copy_from_temp_to_right_parent(TEMP *temp, NODE *right_parent){
	int i;
	for (i = (int)ceil((N+1)/2) + 1; i < N; i++){
		right_parent->key[i - ((int)ceil((N+1)/2) + 1)] = temp->key[i];
		right_parent->chi[i - ((int)ceil((N+1)/2) + 1)] = temp->chi[i];
		right_parent->nkey++;
	}
	right_parent->chi[i - ((int)ceil((N+1)/2) + 1)] = temp->chi[i];
	for (int i = 0; i < right_parent->nkey+1; i++) right_parent->chi[i]->parent = right_parent;
}

void insert_after_left_child(NODE *parent, NODE *left_child, int rs_key, NODE *right_child){
	int li = 0;
	int ri = 0;
	
	for(int i = 0; i < parent->nkey + 1; i++){
		if (parent->chi[i] == left_child) {
			li = i; // left_child_id
			ri = li+1; 
			break; 
		}
	}
	
	
	for (int i = parent->nkey+1; i > ri; i--) {
		parent->chi[i] = parent->chi[i-1];
	}
	for (int i = parent->nkey; i > li; i--) {
		parent->key[i] = parent->key[i-1];
	}
	
	parent->key[li] = rs_key;
	parent->chi[ri] = right_child;
	parent->nkey++;
	
}

void insert_temp_after_left_child(TEMP *temp, NODE *left_child, int rs_key, NODE *right_child){
	int li = 0;
	int ri = 0;
	int i;
	
	for(i = 0; i < temp->nkey + 1; i++){
		if (temp->chi[i] == left_child) {
			li = i; // left_child_id
			ri = li+1; 
			break; 
		}
	}
	assert(i != temp->nkey+1);
	
	for (int i = temp->nkey+1; i > ri; i--) {
		temp->chi[i] = temp->chi[i-1];
	}
	for (int i = temp->nkey; i > li; i--) {
		temp->key[i] = temp->key[i-1];
	}
	
	temp->key[li] = rs_key;
	temp->chi[ri] = right_child;
	temp->nkey++;
}

void insert_in_parent(NODE *left_child, int rs_key, NODE *right_child) {
	NODE *left_parent;
	NODE *right_parent;
	
	if (left_child == Root) {
		Root = alloc_root(left_child, rs_key, right_child);
		left_child->parent = right_child->parent = Root;
		return;
	}
	
	//Assignment 3: Internal Split
	left_parent = left_child->parent;
	if (left_parent->nkey < N-1) {
		insert_after_left_child(left_parent, left_child, rs_key, right_child);
	}
	else {
		TEMP temp;
		copy_to_temp(&temp, left_parent);
		insert_temp_after_left_child(&temp, left_child, rs_key, right_child);
		
		reset(left_parent);
		right_parent = alloc_internal(left_parent->parent);
		
		copy_from_temp_to_left_parent(&temp, left_parent);
		int rs_key_parent = temp.key[mid];
		copy_from_temp_to_right_parent(&temp, right_parent);
		insert_in_parent(left_parent, rs_key_parent, right_parent);
	}
}

void insert(int key, DATA *data){
	NODE *leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}
	else {
		leaf = find_leaf(Root, key);
	}
	if (leaf->nkey < (N-1)) {
		insert_in_leaf(leaf, key, data);
	}
	else {
		//Assignment 2: Leaf split
		NODE *left = leaf;
		NODE *right = alloc_leaf(leaf->parent);
		TEMP temp;
		copy_to_temp(&temp, left);
		insert_in_temp(&temp,key,data);
		right->chi[N-1] = left->chi[N-1];
		left->chi[N-1] = right;
		reset(left);
		copy_from_temp_to_left(temp, left);
		copy_from_temp_to_right(temp, right);
		int rs_key = right->key[0];
		insert_in_parent(left, rs_key, right);
	}
}

void init_root(void){
	Root = NULL;
}

int interactive(){
	int key;

	std::cout << "Key: ";
	std::cin >> key;

	return key;
}

int main(int argc, char *argv[]){
	struct timeval begin, end;

	init_root();

	printf("-----Insert-----\n");
	begin = cur_time();
	while (true) {
		insert(interactive(), NULL);
		print_tree(Root);
	}
	end = cur_time();

	return 0;
}
